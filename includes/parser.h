/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:48:09 by yususato          #+#    #+#             */
/*   Updated: 2024/03/12 19:38:31 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_redirect_type
{
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}						t_redirect_type;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	t_file				*next;
}						t_file;

typedef struct s_parser
{
	char				**cmd;
	t_file				*file;
	t_parser			*next;
	t_parser			*prev;
}						t_parser;

#endif
