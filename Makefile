# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yususato <yususato@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 20:28:35 by yususato          #+#    #+#              #
#    Updated: 2024/05/20 20:04:54 by yususato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
INCLUDES_DIR = ./includes
BUILTIN_DIR = ./srcs/built_in
LEXER_DIR = ./srcs/lexer
PARSER_DIR = ./srcs/parser
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR)
SRCS =	./srcs/signalctrl.c \
		$(BUILTIN_DIR)/cd.c \
		$(BUILTIN_DIR)/echo.c \
		$(BUILTIN_DIR)/env_command.c \
		$(BUILTIN_DIR)/env_handler.c \
		$(BUILTIN_DIR)/export.c \
		$(BUILTIN_DIR)/pwd.c \
		$(BUILTIN_DIR)/unset.c \
		$(LEXER_DIR)/lexer.c \
		$(LEXER_DIR)/lexer_check.c \
		$(LEXER_DIR)/lexer_quote.c \
		$(LEXER_DIR)/lexer_split.c \
		$(LEXER_DIR)/lexer_token.c \
		./srcs/main.c \
		./srcs/error.c\
		$(PARSER_DIR)/parser.c  \
		$(PARSER_DIR)/parser_pipe.c \
		$(PARSER_DIR)/parser_check.c \
		$(PARSER_DIR)/parser_redirect.c \
		$(PARSER_DIR)/parser_cmd.c \
		./srcs/execute.c

		# $(PARSER_DIR)/parser_token.c \

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