/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:11:55 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/20 18:52:41 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

t_buf	*new_buf()
{
	t_buf *buf;

	buf = (t_buf *)malloc(sizeof(t_buf));
	buf->size = BUFFER_SIZE;
	buf->buffer = (char *)malloc(buf->size);
	buf->buffer[0] = '\0';
	buf->len = 0;
	return (buf);
}

void	buf_append(t_buf *buf, char c)
{

	buf->buffer[buf->len] = c;
	buf->len += 1;
	if (buf->len == buf->size)
		buf_expand(buf);
}

void	buf_expand(t_buf *buf)
{
	char	*new;
	int		i;

	new = (char *)malloc(buf->size * 2);
	buf->size *= 2;
	i = 0;
	while (buf->buffer[i])
	{
		new[i] = buf->buffer[i];
		i += 1;
	}
	new[i] = '\0';
	free(buf->buffer);
	buf->buffer = new;
}

void	buf_clear(t_buf *buf)
{
	buf->len = 0;
}

void	buf_destroy(t_buf *buf)
{
	free(buf->buffer);
	free(buf);
}
