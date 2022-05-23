/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/23 18:51:36 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;

	t_sh	*msh;
	msh = init_sh(envp);

	// tokenize test
	while (1)
	{
		// parsing(readline("Minishell % "), msh);
		parsing(ft_strdup("echo            \"he\"l'l'\"o\" '|' \"cat\" -e"), msh);
		print_cmdt(msh);
		// type
		// remove quote
		break ;
	}

	// replace_env test
	// char *test1 = replace_env("abcdefg hijklmn opqrstu ", msh);
	// printf("test1 = %s\n", test1);
	// char *test2 = replace_env("$USER", msh);
	// printf("test2 = %s\n", test2);
	// char *test3 = replace_env("\"$USER\" '$USER' \"$USER\"", msh);
	// printf("test3 = %s\n", test3);
	// char *test4 = replace_env("$USER$AAA$USER$USER$AAA", msh);
	// printf("test4 = %s\n", test4);
	// char *test5 = replace_env("$ \"$\" $ ", msh);
	// printf("test5 = %s\n", test5);
	// char *test6 = replace_env("$USER\"abc\"", msh);
	// printf("test6 = %s\n", test6);

	// buffer test
	// t_buf	*test;
	// test = new_buf();
	// char *tmp = "abcdefghikljsdfhbnojnfbop oijfapobknadsdfbfdobnjokjop oaksdjfoasfhbniosejbno woakdgjnaaaaaaaaaaa";
	// int i = 0;
	// while (tmp[i])
	// {
	// 	printf("%d\n", i);
	// 	buf_append(test, tmp[i]);
	// 	i += 1;
	// }
	// system("leaks minishell");
	// printf("%d %s\n", test->size, test->buffer);

	// getenv 동적할당여부 (false)
	// char *test = getenv("PWD");
	// printf("PWD : %s\n", test);
	// free(test);

	// 환경변수 제대로 init 된거 test
	// t_env	*tmp = msh->envt->head;
	// int i = 0;
	// while (tmp)
	// {
	// 	printf("[%d] key : [%s] value : [%s]\n", i, tmp->key, tmp->value);
	// 	i += 1;
	// 	tmp = tmp->next;
	// }

	// readline 동적할당여부 (true)
	// char *line = readline("shell % ");
	// printf("line : %s\n",line);
	// free(line);

}

// init
t_sh	*init_sh(char **envp)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->cmdt = init_table();
	sh->envt = init_envt(envp);
	sh->sh_error = 0;
	return (sh);
}

t_table	*init_table(void)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->head = NULL;
	table->size = 0;
	return (table);
}

t_cmdline	*init_cmdl(t_table *tokens)
{
	t_cmdline	*cmdl;

	cmdl = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!cmdl)
		return (NULL);
	cmdl->tokens = tokens;
	cmdl->next = NULL;
	return (cmdl);
}

t_table	*init_envt(char **envp)
{
	t_table	*envt;
	int			i;

	envt = (t_table *)malloc(sizeof(t_table));
	if (!envt)
		return (NULL);
	envt->head = NULL;
	i = 0;
	while (envp[i])
	{
		env_add_back(envt, envp[i]);
		i += 1;
	}
	return (envt);
}

t_env	*init_env(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

// free
void	free_cmdt(t_table *cmdt)
{
	t_cmdline	*tmp;
	t_cmdline	*cur;

	cur = cmdt->head;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free_tokens(tmp->tokens);
		free(tmp);
	}
	free(cmdt);
}

void	free_tokens(t_table *tokens)
{
	t_token	*tmp;
	t_token	*cur;

	cur = tokens->head;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->token);
		free(tmp);
	}
	free(tokens);
}

// struct 제어
void	env_add_back(t_table *envt, char *env)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	value = ft_strdup(ft_strchr(env, '=') + 1);
	if (!envt->head)
		envt->head = init_env(key, value);
	else
	{
		tmp = envt->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_env(key, value);
	}
	envt->size += 1;
}

void	cmdl_add_back(t_table *cmdt, t_cmdline *cmdl)
{
	t_cmdline	*tmp;

	if (!cmdt->head)
		cmdt->head = cmdl;
	else
	{
		tmp = cmdt->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmdl;
	}
}

void	token_add_back(t_table *tokens, char *token)
{
	t_token *tmp;
	t_token *cur;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->token = token;
	tmp->type = 0;
	tmp->next = NULL;
	cur = tokens->head;
	if (!cur)
		tokens->head = tmp;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = tmp;
	}
	tokens->size += 1;
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
		if (line[i] == '\'' && !(flag_quote & DOUBLE_Q))
			flag_quote ^= SINGLE_Q;
		if (line[i] == '\"' && !(flag_quote & SINGLE_Q))
			flag_quote ^= DOUBLE_Q;
		if ((isifs(line[i]) || !line[i]) && !flag_quote)
		{
			char *token = ft_strdup(buf->buffer);
			token_add_back(tokens, token);
			buf->len = 0;
			while (isifs(line[i]))
				i += 1;
			if (!line[i])
				break ;
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

// parse
void	parsing(char *line, t_sh *sh)
{
	t_buf	*buf;
	int	flag_quote;
	int	i;

	free_cmdt(sh->cmdt);
	sh->cmdt = init_table();
	buf = buf_new();
	flag_quote = FALSE;
	i = 0;
	while (TRUE)
	{
		if (line[i] == '\'' && !(flag_quote & DOUBLE_Q))
			flag_quote ^= SINGLE_Q;
		if (line[i] == '\"' && !(flag_quote & SINGLE_Q))
			flag_quote ^= DOUBLE_Q;
		if ((line[i] == '|' || !line[i]) && !flag_quote)
		{
			printf("%c\n", line[i]);
			char	*cmdl = ft_strdup(buf->buffer);
			buf->len = 0;
			cmdl_add_back(sh->cmdt, init_cmdl(tokenize(replace_env(cmdl, sh))));
			free(cmdl);
		}
		else
			buf_append(buf, line[i]);
		if (!line[i])
			break ;
		i += 1;
	}
	buf_destroy(buf);
	free(line);
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
		if (cmdl[i] == '\'' && !(flag_quote & DOUBLE_Q))
			flag_quote ^= SINGLE_Q;
		if (cmdl[i] == '\"' && !(flag_quote & SINGLE_Q))
			flag_quote ^= DOUBLE_Q;
		if (cmdl[i] == '$' && iskey(cmdl[i + 1]) && !(flag_quote & SINGLE_Q))
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

int	iskey(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	isifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	print_cmdt(t_sh *sh)
{
	t_cmdline *cmdl;
	int i = 0;
	cmdl = sh->cmdt->head;
	while (cmdl)
	{
		t_token	*token;
		int j = 0;
		printf("----cmdl[%d]----\n", i);
		token = cmdl->tokens->head;
		while (token)
		{
			printf("token[%d] : [%s] ", j, token->token);
			token = token->next;
			j += 1;
			printf("\n");
		}
		i += 1;
		printf("\n");
		cmdl = cmdl->next;
	}
}
