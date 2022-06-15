/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:45:34 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 09:43:56 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_exit_status(t_sh *sh, t_buf *buf)
{
	char	*sh_error;

	sh_error = ft_itoa(sh->sh_error);
	buf_append_str(buf, sh_error);
	free(sh_error);
	return (2);
}

static int	replace_env_value(char *cmdl, t_sh *sh, t_buf *buf, int idx)
{
	t_env	*env;
	char	*key;
	int		key_len;

	key_len = 0;
	idx += 1;
	while (iskey(cmdl[idx + key_len]) && cmdl[idx + key_len] != '$')
	{
		if (ft_isdigit(cmdl[idx]))
		{
			key_len = 1;
			break ;
		}
		key_len += 1;
	}
	key = ft_substr(cmdl, idx, key_len);
	env = _getenv(key, sh->envt);
	if (env)
		buf_append_str(buf, (char *)env->value);
	free(key);
	return (key_len + 1);
}

char	*replace_env(char *cmdl, t_sh *sh)
{
	t_buf	*buf;
	char	*replaced;
	int		flag_quote;
	int		i;

	i = 0;
	flag_quote = FALSE;
	buf = buf_new();
	while (cmdl[i])
	{
		toggle_flag_quote(cmdl[i], &flag_quote);
		if (cmdl[i] == '$' && cmdl[i + 1] == '?' && !(flag_quote & SINGLE_Q))
			i += replace_exit_status(sh, buf);
		else if (cmdl[i] == '$' && iskey(cmdl[i + 1]) \
			&& !(flag_quote & SINGLE_Q))
			i += replace_env_value(cmdl, sh, buf, i);
		else
		{
			buf_append(buf, cmdl[i]);
			i += 1;
		}
	}
	replaced = ft_strdup(buf->buffer);
	buf_destroy(buf);
	return (replaced);
}
