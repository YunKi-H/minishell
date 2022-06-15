/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:31:07 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 12:17:30 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err(int errnbr)
{
	printf("%s\n", strerror(errnbr));
	exit(errnbr);
}

void	cmd_not_found(t_cmdline *cmdl)
{
	t_token	*cmd;

	cmd = cmdl->tokens->head;
	while (cmd->type != CMD)
		cmd = cmd->next;
	print_err("command not found: ", cmd->token, "\n");
	exit(127);
}

void	print_err(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, s3, ft_strlen(s3));
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

int	check_redir_err(t_table *cmdt, t_sh *sh)
{
	t_cmdline	*cmdl;
	t_token		*token;

	cmdl = cmdt->head;
	while (cmdl)
	{
		token = cmdl->tokens->head;
		while (token)
		{
			if (token->type == REDIRECT)
			{
				if (!token->next || token->next->type != FILENAME)
				{
					sh->sh_error = 258;
					return (258);
				}
			}
			token = token->next;
		}
		cmdl = cmdl->next;
	}
	return (0);
}
