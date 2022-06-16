/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:47:07 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/16 11:35:06 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(t_sh *sh, t_token *token)
{
	t_env	*env;
	t_env	*prev;

	env = sh->envt->head;
	prev = env;
	while (env->next)
	{
		if (!ft_strncmp(env->key, token->token, -1))
			break ;
		if (prev->next == env)
			prev = prev->next;
		env = env->next;
	}
	if (!ft_strncmp(env->key, token->token, -1))
	{
		if (env == sh->envt->head)
			sh->envt->head = env->next;
		else
			prev->next = env->next;
		free((void *)env->key);
		free((void *)env->value);
		free(env);
		sh->envt->size -= 1;
	}
}

int	ft_unset(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	while (token->type != CMD)
		token = token->next;
	while (token)
	{
		if (token->next)
			token = token->next;
		else
			break ;
		if (token->type > 1)
			continue ;
		if (!isvalid_key(token->token))
		{
			printf("unset: `%s': not a valid identifier\n", token->token);
			sh->sh_error = 1;
			continue ;
		}
		else
			remove_env(sh, token);
	}
	return (sh->sh_error);
}
