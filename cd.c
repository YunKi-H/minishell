/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:48:40 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/28 17:02:06 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_sh *sh, char *path)
{
	t_env	*oldpwd;
	t_env	*pwd;

	pwd = _getenv("PWD", sh->envt);
	oldpwd = _getenv("OLDPWD", sh->envt);
	if (pwd)
	{
		if (oldpwd)
		{
			free((void *)oldpwd->value);
			oldpwd->value = ft_strdup(pwd->value);
		}
		free((void *)pwd->value);
		pwd->value = ft_strdup(path);
	}
	else
	{
		if (oldpwd)
		{
			free((void *)oldpwd->value);
			oldpwd->value = ft_strdup("");
		}
	}
}

int	ft_cd(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*tmp;
	t_env	*env;

	if (cmdl->tokens->size == 1)
	{
		env = _getenv("HOME", sh->envt);
		if (!env)
		{
			printf("cd: HOME not set\n");
			sh->sh_error = 1;
		}
		else
			sh->sh_error = chdir(env->value);
	}
	else
	{
		tmp = cmdl->tokens->head;
		tmp = tmp->next;
		if (chdir(tmp->token) == -1)
		{
			printf("cd: %s: No such file or directory\n", tmp->token);
			sh->sh_error = 1;
		}
		else
			update_pwd(sh, tmp->token);
	}
	return (sh->sh_error);
}
