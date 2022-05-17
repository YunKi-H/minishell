/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/17 14:54:18 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

int	main(int argc, char *argv[], char **envp)
{
	t_sh	*msh;

	(void)argc;
	(void)argv;
	msh = init_sh(envp);


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

// cmd init
t_sh	*init_sh(char **envp)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->cmdt = init_cmdt();
	sh->envt = init_envt(envp);
	return (sh);
}

t_cmdtable	*init_cmdt()
{
	t_cmdtable	*cmdt;

	cmdt = (t_cmdtable *)malloc(sizeof(t_cmdtable));
	if (!cmdt)
		return (NULL);
	cmdt->head = NULL;
	cmdt->size = 0;
	return (cmdt);
}

t_cmdline	*init_cmdl()
{
	t_cmdline	*cmdl;

	cmdl = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!cmdl)
		return (NULL);
	cmdl->tokens = NULL;
	cmdl->redirect = NULL;
	cmdl->next = NULL;
	return (cmdl);
}

t_envtable	*init_envt(char **envp)
{
	t_envtable	*envt;
	int			i;

	envt = (t_envtable *)malloc(sizeof(t_envtable));
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

void	env_add_back(t_envtable *envt, char *env)
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








































int	parsing(char *line, t_cmdtable *cmdt)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			// i += 1;
			while (line[i] == '\"' && line[i])
			{
				if (line[i] == '$')
				{
					// i += 1;
				}
				// i += 1;
			}
		}
		if (line[i] == '\'')
		{
			// i += 1;
		}
		if (line[i] == '$')
		{
			// i += 1;
		}
		if (line[i] == '|')
		{
			// i += 1;
		}
		i += 1;
	}
}



































//builtin
// int	pwd()
// {
// 	char	*buf;

// 	buf = getcwd(NULL, 42);
// 	if (buf)
// 		printf("%s\n", buf);
// 	else
// 		return (1);
// 	free(buf);
// 	return (0);
// }

// static int	is_opt_echo(const char *word)
// {
// 	int	i;

// 	i = 0;
// 	if (word[i] != '-')
// 		return (0);
// 	else
// 	{
// 		i += 1;
// 		while (word[i])
// 		{
// 			if (word[i] != 'n')
// 				return (0);
// 			i += 1;
// 		}
// 	}
// 	return (1);
// }

// int echo(const char **parsed)
// {
// 	int	option;
// 	int	i;

// 	i = 1;
// 	option = 0;
// 	while (is_opt_echo(parsed[i]))
// 	{
// 		option = 1;
// 		i += 1;
// 	}
// 	while (parsed[i])
// 	{
// 		printf("%s", parsed[i]);
// 		i += 1;
// 		if (parsed[i])
// 			printf(" ");
// 	}
// 	if (!option)
// 		printf("\n");
// 	return (0);
// }

// int	cd(const char **parsed)
// {
// 	if (!parsed[1])
// 		return (chdir(getenv("HOME")));
// 	if (parsed[2])
// 		return (1);
// 	if (parsed[1][0] == '~' && !parsed[1][1])
// 		return (chdir(getenv("HOME"))); //구조체에 HOME 경로를 따로 저장(init 할떄)
// 	return (chdir(parsed[1]));
// }

// int	env(const char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n",env[i]);
// 		i += 1;
// 	}
// 	return (0);
// }

// void	parse(char *line, t_sh *sh)
// {
// 	char	**parsed;

// 	if (line)
// 		add_history(line);
// 	parsed = ft_split(line, ' ');
// 	if (!ft_strncmp("pwd", parsed[0], ft_strlen(parsed[0])))
// 		pwd();
// 	if (!ft_strncmp("echo", parsed[0], ft_strlen(parsed[0])))
// 		echo((const char **)parsed);
// 	if (!ft_strncmp("cd", parsed[0], ft_strlen(parsed[0])))
// 		cd((const char **)parsed);
// 	if (!ft_strncmp("env", parsed[0], ft_strlen(parsed[0])))
// 		env((const char **)sh->env);
// }
