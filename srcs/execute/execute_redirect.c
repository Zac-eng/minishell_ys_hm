/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/07 21:39:22 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redirect(t_parser *cmd, t_env **env, char **paths, bool set_st)
{
	int	std_io[2];

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths, set_st));
	if (save_io(&std_io[0]) < 0)
		return ;
	if (heredoc_loop(cmd->file, env) == false)
		return ;
	if (cmd->cmd == NULL)
		return ;
	if (redirect_stream(cmd->file) < 0)
	{
		get_back_io(&std_io[0]);
		return ;
	}
	execute_cmd(cmd->cmd, env, paths, set_st);
	get_back_io(&std_io[0]);
}
