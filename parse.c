/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:31:25 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 13:33:07 by yuhwang          ###   ########.fr       */
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

int	parsing(char *line, t_sh *sh)
{
	t_buf	*buf;
	int	flag_quote;
	int	i;

	if (!line)
	{
		printf("\e[A%sexit\n", "msh % ");
		exit(0);
	}
	if (!isemptyline(line))
		add_history(line);
	free_cmdt(sh->cmdt);
	sh->cmdt = init_table();
	buf = buf_new();
	flag_quote = FALSE;
	i = 0;
	while (TRUE)
	{
		toggle_flag_quote(line[i], &flag_quote);
		if ((line[i] == '|' || !line[i]) && !flag_quote)
		{
			char	*cmdl = ft_strdup(buf->buffer);
			buf->len = 0;
			buf->buffer[0] = '\0';
			cmdl_add_back(sh->cmdt, init_cmdl(remove_quote(tokenize(replace_env(cmdl, sh)))));
			free(cmdl);
		}
		else
			buf_append(buf, line[i]);
		if (!line[i])
			break ;
		i += 1;
	}
	// (파이프 || flag on) 문장이 끝날 경우  예외처리
	// 0 < i -> if (i == 0)
	if (0 < i && (line[i - 1] == '|' || flag_quote))
	{
		printf("syntax error near unexpected token\n");
		sh->sh_error = 258;
		return (sh->sh_error);
	}
	buf_destroy(buf);
	free(line);
	return (0);
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
		{
			char	*sh_error;

			sh_error = ft_itoa(sh->sh_error);
			buf_append_str(buf, sh_error);
			free(sh_error);
			i += 2;
		}
		else if (cmdl[i] == '$' && iskey(cmdl[i + 1]) && !(flag_quote & SINGLE_Q))
		{
			char	*key;
			int		key_len = 0;
			i += 1;
			while (iskey(cmdl[i + key_len]))
				key_len += 1;
			key = ft_substr(cmdl, i, key_len);
			t_env	*env = sh->envt->head;
			while (env)
			{
				if (!ft_strncmp(key, env->key, -1))
					break ;
				env = env->next;
			}
			if (env)
				buf_append_str(buf, (char *)env->value);
			free(key);
			i += key_len;
		}
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

t_table *tokenize(char *line)
{
	t_table	*tokens;
	t_buf	*buf;
	int		flag_quote;
	int		i;

	tokens = init_table();
	buf = buf_new();
	flag_quote = FALSE;
	i = 0;
	while (isifs(line[i]))
		i += 1;
	while (TRUE)
	{
		toggle_flag_quote(line[i], &flag_quote);
		if ((isifs(line[i]) || !line[i]) && !flag_quote)
		{
			char *token = ft_strdup(buf->buffer);
			token_add_back(tokens, token, ARG);
			buf->len = 0;
			buf->buffer[0] = '\0';
			while (isifs(line[i]))
				i += 1;
			if (!line[i])
				break;
		}
		else if (isredirect(line, i) && !flag_quote)
		{
			if (buf->len)
				token_add_back(tokens, ft_strdup(buf->buffer), ARG);
			buf->len = 0;
			buf->buffer[0] = '\0';
			token_add_back(tokens, ft_substr(line, i, isredirect(line, i)), REDIRECT);
			i += isredirect(line, i);
			while (isifs(line[i]))
				i += 1;
			if (!line[i])
				break;
		}
		else
		{
			buf_append(buf, line[i]);
			i += 1;
		}
	}
	buf_destroy(buf);
	free(line);
	return (tokens);
}

t_table	*remove_quote(t_table *tokens)
{
	t_token	*token;
	t_buf	*buf;
	int		flag_quote;

	token = tokens->head;
	buf = buf_new();
	flag_quote = FALSE;
	while (token->next)
	{
		if (token->type == REDIRECT && token->next && !token->next->type)
			token->next->type = FILENAME;
		int	i;
		i = 0;
		while (token->token[i])
		{
			if (token->token[i] == '\'' && (!(flag_quote & DOUBLE_Q) || flag_quote & SINGLE_Q))
				flag_quote ^= SINGLE_Q;
			else if (token->token[i] == '\"' && (!(flag_quote & SINGLE_Q) || flag_quote & DOUBLE_Q))
				flag_quote ^= DOUBLE_Q;
			else
				buf_append(buf, token->token[i]);
			i += 1;
		}
		free(token->token);
		token->token = ft_strdup(buf->buffer);
		buf->len = 0;
		buf->buffer[0] = '\0';
		token = token->next;
	}
	int	i;
	i = 0;
	while (token->token[i])
	{
		if (token->token[i] == '\'' && (!(flag_quote & DOUBLE_Q) || flag_quote & SINGLE_Q))
			flag_quote ^= SINGLE_Q;
		else if (token->token[i] == '\"' && (!(flag_quote & SINGLE_Q) || flag_quote & DOUBLE_Q))
			flag_quote ^= DOUBLE_Q;
		else
			buf_append(buf, token->token[i]);
		i += 1;
	}
	free(token->token);
	token->token = ft_strdup(buf->buffer);
	buf->len = 0;
	buf->buffer[0] = '\0';
	if (token->type == REDIRECT)
		; // syntax error
	token = tokens->head;
	while (token && token->type)
		token = token->next;
	if (token)
		token->type = CMD;
	buf_destroy(buf);
	return (tokens);
}
