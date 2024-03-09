/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/03/09 11:35:24 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"

typedef enum e_token
{
	PIPE,
	SPASE,
	S_QUOTE,
	D_QUOTE,
	STR
}						t_token;

typedef struct s_node
{
	int				data;
	struct s_node	*prev;
	struct s_node	*next;
	char			*str;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		current;
}	t_stack;

void	signalctrl(void);
char	*ft_strtrim(char const *s1, char const *set);
char	*split_quote(t_stack *lexer, char *line);
char	*split_normal(t_stack *lexer, char *line);
char	*split_line(t_stack *lexer, char *line);
t_stack	lexer(char *line);
t_stack	*create_stack(void);
void	push(t_stack *stack, char *i, int type);
int		pop(t_stack *stack);

#endif