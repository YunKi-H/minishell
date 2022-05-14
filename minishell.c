/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/14 16:31:11 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		parse(readline("Minishell % "));
	}
}

int	pwd()
{
	char	*buf;

	buf = getcwd(NULL, 42);
	if (buf)
		printf("%s\n", buf);
	else
		return (1);
	free(buf);
	return (0);
}

static int	is_opt_echo(const char *word)
{
	int	i;

	i = 0;
	if (word[i] != '-')
		return (0);
	else
	{
		i += 1;
		while (word[i])
		{
			if (word[i] != 'n')
				return (0);
			i += 1;
		}
	}
	return (1);
}

int echo(const char **parsed)
{
	int	option;
	int	i;

	i = 1;
	option = 0;
	while (is_opt_echo(parsed[i]))
	{
		option = 1;
		i += 1;
	}
	while (parsed[i])
	{
		printf("%s", parsed[i]);
		i += 1;
		if (parsed[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}

void	parse(char *line)
{
	char	**parsed;

	if (line)
		add_history(line);
	parsed = ft_split(line, ' ');
	if (!ft_strncmp("pwd", parsed[0], ft_strlen(parsed[0])))
		pwd();
	if (!ft_strncmp("echo", parsed[0], ft_strlen(parsed[0])))
		echo((const char **)parsed);
	if (!ft_strncmp("cd", parsed[0], ft_strlen(parsed[0])))
		cd((const char **)parsed);
}

int	cd(const char **parsed)
{
	if (!parsed[1])
		return (chdir(getenv("HOME")));
	if (parsed[2])
		return (1);
	if (parsed[1][0] == '~' && !parsed[1][1])
		return (chdir(getenv("HOME")));
	return (chdir(parsed[1]));
}
