# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 20:28:35 by yususato          #+#    #+#              #
#    Updated: 2024/06/10 20:07:19 by hmiyazak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
INCLUDES_DIR = ./includes
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR)
BUILTIN_DIR = ./srcs/built_in
EXECUTE_DIR = ./srcs/execute
LEXER_DIR = ./srcs/lexer
PARSER_DIR = ./srcs/parser
UTILS_DIR = ./srcs/utils
SRCS =	$(BUILTIN_DIR)/env/env_constructor.c \
		$(BUILTIN_DIR)/env//env_converter.c \
		$(BUILTIN_DIR)/env//env_handler.c \
		$(BUILTIN_DIR)/env/env.c \
		$(BUILTIN_DIR)/cd.c \
		$(BUILTIN_DIR)/echo.c \
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
		$(LEXER_DIR)/lexer.c \
		$(LEXER_DIR)/lexer_check.c \
		$(LEXER_DIR)/lexer_quote.c \
		$(LEXER_DIR)/lexer_split.c \
		$(LEXER_DIR)/lexer_token.c \
		$(PARSER_DIR)/parser.c \
		$(PARSER_DIR)/parser_cmd.c \
		$(PARSER_DIR)/parser_pipe.c \
		$(PARSER_DIR)/parser_redirect.c \
		$(PARSER_DIR)/parser_check.c \
		./srcs/signalctrl.c \
		./srcs/main.c \

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