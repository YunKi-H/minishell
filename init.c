/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:26:34 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 14:14:35 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*init_sh(char **envp)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->cmdt = init_table();
	sh->envt = init_envt(envp);
	sh->sh_error = 0;
	return (sh);
}

t_table	*init_table(void)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->head = NULL;
	table->size = 0;
	return (table);
}

t_cmdline	*init_cmdl(t_table *tokens)
{
	t_cmdline	*cmdl;

	cmdl = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!cmdl)
		return (NULL);
	cmdl->tokens = tokens;
	cmdl->input = STDIN_FILENO;
	cmdl->output = STDOUT_FILENO;
	cmdl->next = NULL;
	return (cmdl);
}

t_table	*init_envt(char **envp)
{
	t_table		*envt;
	int			i;

	envt = (t_table *)malloc(sizeof(t_table));
	if (!envt)
		return (NULL);
	envt->head = NULL;
	i = 0;
	while (envp[i])
	{
		env_add_back(envt, envp[i]);
		i += 1;
	}
	return (envt);
}

t_env	*init_env(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}
