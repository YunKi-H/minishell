/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 13:58:53 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;

	t_sh	*msh;
	msh = init_sh(envp);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	while (1)
	{
		if (parsing(ft_readline("\rmsh % "), msh))
			continue ; // new prompt
		// todo : check_syn_err(msh);
		run_cmd(msh);
	}
}

void	print_cmdt(t_sh *sh)
{
	t_cmdline *cmdl;
	int i = 0;
	cmdl = sh->cmdt->head;
	while (cmdl)
	{
		t_token	*token;
		int j = 0;
		printf("----cmdl[%d]----\n", i);
		token = cmdl->tokens->head;
		while (token)
		{
			printf("token[%d] : [%s] (%d)", j, token->token, token->type);
			token = token->next;
			j += 1;
			printf("\n");
		}
		printf("----cmdl[%d]----\n", i);
		i += 1;
		cmdl = cmdl->next;
	}
}
