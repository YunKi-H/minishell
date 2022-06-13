/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:46:45 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 14:45:31 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_empty_val(t_sh *sh, t_token *token)
{
	t_env	*env;

	env = _getenv(token->token, sh->envt);
	if (!env)
	{
		env = sh->envt->head;
		while (env->next)
			env = env->next;
		env->next = init_env(ft_strdup(token->token), NULL);
	}
}

static int	export_valid_env(t_sh *sh, t_token *t)
{
	char	*key;
	t_env	*env;

	key = ft_substr(t->token, 0, ft_strchr(t->token, '=') - t->token);
	if (!isvalid_key(key))
	{
		printf("export: `%s': not a valid identifier\n", t->token);
		sh->sh_error = 1;
		free(key);
		return (1);
	}
	env = _getenv(key, sh->envt);
	if (env)
	{
		free((void *)env->value);
		env->value = ft_strdup(ft_strchr(t->token, '=') + 1);
	}
	else
	{
		env_add_back(sh->envt, t->token);
		free(key);
	}
	return (0);
}

static void	env_with_declare(t_sh *sh)
{
	t_env	*env;

	env = sh->envt->head;
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=%s", env->value);
		printf("\n");
		env = env->next;
	}
}

int	isvalid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (FALSE);
	i += 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i += 1;
	}
	return (TRUE);
}

int	ft_export(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	if (!token->next)
		env_with_declare(sh);
	while (token)
	{
		if (token->next)
			token = token->next;
		else
			break ;
		if (!ft_strchr(token->token, '=') && isvalid_key(token->token))
			export_empty_val(sh, token);
		else if (!ft_strchr(token->token, '=') && !isvalid_key(token->token))
		{
			printf("export: `%s': not a valid identifier\n", token->token);
			sh->sh_error = 1;
			continue ;
		}
		else if (ft_strchr(token->token, '='))
			if (export_valid_env(sh, token))
				continue ;
	}
	return (sh->sh_error);
}
