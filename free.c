/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:27:54 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 13:33:56 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdt(t_table *cmdt)
{
	t_cmdline	*tmp;
	t_cmdline	*cur;

	cur = cmdt->head;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free_tokens(tmp->tokens);
		free(tmp);
	}
	free(cmdt);
}

void	free_tokens(t_table *tokens)
{
	t_token	*tmp;
	t_token	*cur;

	cur = tokens->head;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->token);
		free(tmp);
	}
	free(tokens);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i += 1;
	}
	free(args);
}
