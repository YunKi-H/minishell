/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:43:28 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/28 17:00:23 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	if (!token->next)
	{
		printf("exit\n");
		exit(0);
	}
	token = token->next;
	if (isnum(token->token))
	{
		if (token->next)
		{
			printf("exit\nexit: too many arguments\n");
			sh->sh_error = 1;
		}
		else
			exit((unsigned char)ft_atoi(token->token));
	}
	else
	{
		printf("exit\nexit: %s: numeric argument required\n", token->token);
		exit(255);
	}
	return (sh->sh_error);
}

int	isnum(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] < '0' || token[i] > '9')
			return (FALSE);
		i += 1;
	}
	return (TRUE);
}
