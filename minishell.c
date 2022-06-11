/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/11 18:10:35 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(130);
	if (sig == SIGQUIT)
		return ;
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
		if (parsing(ft_readline("\rmsh % "), msh))
			continue ; // new prompt
		// todo : check_syn_err(msh);
		run_cmd(msh);
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
	cmdl->input = STDIN_FILENO;
	cmdl->output = STDOUT_FILENO;
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
	result = (char **)ft_calloc(envt->size + 1, sizeof(char *));
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
	buf_destroy(buf);
	return (result);
}

char	**cmdltocmdp(t_table *tokens)
{
	t_token		*tmp;
	char		**result;
	int			i;

	tmp = tokens->head;
	result = (char **)ft_calloc(tokens->size + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		if (tmp->type <= CMD)
		{
			result[i] = ft_strdup(tmp->token);
			i += 1;
		}
		tmp = tmp->next;
	}
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

	while (token && token->type != CMD)
		token = token->next;
	while (TRUE)
	{
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
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
	if (!cmd)
		return (FALSE);
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
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
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

char	*ft_readline(const char *prompt)
{
	char			*line;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	line = readline(prompt);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (line);
}

int	redirection_set(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	while (token)
	{
		if (token->type & REDIRECT)
		{
			if (!ft_strncmp(token->token, "<<", -1))
			{
				char	*delimeter;
				char	*line;
				int		fd[2];
				int		pid;

				if (cmdl->input > 1)
					close(cmdl->input);
				if (pipe(fd) < 0)
					; // pipe err
				cmdl->input = fd[0];
				delimeter = token->next->token;
				pid = fork();
				if (pid == 0)
				{
					signal(SIGINT, &handler_heredoc);
					signal(SIGQUIT, &handler_heredoc);
					close(fd[0]);
					while (TRUE)
					{
						line = ft_readline("> ");
						if (!ft_strncmp(delimeter, line, -1))
						{
							free(line);
							break ;
						}
						write(fd[1], line, ft_strlen(line));
						write(fd[1], "\n", 1);
						free(line);
					}
					close(fd[1]);
					exit(0);
				}
				else
				{
					waitpid(pid, &sh->sh_error, 0);
					close(fd[1]);
				}
			}
			if (!ft_strncmp(token->token, "<", -1))
			{
				if (cmdl->input > 1)
					close(cmdl->input);
				cmdl->input = open(token->next->token, O_RDONLY);
				if (cmdl->input < 0)
					; // file open err (no such file or directory)
			}
			if (!ft_strncmp(token->token, ">", -1))
			{
				if (cmdl->output > 1)
					close(cmdl->output);
				cmdl->output = open(token->next->token, O_RDWR | O_TRUNC | O_CREAT, 00666);
				if (cmdl->output < 0)
					; // file open err (no such file or directory)
			}
			if (!ft_strncmp(token->token, ">>", -1))
			{
				if (cmdl->output > 1)
					close(cmdl->output);
				cmdl->output = open(token->next->token, O_RDWR | O_CREAT | O_APPEND, 00666);
				if (cmdl->output < 0)
					; // file open err (no such file or directory)
			}
		}
		token = token->next;
	}
	return (0);
}

int	excutor(t_sh *sh,t_cmdline *cmdl)
{
	return (execve(get_path(cmdl, sh), cmdltocmdp(cmdl->tokens), envttoevnp(sh->envt)));
}

int	run_cmd(t_sh *sh)
{
	t_cmdline	*cmdl;

	cmdl = sh->cmdt->head;
	while (cmdl)
	{
		redirection_set(sh, cmdl);
		cmdl = cmdl->next;
	}
	cmdl = sh->cmdt->head;
	if (isbuiltin(sh->cmdt->head) && sh->cmdt->size == 1)
		sh->sh_error = run_builtin(sh, sh->cmdt->head);
	else
	{
		int	*pid;
		int	i;
		int	pipe_old[2];
		int	pipe_new[2];

		pipe(pipe_old);
		close(pipe_old[0]);
		close(pipe_old[1]);
		dup2(0, pipe_old[0]);
		i = 0;
		pid = (int *)ft_calloc(sh->cmdt->size, sizeof(int));
		while (i < sh->cmdt->size)
		{
			pipe(pipe_new);
			pid[i] = fork();
			if (!pid[i]) // child
			{
				close(pipe_old[1]);
				dup2(pipe_old[0], 0);
				close(pipe_old[0]);
				close(pipe_new[0]);
				if (i == sh->cmdt->size - 1)
					dup2(pipe_new[1], 1);
				close(pipe_new[1]);
				if (cmdl->input > 0)
				{
					dup2(cmdl->input, 0);
					close(cmdl->input);
				}
				if (cmdl->output > 1)
				{
					dup2(cmdl->output, 1);
					close(cmdl->output);
				}
				// run cmd
				if (isbuiltin(cmdl))
					exit(run_builtin(sh, cmdl));
				else
				{
					if (excutor(sh, cmdl))
						exit(127);
				}
			}
			else // parent
			{
				close(pipe_old[0]);
				pipe_old[0] = pipe_new[0];
				pipe_old[1] = pipe_new[1];
				close(pipe_old[1]);
				if (i == sh->cmdt->size - 1)
					close(pipe_old[0]);
			}
			cmdl = cmdl->next;
			i += 1;
		}
		i = 0;
		while (i < sh->cmdt->size)
			waitpid(pid[i], &sh->sh_error, 0);
		free(pid);
	}
	return (sh->sh_error);
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
