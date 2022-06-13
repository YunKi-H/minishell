/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:58:38 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 17:01:35 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*cmd;

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

void	redir_input(t_cmdline *cmdl, t_token *token)
{
	if (cmdl->input > 1)
		close(cmdl->input);
	cmdl->input = open(token->next->token, O_RDONLY);
	if (cmdl->input < 0)
		ft_err(errno);
}

void	redir_output(t_cmdline *cmdl, t_token *token)
{
	if (cmdl->output > 1)
		close(cmdl->output);
	cmdl->output = open(token->next->token, O_RDWR | O_TRUNC | O_CREAT, 00666);
	if (cmdl->output < 0)
		ft_err(errno);
}

void	redir_append(t_cmdline *cmdl, t_token *token)
{
	if (cmdl->output > 1)
		close(cmdl->output);
	cmdl->output = open(token->next->token, O_RDWR | O_CREAT | O_APPEND, 00666);
	if (cmdl->output < 0)
		ft_err(errno);
}

void	redir_heredoc(t_sh *sh, t_cmdline *cmdl, char *delimeter)
{
	int		fd[2];
	char	*line;
	int		pid;

	if (pipe(fd) < 0)
		ft_err(errno);
	cmdl->input = fd[0];
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
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		free(line);
		close(fd[1]);
		exit(0);
	}
	waitpid(pid, &sh->sh_error, 0);
	close(fd[1]);
}

int	redirection_set(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	while (token)
	{
		if (token->type & REDIRECT)
		{
			if (!ft_strncmp(token->token, "<", -1))
				redir_input(cmdl, token);
			if (!ft_strncmp(token->token, ">", -1))
				redir_output(cmdl, token);
			if (!ft_strncmp(token->token, ">>", -1))
				redir_append(cmdl, token);
			if (!ft_strncmp(token->token, "<<", -1))
			{
				if (cmdl->input > 1)
					close(cmdl->input);
				ft_heredoc(sh, cmdl, token->next->token);
			}
		}
		token = token->next;
	}
	return (0);
}

int	excutor(t_sh *sh, t_cmdline *cl)
{
	return (
		execve(
			get_path(cl, sh), \
			cmdltocmdp(cl->tokens), \
			envttoevnp(sh->envt) \
		)
	);
}

void	exec_builtin_once(t_sh *sh, t_cmdline *cmdl)
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

void	set_child_pipe(t_cmdline *cmdl, int p_old[2], int p_new[2], int isend)
{
	dup2(p_old[0], 0);
	close(p_old[0]);
	close(p_old[1]);
	if (isend != 1)
		dup2(p_new[1], 1);
	close(p_new[0]);
	close(p_new[1]);
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
}

void	set_parent_pipe(t_cmdline *cmdl, int p_old[2], int p_new[2], int isend)
{
	close(p_old[0]);
	close(p_old[1]);
	p_old[0] = p_new[0];
	p_old[1] = p_new[1];
	if (isend == 1)
	{
		close(p_old[0]);
		close(p_old[1]);
	}
}

void	init_pipe(int p_old[2])
{
	pipe(p_old);
	close(p_old[0]);
	dup2(0, p_old[0]);
}

// line 26 -> 25 possible?
void	exec_cmds(t_sh *sh, t_cmdline *cmdl)
{
	int *const	pid = (int *)ft_calloc(sh->cmdt->size, sizeof(int));
	int			i;
	int			pipe_old[2];
	int			pipe_new[2];

	init_pipe(pipe_old);
	i = -1;
	while (++i < sh->cmdt->size)
	{
		pipe(pipe_new);
		pid[i] = fork();
		if (!pid[i])
		{
			set_child_pipe(cmdl, pipe_old, pipe_new, sh->cmdt->size - i);
			if (isbuiltin(cmdl))
				exit(run_builtin(sh, cmdl));
			else
				if (excutor(sh, cmdl))
					exit(127);
		}
		set_parent_pipe(cmdl, pipe_old, pipe_new, sh->cmdt->size - i);
		cmdl = cmdl->next;
	}
	i = 0;
	while (i < sh->cmdt->size)
		waitpid(pid[i++], &sh->sh_error, 0);
	free(pid);
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
		exec_builtin_once(sh, cmdl);
	else
		exec_emds(sh, cmdl);
	return (sh->sh_error);
}
