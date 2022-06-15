/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:39:15 by yuhwang           #+#    #+#             */
/*   Updated: 2022/06/15 17:54:29 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
// fork, getcwd, chdir, unlink, execve, dup, dup2, pipe
// isatty, ttyname, ttyslot
# include <stdlib.h>
// malloc, free, getenv
# include <stdio.h>
// printf
# include <string.h>
// strerror
# include <signal.h>
// signal, kill
# include <fcntl.h>
// write, open, read, close
# include <dirent.h>
// opendir, readdir, closedir
# include <errno.h>
// errno
# include <termios.h>
// tcsetattr, tcgetattr, tgetent
# include <term.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/wait.h>
// wait, waitpid, wait3, wait4
# include <sys/stat.h>
// stat, lstat, fstat
# include <sys/ioctl.h>
// ioctl
# include <readline/readline.h>
// readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>
// add_history
# include "../libft/libft.h"
# include "buffer.h"

enum e_bool
{
	FALSE,
	TRUE
};

enum e_flag
{
	SINGLE_Q = 1,
	DOUBLE_Q = 2
};

enum e_syntax
{
	INDEX = 0,
	FLAG_Q = 1,
	PIPE = 2,
	REDIR = 3
};

enum e_type
{
	ARG			=	0b00000000,
	CMD			=	0b00000001,
	FILENAME	=	0b00000010,
	REDIRECT	=	0b00000100
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
	int		sh_error;
};

struct s_table
{
	void	*head;
	int		size;
};

struct s_cmdline
{
	t_table				*tokens;
	int					input;
	int					output;
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
t_cmdline	*init_cmdl(t_table *tokens);
t_table		*init_envt(char **envp);
t_env		*init_env(const char *key, const char *value);
// free
void		free_cmdt(t_table *cmdt);
void		free_tokens(t_table *tokens);
void		free_args(char **args);
// struct
void		env_add_back(t_table *envt, char *env);
void		cmdl_add_back(t_table *cmdt, t_cmdline *cmdl);
void		token_add_back(t_table *tokens, char *token, int type);
t_token		*find_cmd(t_cmdline *cmdl);
t_token		*find_next_arg(t_token *token);
// parse
int			parsing(char *readline, t_sh *sh);
char		*replace_env(char *cmdline, t_sh *sh);
t_table		*tokenize(char *line);
t_table		*remove_quote(t_table *tokens);
// execute
char		*get_path(t_cmdline *cmdl, t_sh *sh);
int			excutor(t_sh *sh, t_cmdline *cmdl);
int			run_builtin(t_sh *sh, t_cmdline *cmdl);
int			run_cmd(t_sh *sh);
// bool
int			isifs(char c);
int			iskey(char c);
int			isredirect(char *line, int i);
int			isopt_echo(char *token);
int			isvalid_key(char *key);
int			isnum(char *token);
int			isemptyline(char *line);
int			isbuiltin(t_cmdline *cmdl);
// utils
void		handler_default(int sig);
void		handler_heredoc(int sig);
void		handler_heredoc_p(int sig);
void		handler_temp(int sig);
void		handler_nothing(int sig);
void		ft_signal(void (*handler)(int));
void		toggle_flag_quote(char c, int *flag);
t_env		*_getenv(char *key, t_table *envt);
char		*ft_readline(const char *prompt);
// linked list -> char **
char		**envttoevnp(t_table *envt);
char		**cmdltocmdp(t_table *tokens);
// builtins
int			ft_echo(t_cmdline *cmdl);
int			ft_env(t_table *envt);
int			ft_pwd(void);
int			ft_export(t_sh *sh, t_cmdline *cmdl);
int			ft_unset(t_sh *sh, t_cmdline *cmdl);
int			ft_cd(t_sh *sh, t_cmdline *cmdl);
int			ft_exit(t_sh *sh, t_cmdline *cmdl);
// redirection
int			redirection_set(t_sh *sh, t_cmdline *cmdl);
void		redir_input(t_sh *sh, t_cmdline *cmdl, t_token *token);
void		redir_output(t_sh *sh, t_cmdline *cmdl, t_token *token);
void		redir_append(t_sh *sh, t_cmdline *cmdl, t_token *token);
void		redir_heredoc(t_sh *sh, t_cmdline *cmdl, char *delimeter);
// pipe
void		ft_pipe(int *fd);
void		init_pipe(int *p_old);
void		set_child_pipe(t_cmdline *cmdl, int *old, int *new, int isend);
void		set_parent_pipe(int *p_old, int *p_new, int isend, t_cmdline *cmdl);
// err
void		ft_err(int errnbr);
int			check_syn_err(char *line);
void		cmd_not_found(t_cmdline *cmdl);
int			check_redir_err(t_table *cmdt, t_sh *sh);
void		print_err(char *s1, char *s2, char *s3);

#endif
