/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:39:15 by yuhwang           #+#    #+#             */
/*   Updated: 2022/05/17 19:55:11 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
//fork, getcwd, chdir, unlink, execve, dup, dup2, pipe
//isatty, ttyname, ttyslot
# include <stdlib.h>
//malloc, free, getenv
# include <stdio.h>
//printf, stderror
# include <signal.h>
//signal, kill
# include <fcntl.h>
//write, open, read, close
# include <dirent.h>
//opendir, readdir, closedir
# include <errno.h>
//errno
# include <termios.h>
//tcsetattr, tcgetattr, tgetent
# include <term.h>
//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/wait.h>
//wait, waitpid, wait3, wait4
# include <sys/stat.h>
//stat, lstat, fstat
# include <sys/ioctl.h>
//ioctl
# include <readline/readline.h>
//readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>
//add_history
# include "../libft/libft.h"

enum e_bool
{
	FALSE,
	TRUE
};

typedef struct s_sh			t_sh;
typedef struct s_table		t_table;
typedef struct s_cmdline	t_cmdline;
typedef struct s_token		t_token;
typedef struct s_env		t_env;

struct s_sh
{
	t_table	*cmdt;
	t_table	*envt;
};

struct s_table
{
	void	*head;
};

struct s_cmdline
{
	t_table				*tokens;
	struct s_cmdline	*next;
};

struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
};

struct s_env
{
	const char		*key;
	const char		*value;
	struct s_env	*next;
};

// init
t_sh		*init_sh(char **envp);
t_table		*init_table(void);
t_cmdline	*init_cmdl(void);
t_table		*init_envt(char **envp);
t_env		*init_env(const char *key, const char *value);
// free
void		free_cmdt(t_table *cmdt);
void		free_tokens(t_table *tokens);
// struct
void		env_add_back(t_table *envt, char *env);
void		cmdl_add_back(t_table *cmdt, t_cmdline *cmdl);
// parse
int			parsing(char *line, t_table *cmdt);
int			isifs(char c);

#endif
