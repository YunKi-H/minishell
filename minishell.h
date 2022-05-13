/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:39:15 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/13 11:47:17 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../libft/libft.h"
