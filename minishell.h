/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:39:15 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/17 14:54:12 by yuhwang          ###   ########.fr       */
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
#include <stdbool.h>
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

typedef struct s_cmdline t_cmdline;
typedef struct s_cmdtable t_cmdtable;
typedef struct s_env t_env;
typedef struct s_envtable t_envtable;

struct s_cmdtable
{
	t_cmdline	*head;
	size_t		size;
};

struct s_cmdline
{
	char				**tokens;
	bool				*redirect;
	struct s_cmdline	*next;
};

struct s_envtable
{
	t_env	*head;
};

struct s_env
{
	const char		*key;
	const char		*value;
	struct s_env	*next;
};

typedef struct s_sh
{
	t_cmdtable	*cmdt;
	t_envtable	*envt;
}	t_sh;

int			parsing(char *line, t_cmdtable *cmdt);

t_sh		*init_sh(char **envp);
t_cmdtable	*init_cmdt();
t_cmdline	*init_cmdl();
t_envtable	*init_envt(char **envp);
t_env		*init_env(const char *key, const char *value);

void	env_add_back(t_envtable *envt, char *env);















//builtins
void	parse(char *line, t_sh *shell);
int		pwd();
int		echo(const char **parsed);
int		cd(const char **parsed);
int		env(const char **env);
