# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 11:39:56 by yuhwang           #+#    #+#              #
#    Updated: 2022/06/15 16:18:26 by yuhwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
RM			=	rm -f

LIBFTDIR	=	../libft
LIBFTFILE	=	libft.a

READLINE	=	-lreadline
LDFLAGS		=	-L/opt/homebrew/opt/readline/lib
CPPFLAGS	=	-I/opt/homebrew/opt/readline/include

SRCS		=	minishell.c		\
				parse.c			\
				execute.c		\
				buffer.c		\
				bool.c			\
				cd.c			\
				echo.c			\
				env.c			\
				exit.c			\
				export.c		\
				pwd.c			\
				unset.c			\
				handler.c		\
				init.c			\
				free.c			\
				ttop.c			\
				node_add_back.c	\
				get_arg.c		\
				ft_readline.c	\
				redirection.c	\
				pipe.c			\
				tokenize.c		\
				replace_env.c	\
				remove_quote.c	\
				error.c			\

OBJS		=	$(SRCS:.c=.o)

$(NAME)		:	$(OBJS)
				$(MAKE) bonus -C $(LIBFTDIR)
				$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $(READLINE) -o $@ $^ $(LIBFTDIR)/$(LIBFTFILE)

all			:	$(NAME)

%.o			:	%.c
				$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

clean		:
				$(MAKE) -C $(LIBFTDIR) fclean
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean fclean re
