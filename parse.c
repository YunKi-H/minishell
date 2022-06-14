/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:31:25 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/14 19:50:49 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_flag_quote(char c, int *flag)
{
	if (c == '\'' && !(*flag & DOUBLE_Q))
		*flag ^= SINGLE_Q;
	if (c == '\"' && !(*flag & SINGLE_Q))
		*flag ^= DOUBLE_Q;
}

void	make_cmdl(t_sh *sh, t_buf *buf)
{
	char	*cmdl;

	cmdl = ft_strdup(buf->buffer);
	buf->len = 0;
	buf->buffer[0] = '\0';
	cmdl_add_back(
		sh->cmdt, \
		init_cmdl(
			remove_quote(
				tokenize(replace_env(cmdl, sh))
				)
			)
		);
	free(cmdl);
}

int	parsing(char *line, t_sh *sh)
{
	t_buf	*buf;
	int		flag_quote;
	int		i;

	if (check_syn_err(line))
		return (258);
	free_cmdt(sh->cmdt);
	sh->cmdt = init_table();
	buf = buf_new();
	flag_quote = FALSE;
	i = 0;
	while (TRUE)
	{
		toggle_flag_quote(line[i], &flag_quote);
		if ((line[i] == '|' || !line[i]) && !flag_quote)
			make_cmdl(sh, buf);
		else
			buf_append(buf, line[i]);
		if (!line[i])
			break ;
		i += 1;
	}
	buf_destroy(buf);
	free(line);
	return (0);
}
