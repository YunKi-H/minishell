/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:58:38 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 13:58:46 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	run_builtin(t_sh *sh, t_cmdline *cmdl)
{
	t_token *cmd;

	cmd = cmdl->tokens->head;
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
	if (!ft_strncmp(cmd->token, "cd", -1))
		return (ft_cd(sh, cmdl));
	if (!ft_strncmp(cmd->token, "echo", -1))
		return (ft_echo(cmdl));
	if (!ft_strncmp(cmd->token, "env", -1))
		return (ft_env(sh->envt));
	if (!ft_strncmp(cmd->token, "exit", -1))
		return (ft_exit(sh, cmdl));
	if (!ft_strncmp(cmd->token, "export", -1))
		return (ft_export(sh, cmdl));
	if (!ft_strncmp(cmd->token, "pwd", -1))
		return (ft_pwd());
	if (!ft_strncmp(cmd->token, "unset", -1))
		return (ft_unset(sh, cmdl));
	return (-1);
}

int	redirection_set(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	while (token)
	{
		if (token->type & REDIRECT)
		{
			if (!ft_strncmp(token->token, "<<", -1))
			{
				char	*delimeter;
				char	*line;
				int		fd[2];
				int		pid;

				if (cmdl->input > 1)
					close(cmdl->input);
				if (pipe(fd) < 0)
					; // pipe err
				cmdl->input = fd[0];
				delimeter = token->next->token;
				pid = fork();
				if (pid == 0)
				{
					signal(SIGINT, &handler_heredoc);
					signal(SIGQUIT, &handler_heredoc);
					close(fd[0]);
					while (TRUE)
					{
						line = ft_readline("> ");
						if (!ft_strncmp(delimeter, line, -1))
						{
							free(line);
							break ;
						}
						write(fd[1], line, ft_strlen(line));
						write(fd[1], "\n", 1);
						free(line);
					}
					close(fd[1]);
					exit(0);
				}
				else
				{
					waitpid(pid, &sh->sh_error, 0);
					close(fd[1]);
				}
			}
			if (!ft_strncmp(token->token, "<", -1))
			{
				if (cmdl->input > 1)
					close(cmdl->input);
				cmdl->input = open(token->next->token, O_RDONLY);
				if (cmdl->input < 0)
					; // file open err (no such file or directory)
			}
			if (!ft_strncmp(token->token, ">", -1))
			{
				if (cmdl->output > 1)
					close(cmdl->output);
				cmdl->output = open(token->next->token, O_RDWR | O_TRUNC | O_CREAT, 00666);
				if (cmdl->output < 0)
					printf("file open err\n"); // file open err (no such file or directory)
			}
			if (!ft_strncmp(token->token, ">>", -1))
			{
				if (cmdl->output > 1)
					close(cmdl->output);
				cmdl->output = open(token->next->token, O_RDWR | O_CREAT | O_APPEND, 00666);
				if (cmdl->output < 0)
					; // file open err (no such file or directory)
			}
		}
		token = token->next;
	}
	return (0);
}

int	excutor(t_sh *sh,t_cmdline *cmdl)
{
	return (execve(get_path(cmdl, sh), cmdltocmdp(cmdl->tokens), envttoevnp(sh->envt)));
}

int	run_cmd(t_sh *sh)
{
	t_cmdline	*cmdl;

	cmdl = sh->cmdt->head;
	while (cmdl)
	{
		redirection_set(sh, cmdl);
		cmdl = cmdl->next;
	}
	cmdl = sh->cmdt->head;
	if (isbuiltin(sh->cmdt->head) && sh->cmdt->size == 1)
	{
		int	stdfd[2];

		pipe(stdfd);
		close(stdfd[0]);
		close(stdfd[1]);
		dup2(0, stdfd[0]);
		dup2(1, stdfd[1]);
		if (cmdl->input > 0)
		{
			dup2(cmdl->input, 0);
			close(cmdl->input);
		}
		if (cmdl->output > 1)
		{
			dup2(cmdl->output, 1);
			close(cmdl->output);
		}
		sh->sh_error = run_builtin(sh, sh->cmdt->head);
		dup2(stdfd[0], 0);
		dup2(stdfd[1], 1);
	}
	else
	{
		int	*pid;
		int	i;
		int	pipe_old[2];
		int	pipe_new[2];

		pipe(pipe_old);
		close(pipe_old[0]);
		dup2(0, pipe_old[0]);
		i = 0;
		pid = (int *)ft_calloc(sh->cmdt->size, sizeof(int));
		while (i < sh->cmdt->size)
		{
			pipe(pipe_new);
			pid[i] = fork();
			if (!pid[i]) // child
			{
				dup2(pipe_old[0], 0);
				close(pipe_old[0]);
				close(pipe_old[1]);
				if (i != sh->cmdt->size - 1)
					dup2(pipe_new[1], 1);
				close(pipe_new[0]);
				close(pipe_new[1]);
				if (cmdl->input > 0)
				{
					dup2(cmdl->input, 0);
					close(cmdl->input);
				}
				if (cmdl->output > 1)
				{
					dup2(cmdl->output, 1);
					close(cmdl->output);
				}
				// run cmd
				if (isbuiltin(cmdl))
					exit(run_builtin(sh, cmdl));
				else
				{
					if (excutor(sh, cmdl))
						exit(127);
				}
			}
			else // parent
			{
				close(pipe_old[0]);
				close(pipe_old[1]);
				pipe_old[0] = pipe_new[0];
				pipe_old[1] = pipe_new[1];
				if (i == sh->cmdt->size - 1)
				{
					close(pipe_old[0]);
					close(pipe_old[1]);
				}
			}
			cmdl = cmdl->next;
			i += 1;
		}
		i = 0;
		while (i < sh->cmdt->size)
			waitpid(pid[i++], &sh->sh_error, 0);
		free(pid);
	}
	return (sh->sh_error);
}
