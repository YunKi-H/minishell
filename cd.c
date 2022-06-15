/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:48:40 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 11:41:31 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_sh *sh)
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
		pwd->value = getcwd(NULL, 0);
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
	const t_token	*tmp = cmdl->tokens->head;
	const t_env		*env = _getenv("HOME", sh->envt);

	if (cmdl->tokens->size == 1)
	{
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
		if (chdir(tmp->next->token) == -1)
		{
			print_err("cd: ", tmp->next->token, \
			": No such file or directory\n");
			sh->sh_error = 1;
		}
		else
			update_pwd(sh);
	}
	return (sh->sh_error);
}
