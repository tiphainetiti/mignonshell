/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:27:57 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:43:34 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>
#include <unistd.h>

int	execute_builtin_command(t_data *data, char *cmd)
{
	int	tmp;
	int	ret;

	ret = 1;
	tmp = dup(STDOUT_FILENO);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "/bin/echo") == 0)
		execute_echo(data);
	else if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "/bin/pwd") == 0)
		execute_pwd(data);
	else if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "/bin/env") == 0)
		execute_env(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		execute_exit(data, tmp);
	else if (ft_strcmp(cmd, "export") == 0)
		execute_export(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		execute_cd(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		execute_unset(data);
	else
		ret = 0;
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	return (ret);
}

void	handle_fd_builtin(t_data *data)
{
	if (data->infile != STDIN_FILENO && data->infile != -1)
		close(data->infile);
	if (data->outfile != STDOUT_FILENO && data->outfile != -1)
		close(data->outfile);
	if (data->fd[READ_FD] != -1)
	{
		close(data->fd[READ_FD]);
		data->fd[READ_FD] = -1;
	}
	if (data->fd[WRITE_FD] != -1)
	{
		close(data->fd[WRITE_FD]);
		data->fd[WRITE_FD] = -1;
	}
}

int	parsing_builtin(t_data *data)
{
	char	*cmd;

	cmd = data->cmd->cmd[0];
	if (cmd != NULL)
	{
		if (data->infile == -1)
			return (0);
		if (execute_builtin_command(data, cmd) == 1)
		{
			handle_fd_builtin(data);
			return (1);
		}
	}
	return (0);
}
