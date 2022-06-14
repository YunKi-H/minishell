/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:35:26 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/14 18:45:39 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *prompt)
{
	char			*line;
	struct termios	term_old;
	struct termios	term_new;

	tcgetattr(STDOUT_FILENO, &term_old);
	tcgetattr(STDOUT_FILENO, &term_new);
	term_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term_new);
	line = readline(prompt);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term_old);
	if (!line)
	{
		printf("\e[A%sexit\n", prompt);
		exit(0);
	}
	if (isemptyline(line))
		return (NULL);
	add_history(line);
	return (line);
}
