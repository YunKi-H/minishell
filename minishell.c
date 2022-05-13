/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:30:42 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/10 10:32:09 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cc minishell.c -lreadline -L/opt/homebrew/Cellar/readline

#include <unistd.h>
//fork, getcwd, chdir, unlink, execve, dup, dup2, pipe
//isatty, ttyname, ttyslot
#include <stdlib.h>
//malloc, free, getenv
#include <stdio.h>
//printf, stderror
#include <signal.h>
//signal, kill
#include <fcntl.h>
//write, open, read, close
#include <dirent.h>
//opendir, readdir, closedir
#include <errno.h>
//errno
#include <termios.h>
//tcsetattr, tcgetattr, tgetent
#include <term.h>
//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <sys/wait.h>
//wait, waitpid, wait3, wait4
#include <sys/stat.h>
//stat, lstat, fstat
#include <sys/ioctl.h>
//ioctl
#include <readline/readline.h>
//readline, rl_on_new_line, rl_replace_line, rl_redisplay
#include <readline/history.h>
//add_history

int main(int argc, char **argv, char **envp)
{
	// char *tmp = readline("CuteShell S2 % ");
	// printf("GET! : %s\n", tmp);

	// char *arg[3];
	// arg[0] = "ls";
	// arg[1] = "-al";
	// arg[2] = NULL;
	// execve("/bin/ls", arg, envp);
	for (int i = 0; envp[i]; i++)
	{
		printf("mem : %p , env : %s\n", envp[i], envp[i]);
	}
}
