/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:58:38 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/16 10:59:19 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*cmd;

	cmd = cmdl->tokens->head;
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
	if (!ft_strncmp(cmd->token, "echo", -1))
		return (ft_echo(cmdl));
	sh->sh_error = 0;
	if (!ft_strncmp(cmd->token, "cd", -1))
		return (ft_cd(sh, cmdl));
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

int	excutor(t_sh *sh, t_cmdline *cl)
{
	char	*path;

	path = get_path(cl, sh);
	if (!path)
		return (1);
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

	ft_pipe(stdfd);
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
	close(stdfd[0]);
	close(stdfd[1]);
}

void	exec_cmds(t_sh *sh, t_cmdline *cmdl)
{
	int *const	pid = (int *)ft_calloc(sh->cmdt->size, sizeof(int));
	int			fd[5];

	init_pipe(fd);
	fd[4] = -1;
	while (++fd[4] < sh->cmdt->size)
	{
		ft_pipe(&fd[2]);
		pid[fd[4]] = fork();
		if (!pid[fd[4]])
		{
			set_child_pipe(cmdl, fd, &fd[2], sh->cmdt->size - fd[4]);
			if (isbuiltin(cmdl))
				exit(run_builtin(sh, cmdl));
			else
				if (excutor(sh, cmdl))
					cmd_not_found(cmdl);
			exit(0);
		}
		set_parent_pipe(fd, &fd[2], !cmdl->next, cmdl);
		cmdl = cmdl->next;
	}
	while (fd[4])
		waitpid(pid[sh->cmdt->size - fd[4]--], &sh->sh_error, 0);
	free(pid);
}

int	run_cmd(t_sh *sh)
{
	t_cmdline	*cmdl;

	cmdl = sh->cmdt->head;
	while (cmdl)
	{
		if (redirection_set(sh, cmdl))
			return (sh->sh_error);
		cmdl = cmdl->next;
	}
	cmdl = sh->cmdt->head;
	ft_signal(&handler_temp);
	if (find_cmd(cmdl) && ft_strrchr(find_cmd(cmdl)->token, 'm'))
		if (!ft_strncmp(ft_strrchr(find_cmd(cmdl)->token, 'm'), \
		"minishell", -1))
			ft_signal(&handler_nothing);
	if (isbuiltin(sh->cmdt->head) && sh->cmdt->size == 1)
		exec_builtin_once(sh, cmdl);
	else
	{
		exec_cmds(sh, cmdl);
		exit_status(sh->sh_error, sh);
	}
	ft_signal(&handler_default);
	return (sh->sh_error);
}
