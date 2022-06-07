/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:46:45 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/07 16:28:20 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	if (!token->next)
	{
		t_env	*env = sh->envt->head;

		while (env)
		{
			printf("declare -x %s", env->key);
			if (env->value)
				printf("=%s",env->value);
			printf("\n");
			env = env->next;
		}
	}
	while (token)
	{
		if (token->next)
			token = token->next;
		else
			break ;
		if (!ft_strchr(token->token, '=') && isvalid_key(token->token))
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
		else if (!ft_strchr(token->token, '=') && !isvalid_key(token->token))
		{
			printf("export: `%s': not a valid identifier\n", token->token);
			sh->sh_error = 1;
			continue ;
		}
		else if (ft_strchr(token->token, '='))
		{
			char	*key;
			char	*value;
			t_env	*env;

			key = ft_substr(token->token, 0, ft_strchr(token->token, '=') - token->token);
			if (!isvalid_key(key))
			{
				printf("export: `%s': not a valid identifier\n", token->token);
				sh->sh_error = 1;
				free(key);
				continue ;
			}
			value = ft_strdup(ft_strchr(token->token, '=') + 1);
			env = _getenv(key, sh->envt);
			if (env)
			{
				free((void *)env->value);
				env->value = value;
			}
			else
			{
				env_add_back(sh->envt, token->token);
				free(key);
				free(value);
			}
		}
	}
	return (sh->sh_error);
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
