/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:58:04 by ocussy            #+#    #+#             */
/*   Updated: 2025/05/02 17:38:45 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_shell(t_data *data, int i, int j)
{
	g_sig = 0;
	if (data->envt)
		delete_envt(&(data->envt));
	if (data->export)
		delete_export(&(data->export));
	print_exit_shell(data, i);
	data->exit_code = j;
	if (data->cmd != NULL)
		free_cmd_list(&data->cmd);
	if (data->tmp_fd != -1)
		close(data->tmp_fd);
	if (data->path != NULL)
		free(data->path);
	free_limiter_list(&data->limiter);
	free(data->pid);
	exit(data->exit_code);
}

void	callexecve(t_data *data)
{
	char	**tab;

	if (g_sig == 666)
		exit_shell(data, 0, data->exit_code);
	check_dir_error(data);
	// Pour "$HOMEdskjhfkdshfsd"
	if (data->cmd->was_quoted && (data->cmd->cmd[0] == NULL
			|| data->cmd->cmd[0][0] == '\0'))
		exit_shell(data, 1, 127);
	if (parsing_builtin(data) == 0 && data->cmd->cmd[0] != NULL)
	{
		get_path(data);
		if (data->path == NULL)
			exit_shell(data, 1, 127);
		tab = make_env_tab(data->envt);
		if (tab == NULL)
			exit_shell(data, 0, 1);
		if (parsing_builtin(data) == 0)
			do_execve(data, tab);
		else
			exit_shell(data, 0, data->exit_code);
	}
	else
		exit_shell(data, 0, data->exit_code);
}

void	setup_and_execute_command(t_data *data)
{
	data->pid[0] = fork();
	if (data->pid[0] == -1)
		exit_shell(data, 0, 1);
	else if (data->pid[0] == 0)
	{
		if (g_sig == 131)
			exit_shell(data, 0, 131);
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
		callexecve(data);
	}
	else
		wait_parent(data);
}

void	make_one_command(t_data *data)
{
	if (data->cmd->cmd[0] == NULL && data->cmd->nb_file >= 1)
	{
		no_command(data);
		return ;
	}
	if (data->cmd->nb_file >= 1)
		get_fd_array(data);
	if (g_sig == 666)
		data->exit_code = 130;
	else if (parsing_builtin(data) == 0)
		setup_and_execute_command(data);
	if (data->cmd != NULL)
		free_cmd_list(&data->cmd);
	if (data->infile != STDIN_FILENO && data->infile != -1)
		close(data->infile);
	if (data->outfile != STDOUT_FILENO && data->outfile != -1)
		close(data->outfile);
	return ;
}

void	exec(t_data *data)
{
	if (init_pid(data) == 1)
		return ;
	if (data->nb_cmd == 0)
	{
		if (data->cmd->nb_file >= 1)
			get_fd_array(data);
	}
	if (data->nb_cmd >= 1)
	{
		handle_signal(2);
		if (data->nb_cmd == 1)
			make_one_command(data);
		else
			make_command_pipe(data);
	}
	else
		free_cmd_list(&data->cmd);
	if (g_sig == 130)
	{
		data->exit_code = 130;
		g_sig = 0;
	}
	if (g_sig == 131)
		data->exit_code = 131;
}
