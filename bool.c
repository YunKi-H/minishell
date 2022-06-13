/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:32:43 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/13 19:37:40 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	isbuiltin(t_cmdline *cmdl)
{
	t_token	*cmd;

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
