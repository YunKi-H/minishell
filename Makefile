# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 11:39:56 by yuhwang           #+#    #+#              #
#    Updated: 2022/05/13 11:47:29 by yuhwang          ###   ########.fr        #
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

OBJS		=	$(SRCS:.c=.o)

$(NAME)		:	$(OBJS)
				$(MAKE) bonus -C $(LIBFTDIR)
				$(CC) -o $@ $^ $(LIBFTDIR)/$(LIBFTFILE) $(READLINE)

all			:	$(NAME)

%.o			:	%.c
				$(CC) $(CFLAGS) -o $@ -c $< -I.

clean		:
				$(MAKE) -C $(LIBFTDIR) clean
				$(RM) $(OBJS)

fclean		:	clean
				$(MAKE) -C $(LIBFTDIR) fclean
				$(RM) $(NAME)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean fclean re
