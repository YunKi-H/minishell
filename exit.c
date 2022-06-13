/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:43:28 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 20:10:57 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*t;

	t = cmdl->tokens->head;
	if (!t->next)
	{
		if (sh->cmdt->size == 1)
			printf("exit\n");
		exit(0);
	}
	if (isnum(t->next->token))
	{
		if (t->next->next)
		{
			printf("exit\nexit: too many arguments\n");
			sh->sh_error = 1;
		}
		else
			exit((unsigned char)ft_atoi(t->next->token));
	}
	else
	{
		printf("exit\nexit: %s: numeric argument required\n", t->next->token);
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
