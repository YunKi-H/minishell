/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:36:14 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 18:44:15 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(int *fd)
{
	if (pipe(fd) < 0)
		ft_err(errno);
}

void	set_child_pipe(t_cmdline *cmdl, int *p_old, int *p_new, int isend)
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

void	set_parent_pipe(int *p_old, int *p_new, int isend)
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

void	init_pipe(int *p_old)
{
	ft_pipe(p_old);
	close(p_old[0]);
	dup2(0, p_old[0]);
}
