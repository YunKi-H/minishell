/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:34:03 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/16 12:07:51 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_input(t_sh *sh, t_cmdline *cmdl, t_token *token)
{
	if (cmdl->input > 0)
		close(cmdl->input);
	cmdl->input = open(token->next->token, O_RDONLY);
	if (cmdl->input < 0)
	{
		sh->sh_error = 1;
		print_err(token->next->token, ": ", strerror(errno));
		write(2, "\n", 1);
	}
}

void	redir_output(t_sh *sh, t_cmdline *cmdl, t_token *token)
{
	if (cmdl->output > 1)
		close(cmdl->output);
	cmdl->output = open(token->next->token, \
	O_RDWR | O_TRUNC | O_CREAT, \
	00666 \
	);
	if (cmdl->output < 0)
	{
		sh->sh_error = 1;
		print_err(token->next->token, ": ", strerror(errno));
		write(2, "\n", 1);
	}
}

void	redir_append(t_sh *sh, t_cmdline *cmdl, t_token *token)
{
	if (cmdl->output > 1)
		close(cmdl->output);
	cmdl->output = open(token->next->token, \
	O_RDWR | O_CREAT | O_APPEND, \
	00666 \
	);
	if (cmdl->output < 0)
	{
		sh->sh_error = 1;
		print_err(token->next->token, ": ", strerror(errno));
		write(2, "\n", 1);
	}
}

void	redir_heredoc(t_sh *sh, t_cmdline *cmdl, char *delimeter)
{
	int		fd[3];
	char	*line;

	ft_pipe(fd);
	cmdl->input = fd[0];
	fd[2] = fork();
	if (fd[2] == 0)
	{
		ft_signal(&handler_heredoc);
		close(fd[0]);
		while (TRUE)
		{
			line = ft_readline_heredoc("> ");
			if (!ft_strncmp(delimeter, line, -1))
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		exit(0);
	}
	close(fd[1]);
	ft_signal(&handler_heredoc_p);
	waitpid(fd[2], &sh->sh_error, 0);
	ft_signal(&handler_default);
}

int	redirection_set(t_sh *sh, t_cmdline *cmdl)
{
	t_token	*token;

	token = cmdl->tokens->head;
	while (token)
	{
		if (token->type & REDIRECT)
		{
			if (!ft_strncmp(token->token, "<", -1))
				redir_input(sh, cmdl, token);
			if (!ft_strncmp(token->token, ">", -1))
				redir_output(sh, cmdl, token);
			if (!ft_strncmp(token->token, ">>", -1))
				redir_append(sh, cmdl, token);
			if (!ft_strncmp(token->token, "<<", -1))
			{
				if (cmdl->input > 0)
					close(cmdl->input);
				redir_heredoc(sh, cmdl, token->next->token);
			}
			if (sh->sh_error)
				return (sh->sh_error);
		}
		token = token->next;
	}
	return (0);
}
