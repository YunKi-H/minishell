/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:45:37 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/14 18:35:15 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmdline *cmdl)
{
	t_token	*token;
	int		opt;

	token = cmdl->tokens->head;
	opt = FALSE;
	token = token->next;
	while (token && isopt_echo(token->token))
	{
		opt = TRUE;
		token = token->next;
	}
	while (token)
	{
		if (token->type == ARG)
		{
			printf("%s", token->token);
			if (token->next)
				printf(" ");
		}
		token = token->next;
	}
	if (!opt)
		printf("\n");
	return (0);
}

int	isopt_echo(char *token)
{
	int	i;

	i = 0;
	if (token[i] != '-')
		return (FALSE);
	i += 1;
	if (!token[i])
		return (FALSE);
	while (token[i])
	{
		if (token[i] != 'n')
			return (FALSE);
		i += 1;
	}
	return (TRUE);
}
