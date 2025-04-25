/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:48:55 by tlay              #+#    #+#             */
/*   Updated: 2025/04/25 15:57:02 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dir_error(t_data *data)
{
	int			path_len;
	struct stat	path_stat;

	if (data->cmd->cmd[0] != NULL)
	{
		if (stat(data->cmd->cmd[0], &path_stat) == 0
			&& S_ISDIR(path_stat.st_mode))
			exit_shell(data, 5, 126);
		path_len = ft_strlen(data->cmd->cmd[0]);
		if (path_len > 1 && data->cmd->cmd[0][path_len - 1] == '/')
			exit_shell(data, 6, 126);
	}
}

void	handle_sigquit_command(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_sig = 131;
}
