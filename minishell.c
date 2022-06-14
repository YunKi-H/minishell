/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/14 16:56:54 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_sh	*msh;

	(void)argc;
	(void)argv;
	msh = init_sh(envp);
	ft_signal(&handler_default);
	while (1)
	{
		if (parsing(ft_readline("\rmsh % "), msh))
		{
			write(2, "syntax error\n", 14);
			continue ;
		}
		if (run_cmd(msh) > 256)
			msh->sh_error >>= 8;
	}
}

void	ft_err(int errnbr)
{
	printf("%s\n", strerror(errnbr));
	exit(errnbr);
}

int	check_syn_err(char *line)
{
	int	counts[3];

	ft_bzero(counts, 3 * sizeof(int));
	counts[INDEX] = -1;
	while (line[++counts[INDEX]])
	{
		if (isifs(line[counts[INDEX]]))
			continue ;
		toggle_flag_quote(line[counts[INDEX]], &counts[FLAG_Q]);
		if (line[counts[INDEX]] == '|' && counts[PIPE])
			return (258);
		if (line[counts[INDEX]] == '|')
			counts[PIPE] = TRUE;
		if (line[counts[INDEX]] != '|' && counts[PIPE])
			counts[PIPE] = FALSE;
	}
	if (counts[FLAG_Q] || counts[PIPE])
		return (258);
	return (0);
}

void	cmd_not_found(t_cmdline *cmdl)
{
	t_token	*cmd;

	cmd = cmdl->tokens->head;
	while (cmd->type != CMD)
		cmd = cmd->next;
	printf("command not found: %s\n", cmd->token);
	exit(127);
}




















void	check_leaks(int n)
{
	for (int i = 0; i < 20; i++)
		printf("%d", n);
	printf("\n");
	system("leaks minishell");
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
