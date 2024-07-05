/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 22:23:59 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_redirected_fds(int *file_io);

void	execute_redirect(t_parser *cmd, t_env **env, char **paths, bool set_st)
{
	int	std_io[2];
	int	file_io[2];

	file_io[0] = 0;
	file_io[1] = 1;
	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths, set_st));
	if (save_io(&std_io[0]) < 0)
		return ;
	heredoc_loop(cmd->file, env);
	if (cmd->cmd == NULL)
		return ;
	if (redirect_stream(cmd->file, &file_io[0]) < 0)
		return (close_redirected_fds(&file_io[0]));
	execute_cmd(cmd->cmd, env, paths, set_st);
	get_back_io(&std_io[0]);
	close_redirected_fds(&file_io[0]);
}

static void	close_redirected_fds(int *file_io)
{
	if (file_io == NULL)
		return ;
	if (file_io[0] != 0)
		close(file_io[0]);
	if (file_io[1] != 1)
		close(file_io[1]);
}
