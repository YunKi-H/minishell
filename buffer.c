/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:11:55 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 14:04:00 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

t_buf	*buf_new(void)
{
	t_buf	*buf;

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
	buf->buffer[buf->len] = '\0';
	if (buf->len + 1 == buf->size)
		buf_expand(buf);
}

void	buf_append_str(t_buf *buf, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		buf_append(buf, str[i]);
		i += 1;
	}
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

void	buf_destroy(t_buf *buf)
{
	free(buf->buffer);
	free(buf);
}
