/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:11:53 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/20 18:58:33 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H
# define BUFFER_SIZE 32

# include <stdlib.h>

typedef struct s_buf	t_buf;

struct s_buf
{
	int		size;
	char	*buffer;
	int		len;
};

t_buf	*new_buf();
void	buf_append(t_buf *buf, char c);
void	buf_expand(t_buf *buf);
void	buf_clear(t_buf *buf);
void	buf_destroy(t_buf *buf);

#endif
