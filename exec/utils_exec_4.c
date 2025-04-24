/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:48:55 by tlay              #+#    #+#             */
/*   Updated: 2025/04/24 17:54:33 by tlay             ###   ########.fr       */
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

void	print_exit_shell_dir(t_data *data, int i)
{
	if (i == 5)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->cmd[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	if (i == 6)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
