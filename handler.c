/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:25:49 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 13:03:45 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	handler_default(int sig)
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

void	handler_temp(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: %d\n", sig);
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\r");
		exit(1);
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_heredoc_p(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		return ;
}
