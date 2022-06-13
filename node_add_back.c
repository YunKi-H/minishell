/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:30:16 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 14:16:25 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_table *envt, char *env)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	value = ft_strdup(ft_strchr(env, '=') + 1);
	if (!envt->head)
		envt->head = init_env(key, value);
	else
	{
		tmp = envt->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_env(key, value);
	}
	envt->size += 1;
}

void	cmdl_add_back(t_table *cmdt, t_cmdline *cmdl)
{
	t_cmdline	*tmp;

	if (!cmdt->head)
		cmdt->head = cmdl;
	else
	{
		tmp = cmdt->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmdl;
	}
	cmdt->size += 1;
}

void	token_add_back(t_table *tokens, char *token, int type)
{
	t_token	*tmp;
	t_token	*cur;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->token = token;
	tmp->type = type;
	tmp->next = NULL;
	cur = tokens->head;
	if (!cur)
		tokens->head = tmp;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = tmp;
	}
	tokens->size += 1;
}
