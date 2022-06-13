/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:33:31 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 13:33:39 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envttoevnp(t_table *envt)
{
	t_buf		*buf;
	t_env		*tmp;
	char		**result;
	int			i;

	buf = buf_new();
	tmp = envt->head;
	result = (char **)ft_calloc(envt->size + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		buf_append_str(buf, (char *)tmp->key);
		buf_append(buf, '=');
		buf_append_str(buf, (char *)tmp->value);
		result[i] = ft_strdup(buf->buffer);
		buf->len = 0;
		buf->buffer[0] = '\0';
		i += 1;
		tmp = tmp->next;
	}
	buf_destroy(buf);
	return (result);
}

char	**cmdltocmdp(t_table *tokens)
{
	t_token		*tmp;
	char		**result;
	int			i;

	tmp = tokens->head;
	result = (char **)ft_calloc(tokens->size + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		if (tmp->type <= CMD)
		{
			result[i] = ft_strdup(tmp->token);
			i += 1;
		}
		tmp = tmp->next;
	}
	return (result);
}
