/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:34:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 16:57:35 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*make_path(char *path, char *name)
{
	t_buf	*buf;
	char	*path_with_file;

	buf = buf_new();
	buf_append_str(buf, path);
	buf_append(buf, '/');
	buf_append_str(buf, name);
	path_with_file = ft_strdup(buf->buffer);
	buf_destroy(buf);
	return (path_with_file);
}

static char	*fine_file(t_token *token, char **paths, int i)
{
	DIR				*dirp;
	struct dirent	*file;
	char			*p;

	dirp = opendir(paths[i]);
	if (!dirp)
		return (NULL);
	while (TRUE)
	{
		file = readdir(dirp);
		if (!file)
			break ;
		if (!ft_strncmp(token->token, file->d_name, -1))
		{
			p = make_path(paths[i], file->d_name);
			free_args(paths);
			closedir(dirp);
			return (p);
		}
	}
	closedir(dirp);
	return (NULL);
}

char	*get_path(t_cmdline *cmdl, t_sh *sh)
{
	const char	**paths = ft_split(_getenv("PATH", sh->envt)->value, ':');
	t_token		*token;
	char		*p;
	int			i;

	token = cmdl->tokens->head;
	while (token && token->type != CMD)
		token = token->next;
	i = -1;
	while (paths[++i])
	{
		p = find_file(token, paths, i);
		if (p)
			return (p);
	}
	free_args(paths);
	return (token->token);
}
