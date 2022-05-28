# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 11:39:56 by yuhwang           #+#    #+#              #
#    Updated: 2022/05/28 14:44:38 by yuhwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFTDIR	=	../libft
LIBFTFILE	=	libft.a
READLINE	=	-lreadline -L/opt/homebrew/Cellar/readline

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

SRCS		=	minishell.c	\
				buffer.c	\
				cd.c		\
				echo.c		\
				env.c		\
				exit.c		\
				export.c	\
				pwd.c		\
				unset.c		\

OBJS		=	$(SRCS:.c=.o)

$(NAME)		:	$(OBJS)
				$(MAKE) bonus -C $(LIBFTDIR)
				$(CC) $(CFLAGS) -o $@ $^ $(LIBFTDIR)/$(LIBFTFILE) $(READLINE)

all			:	$(NAME)

%.o			:	%.c
				$(CC) $(CFLAGS) -o $@ -c $< -I.

clean		:
				$(MAKE) -C $(LIBFTDIR) clean
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME) $(LIBFTDIR)/$(LIBFTFILE)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean fclean re
