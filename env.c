/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:46:14 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/28 17:02:28 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_table *envt)
{
	t_env	*env;

	env = envt->head;
	while (env)
	{
		printf("%s", env->key);
		printf("=");
		printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
