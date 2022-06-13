/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:43:47 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 19:58:06 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_ifs(char *line, int *i)
{
	while (isifs(line[*i]))
		*i += 1;
	if (!line[*i])
		return (EOF);
	return (0);
}

static void	buf_to_token(t_table *tokens, t_buf *buf)
{
	token_add_back(tokens, ft_strdup(buf->buffer), ARG);
	buf->len = 0;
	buf->buffer[0] = '\0';
}

static void	make_tokens(char *l, t_table *tokens, t_buf *buf, int i)
{
	int	flag_quote;

	flag_quote = FALSE;
	skip_ifs(l, &i);
	while (TRUE)
	{
		toggle_flag_quote(l[i], &flag_quote);
		if ((isifs(l[i]) || !l[i]) && !flag_quote)
		{
			buf_to_token(tokens, buf);
			if (skip_ifs(l, &i) == EOF)
				break ;
		}
		else if (isredirect(l, i) && !flag_quote)
		{
			if (buf->len)
				buf_to_token(tokens, buf);
			token_add_back(tokens, ft_substr(l, i, isredirect(l, i)), REDIRECT);
			i += isredirect(l, i);
			if (skip_ifs(l, &i) == EOF)
				break ;
		}
		else
			buf_append(buf, l[i++]);
	}
}

t_table	*tokenize(char *line)
{
	t_table	*tokens;
	t_buf	*buf;

	tokens = init_table();
	buf = buf_new();
	make_tokens(line, tokens, buf, 0);
	buf_destroy(buf);
	free(line);
	return (tokens);
}
