/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/21 08:47:22 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_sh	*msh;

	(void)argc;
	(void)argv;
	(void)envp;
	msh = init_sh(envp);

	// replace_env test
	char *test = "abc\"$PWD\" '$HOME' $ ";
	char *tmp = replace_env(test, msh);
	printf("%s\n", tmp);

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

	// while (1)
	// {
	// 	parse(readline("Minishell % "), sh);
	// }

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
	return (table);
}

t_cmdline	*init_cmdl(void)
{
	t_cmdline	*cmdl;

	cmdl = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!cmdl)
		return (NULL);
	cmdl->tokens = init_table();
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

// void	token_add_back(t_cmdline *cmdl, char *token, int type)
// {

// }

// parse
// int	parsing(char *line, t_sh *sh)
// {
// 	t_cmdline	*cmdl;
// 	t_token		*token;
// 	int	i[2];
// 	int	flag_quote;

// 	free_cmdt(sh->cmdt);
// 	ft_bzero(i, sizeof(int) * 2);
// 	flag_quote = FALSE;
// 	while (line[i[1]])
// 	{
// 		if (line[i[1]] == '\'' && !(flag_quote & DOUBLE_Q))
// 			flag_quote ^= SINGLE_Q;
// 		if (line[i[1]] == '\"' && !(flag_quote & SINGLE_Q))
// 			flag_quote ^= DOUBLE_Q;
// 		if (line[i[1]] == '|' && !flag_quote)
// 		{
// 			char	*cmdline = ft_substr(line, i[0], i[1] - i[0]);
// 			i[0] = i[1] + 1;
// 		}
// 		i[1] += 1;
// 	}
// 	free(line);
// }

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
		if (cmdl[i] == '$' && iskey(cmdl[i + 1]) && !(flag_quote & SINGLE_Q))
		{
			char	*key;
			char	*value;
			int		key_len = 0;
			i += 1;
			while (iskey(cmdl[i + key_len]))
				key_len += 1;
			key = ft_substr(cmdl, i, key_len);
			t_env	*env = sh->envt->head;
			while (env)
			{
				// printf("key : %s, env.key : %s, strcmp = %d\n", key, env->key, \
				// 	ft_strncmp(key, env->key, -1));
				if (!ft_strncmp(key, env->key, -1))
					break ;
				env = env->next;
			}
			if (!env)
				value = ft_strdup("");
			else
				value = ft_strdup(env->value);
			buf_append_str(buf, value);
			free(key);
			free(value);
			i += key_len;
		}
		if (cmdl[i] == '\'' && !(flag_quote & DOUBLE_Q))
			flag_quote ^= SINGLE_Q;
		if (cmdl[i] == '\"' && !(flag_quote & SINGLE_Q))
			flag_quote ^= DOUBLE_Q;
		buf_append(buf, cmdl[i]);
		i += 1;
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
