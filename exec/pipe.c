/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:56:53 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:47:44 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child(t_data *data, int i)
{
	close(data->fd[READ_FD]);
	if (i != 0)
		dup2(data->tmp_fd, STDIN_FILENO);
	if (data->tmp_fd != -1)
		close(data->tmp_fd);
	if (data->infile != STDIN_FILENO)
	{
		if (data->infile == -1)
			exit_shell(data, 4, 1);
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	if (data->outfile != STDOUT_FILENO)
	{
		if (data->outfile == -1)
			exit_shell(data, 4, 1);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
	else
		dup2(data->fd[WRITE_FD], STDOUT_FILENO);
	close(data->fd[WRITE_FD]);
	callexecve(data);
}

void	setup_fds(t_data *data)
{
	if (data->infile != STDIN_FILENO)
	{
		if (data->infile == -1)
			exit_shell(data, 4, 1);
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	if (data->outfile != STDOUT_FILENO)
	{
		if (data->outfile == -1)
			exit_shell(data, 4, 1);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
}

void	execute_last_command(t_data *data)
{
	if (data->cmd->nb_file >= 1)
		get_fd_array(data);
	data->pid[data->nb_cmd - 1] = fork();
	if (data->pid[data->nb_cmd - 1] == -1)
		exit_shell(data, 0, 1);
	else if (data->pid[data->nb_cmd - 1] == 0)
	{
		handle_signal(2);
		dup2(data->tmp_fd, STDIN_FILENO);
		close(data->tmp_fd);
		setup_fds(data);
		if (g_sig != 666)
			callexecve(data);
		exit_shell(data, 0, data->exit_code);
	}
}

void	execute_command_with_pipe(t_data *data, int i)
{
	if (data->cmd->nb_file >= 1)
		get_fd_array(data);
	if (pipe(data->fd) == -1)
		exit_shell(data, 3, 1);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		exit_shell(data, 3, 1);
	else if (data->pid[i] == 0)
	{
		handle_signal(2);
		if (data->exit_code == 130)
			exit_shell(data, 0, 130);
		if (g_sig != 666)
			child(data, i);
		close(data->fd[READ_FD]);
		close(data->fd[WRITE_FD]);
		exit_shell(data, 0, data->exit_code);
	}
}

void	make_command_pipe(t_data *data)
{
	int		i;
	t_cmd	*current;
	t_cmd	*next_cmd;

	i = 0;
	data->tmp_fd = dup(STDIN_FILENO);
	current = data->cmd;
	while (i < data->nb_cmd)
	{
		next_cmd = current->next;
		data->cmd = current;
		handle_signal(2);
		data->infile = STDIN_FILENO;
		data->outfile = STDOUT_FILENO;
		execute_command(data, i);
		free_cmd(current);
		current = next_cmd;
		i++;
		data->cmd = data->cmd->next;
	}
	data->cmd = NULL;
	wait_parent(data);
}
