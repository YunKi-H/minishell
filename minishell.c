/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 17:04:54 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_status(int status, t_sh *sh)
{
	if (WIFEXITED(status))
		sh->sh_error = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		sh->sh_error = WTERMSIG(status) + 128;
}

int	main(int argc, char *argv[], char **envp)
{
	t_sh	*msh;
	char	*line;

	(void)argc;
	(void)argv;
	msh = init_sh(envp);
	ft_signal(&handler_default);
	while (1)
	{
		line = ft_readline("msh % ");
		if (!line)
			continue ;
		if (parsing(line, msh))
		{
			write(2, "syntax error\n", 14);
			continue ;
		}
		exit_status(run_cmd(msh), msh);
	}
}

void	ft_signal(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
