/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/05 14:11:01 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig != SIGINT)
		return ;
	write(1, "\b\b  \b\b", 6);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "\b\b\b\b\b\b\b\bmsh % ", 14);
	write(1, "\n", 1);
	// write(1, "msh % \n", 7);
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;

	t_sh	*msh;
	msh = init_sh(envp);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	while (1)
	{
		if (parsing(readline("msh % "), msh))
			continue ; // new prompt

		if (isbuiltin(msh->cmdt->head))
			msh->sh_error = run_builtin(msh, msh->cmdt->head);
		else
		{
			t_cmdline	*cmdl = msh->cmdt->head;
			int			pid;

			pid = fork();
			if (!pid)
			{
				if (execve(get_path(cmdl, msh), cmdltocmdp(cmdl->tokens), envttoevnp(msh->envt)) < 0)
				{
					msh->sh_error = errno;
					printf("%s\n", strerror(errno));
				}
			}
			waitpid(-1, &msh->sh_error, 0);
		}
	}

	// get_path test
	// while (1)
	// {
	// 	parsing(readline("msh % "), msh);
	// 	char *path = get_path(msh->cmdt->head, msh);
	// 	printf("%s\n", path);
	// 	free(path);
	// 	system("leaks minishell");
	// }

	// _getenv test
	// printf("%s : %s\n", "USER", _getenv("USER", msh->envt)->value);
	// printf("%s : %s\n", "LANG", _getenv("LANG", msh->envt)->value);
	// printf("%s : %s\n", "_", _getenv("_", msh->envt)->value);
	// printf("%s : %s\n", "AAAA", (char *)_getenv("AAAA", msh->envt));

	// exit test
	// t_env *env = msh->envt->head;
	// env->next->next = NULL;
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_exit(msh, cmdl);
	// 	printf("%d\n", msh->sh_error);
	// 	break;
	// }

	// unset test
	// t_env *env = msh->envt->head;
	// env->next->next = NULL;
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	ft_env(msh->envt);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_unset(msh, cmdl);
	// 	ft_env(msh->envt);
	// }

	// export test
	// t_env *env = msh->envt->head;
	// env->next = NULL;
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_export(msh, cmdl);
	// 	ft_env(msh->envt);
	// }

	// cd test
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	t_cmdline	*cmdl = msh->cmdt->head;
	// 	ft_cd(msh, cmdl);
	// 	ft_pwd();
	// }

	// tokenize test
	// while (1)
	// {
	// 	parsing(readline("Minishell % "), msh);
	// 	// parsing(ft_strdup("echo            \"he\"l'l'\"o\" '|' \"cat\" -e"), msh);
	// 	print_cmdt(msh);
	// 	break ;
	// }

	// env,pwd test
	// ft_env(msh->envt);
	// printf("-----------\n");
	// ft_pwd();

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
	// msh->sh_error = 127;
	// char *test6 = replace_env("$???", msh);
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
	cmdt->size += 1;
}

void	token_add_back(t_table *tokens, char *token, int type)
{
	t_token *tmp;
	t_token *cur;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->token = token;
	tmp->type = type;
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

// parse
int	parsing(char *line, t_sh *sh)
{
	t_buf	*buf;
	int	flag_quote;
	int	i;

	if (!line)
	{
		printf("exit\n");
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
	token->type = CMD;
	buf = buf_new();
	flag_quote = FALSE;
	while (token->next)
	{
		if (token->type == REDIRECT)
			token->next->type = FILENAME;
		// func1
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
	// func1
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
	buf_destroy(buf);
	return (tokens);
}

int	iskey(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	isifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	isredirect(char *line, int i)
{
	int	result;

	result = 0;
	if (line[i] == '<' || line[i] == '>')
	{
		result += 1;
		if (line[i + 1] && line[i] == line[i + 1])
			result += 1;
	}
	else
		result = 0;
	return (result);
}

int	isemptyline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isifs(line[i]))
			return (FALSE);
		i += 1;
	}
	return (TRUE);
}

void	toggle_flag_quote(char c, int *flag)
{
	if (c == '\'' && !(*flag & DOUBLE_Q))
		*flag ^= SINGLE_Q;
	if (c == '\"' && !(*flag & SINGLE_Q))
		*flag ^= DOUBLE_Q;
}

char	**envttoevnp(t_table *envt)
{
	t_buf		*buf;
	t_env		*tmp;
	char		**result;
	int			i;

	buf = buf_new();
	tmp = envt->head;
	result = (char **)malloc(sizeof(char *) * (envt->size + 1));
	i = 0;
	while (tmp)
	{
		buf_append_str(buf, (char *)tmp->key);
		buf_append(buf, '=');
		buf_append_str(buf, (char *)tmp->value);
		result[i] = ft_strdup(buf->buffer);
		buf->len = 0;
		buf->buffer[0] = '\0';
		i += 1;
		tmp = tmp->next;
	}
	result[i] = NULL;
	buf_destroy(buf);
	return (result);
}

char	**cmdltocmdp(t_table *tokens)
{
	t_token		*tmp;
	char		**result;
	int			i;

	tmp = tokens->head;
	result = (char **)malloc(sizeof(char *) * (tokens->size + 1));
	i = 0;
	while (tmp)
	{
		result[i] = ft_strdup(tmp->token);
		i += 1;
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i += 1;
	}
	free(args);
}

t_env	*_getenv(char *key, t_table *envt)
{
	t_env	*env;

	env = envt->head;
	if (!env)
		return (env);
	while (env->next)
	{
		if (!ft_strncmp(key, env->key, -1))
			break ;
		env = env->next;
	}
	if (ft_strncmp(key, env->key, -1))
		env = env->next;
	return (env);
}

char	*get_path(t_cmdline *cmdl, t_sh *sh)
{
	t_token			*token = cmdl->tokens->head;
	t_env			*path = _getenv("PATH", sh->envt);
	char			**paths = ft_split(path->value, ':');
	DIR				*dirp = opendir(".");
	struct dirent	*file = NULL;
	int				i = 0;
	t_buf			*buf = buf_new();
	char			*p;

	while (TRUE)
	{
		// printf("2\n");
		file = readdir(dirp);
		if (!file)
			break ;
		if (!ft_strncmp(token->token, file->d_name, -1))
		{
			buf_append(buf, '.');
			buf_append(buf, '/');
			buf_append_str(buf, file->d_name);
			p = ft_strdup(buf->buffer);
			buf_destroy(buf);
			int	j = 0;
			while (paths[j])
			{
				free(paths[j]);
				j += 1;
			}
			closedir(dirp);
			free(paths);
			return (p);
		}
	}
	closedir(dirp);
	while (paths[i])
	{
		// printf("3\n");
		dirp = opendir(paths[i]);
		if (!dirp)
		{
			i += 1;
			continue ;
		}
		while (TRUE)
		{
			file = readdir(dirp);
			if (!file)
				break ;
			// printf ("4 : %s\n", file->d_name);
			if (!ft_strncmp(token->token, file->d_name, -1))
			{
				buf_append_str(buf, paths[i]);
				buf_append(buf, '/');
				buf_append_str(buf, file->d_name);
				p = ft_strdup(buf->buffer);
				buf_destroy(buf);
				int	j = 0;
				while (paths[j])
				{
					free(paths[j]);
					j += 1;
				}
				closedir(dirp);
				free(paths);
				return (p);
			}
		}
		closedir(dirp);
		i += 1;
	}
	buf_destroy(buf);
	int	j = 0;
	while (paths[j])
	{
		free(paths[j]);
		j += 1;
	}
	free(paths);
	return (NULL);
}

int	isbuiltin(t_cmdline *cmdl)
{
	t_token *cmd;

	cmd = cmdl->tokens->head;
	if (!ft_strncmp(cmd->token, "cd", -1))
		return (TRUE);
	if (!ft_strncmp(cmd->token, "echo", -1))
		return (TRUE);
	if (!ft_strncmp(cmd->token, "env", -1))
		return (TRUE);
	if (!ft_strncmp(cmd->token, "exit", -1))
		return (TRUE);
	if (!ft_strncmp(cmd->token, "export", -1))
		return (TRUE);
	if (!ft_strncmp(cmd->token, "pwd", -1))
		return (TRUE);
	if (!ft_strncmp(cmd->token, "unset", -1))
		return (TRUE);
	return (FALSE);
}

int	run_builtin(t_sh *sh, t_cmdline *cmdl)
{
	t_token *cmd;

	cmd = cmdl->tokens->head;
	if (!ft_strncmp(cmd->token, "cd", -1))
		return (ft_cd(sh, cmdl));
	if (!ft_strncmp(cmd->token, "echo", -1))
		return (ft_echo(cmdl));
	if (!ft_strncmp(cmd->token, "env", -1))
		return (ft_env(sh->envt));
	if (!ft_strncmp(cmd->token, "exit", -1))
		return (ft_exit(sh, cmdl));
	if (!ft_strncmp(cmd->token, "export", -1))
		return (ft_export(sh, cmdl));
	if (!ft_strncmp(cmd->token, "pwd", -1))
		return (ft_pwd());
	if (!ft_strncmp(cmd->token, "unset", -1))
		return (ft_unset(sh, cmdl));
	return (-1);
}

int	run_cmd(t_sh *sh)
{
	if (isbuiltin(sh->cmdt->head) && sh->cmdt->size == 1)
		return (run_builtin(sh, sh->cmdt->head));
	return (0);
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
			printf("token[%d] : [%s] (%d)", j, token->token, token->type);
			token = token->next;
			j += 1;
			printf("\n");
		}
		printf("----cmdl[%d]----\n", i);
		i += 1;
		cmdl = cmdl->next;
	}
}
