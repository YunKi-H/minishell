/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 18:46:20 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_sh	*msh;

	(void)argc;
	(void)argv;
	msh = init_sh(envp);
	ft_signal(&handler);
	while (1)
	{
		if (parsing(ft_readline("\rmsh % "), msh))
			continue ; // new prompt
		// todo : check_syn_err(msh);
		run_cmd(msh);
	}
}

void	ft_err(int errnbr)
{
	printf("%s\n", strerror(errnbr));
	exit(errnbr);
}
