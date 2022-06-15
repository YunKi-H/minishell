/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:43:28 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 11:37:37 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit(int status)
{
	write(2, "exit\n", 5);
	exit(status);
}

int	ft_exit(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*t;

	t = cmdl->tokens->head;
	if (!t->next)
	{
		if (sh->cmdt->size == 1)
			print_exit(0);
	}
	if (isnum(t->next->token))
	{
		if (t->next->next)
		{
			print_err("exit\n", "exit: too many arguments", "\n");
			sh->sh_error = 1;
		}
		else
			print_exit(ft_atoi(t->next->token) & 0b11111111);
	}
	else
	{
		print_err("exit\nexit: ", t->next->token, \
		": numeric argument required\n");
		exit(255);
	}
	return (sh->sh_error);
}

int	isnum(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '+' || token[i] == '-')
		i += 1;
	if (!token[i])
		return (FALSE);
	while (token[i])
	{
		if (token[i] < '0' || token[i] > '9')
			return (FALSE);
		i += 1;
	}
	return (TRUE);
}
