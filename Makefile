# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 20:28:35 by yususato          #+#    #+#              #
#    Updated: 2024/05/30 13:26:02 by hmiyazak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./minishell
CC = cc
INCLUDES_DIR = ./includes
BUILTIN_DIR = ./srcs/built_in
EXECUTE_DIR = ./srcs/execute
UTILS_DIR = ./srcs/utils
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR)
SRCS =	$(BUILTIN_DIR)/cd.c \
		$(BUILTIN_DIR)/echo.c \
		$(BUILTIN_DIR)/env_command.c \
		$(BUILTIN_DIR)/env_handler.c \
		$(BUILTIN_DIR)/export.c \
		$(BUILTIN_DIR)/pwd.c \
		$(BUILTIN_DIR)/unset.c \
		$(EXECUTE_DIR)/execute.c \
		$(EXECUTE_DIR)/execute_cmd.c \
		$(EXECUTE_DIR)/execute_redirect.c \
		$(UTILS_DIR)/handle_status.c \
		$(UTILS_DIR)/is_equal.c \
		$(UTILS_DIR)/put_error_exit.c \
		$(UTILS_DIR)/sigexit.c \
		$(UTILS_DIR)/free_env.c \
		$(UTILS_DIR)/paths.c \
		./srcs/signalctrl.c \
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