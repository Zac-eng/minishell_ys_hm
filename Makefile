# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 20:28:35 by yususato          #+#    #+#              #
#    Updated: 2024/04/29 01:01:25 by hmiyazak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
INCLUDES_DIR = ./includes
BUILTIN_DIR = ./srcs/built_in
LP_DIR = ./srcs/lexer_parser
CFLAGS = -I$(INCLUDES_DIR)
#CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR)
SRCS =	./srcs/signalctrl.c \
		$(BUILTIN_DIR)/cd.c \
		$(BUILTIN_DIR)/echo.c \
		$(BUILTIN_DIR)/env.c \
		$(BUILTIN_DIR)/export.c \
		$(BUILTIN_DIR)/pwd.c \
		$(BUILTIN_DIR)/unset.c \
		$(LP_DIR)/lexer.c \
		./srcs/execute.c \
		./srcs/main.c
		

OBJS = $(SRCS:%.c=%.o)

LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBDIR)

clean:
	$(MAKE) clean -C $(LIBDIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re