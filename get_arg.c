/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:34:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 13:34:48 by yuhwang          ###   ########.fr       */
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
