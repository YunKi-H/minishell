/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:09:33 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/14 15:23:03 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_pure_token(t_token *token)
{
	int		flag_quote;
	int		i;
	t_buf	*buf;

	buf = buf_new();
	i = 0;
	flag_quote = FALSE;
	while (token->token[i])
	{
		if (token->token[i] == '\'' && !(flag_quote & DOUBLE_Q))
			flag_quote ^= SINGLE_Q;
		else if (token->token[i] == '\"' && !(flag_quote & SINGLE_Q))
			flag_quote ^= DOUBLE_Q;
		else
			buf_append(buf, token->token[i]);
		i += 1;
	}
	free(token->token);
	token->token = ft_strdup(buf->buffer);
	buf->len = 0;
	buf->buffer[0] = '\0';
	buf_destroy(buf);
}

t_table	*remove_quote(t_table *tokens)
{
	t_token	*token;

	token = tokens->head;
	while (token->next)
	{
		if (token->type == REDIRECT && token->next && !token->next->type)
			token->next->type = FILENAME;
		make_pure_token(token);
		token = token->next;
	}
	make_pure_token(token);
	token = tokens->head;
	while (token && token->type)
		token = token->next;
	if (token)
		token->type = CMD;
	return (tokens);
}
