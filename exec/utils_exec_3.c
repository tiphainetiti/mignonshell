/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:53:56 by ocussy            #+#    #+#             */
/*   Updated: 2025/04/24 18:48:34 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_parent(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(data->pid[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else
			data->exit_code = 1;
		if (data->outfile != STDOUT_FILENO && data->outfile != -1)
			close(data->outfile);
		if (data->infile != STDIN_FILENO && data->infile != -1)
			close(data->infile);
		i++;
	}
	if (data->exit_code != 0 && data->fd[READ_FD] != -1)
		close(data->fd[READ_FD]);
}

void	do_execve(t_data *data, char **tab)
{
	execve(data->path, data->cmd->cmd, tab);
	perror("execve");
	ft_free_tab(tab);
	data->exit_code = 127;
	exit_shell(data, 0, data->exit_code);
}

void	no_command(t_data *data)
{
	get_fd_array(data);
	free_cmd(data->cmd);
	if (data->infile != STDIN_FILENO && data->infile != -1)
		close(data->infile);
	if (data->outfile != STDOUT_FILENO && data->outfile != -1)
		close(data->outfile);
}

void	print_exit_shell(t_data *data, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (i == 2)
		ft_putstr_fd("bash: cannot allocate memory\n", 2);
	if (i == 3)
		ft_putstr_fd("bash: pipe error or child process creation\n", 2);
	if (i == 4 && errno == EACCES)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	print_exit_shell_dir(data, i);
}

void	handle_sigquit_command(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_sig = 131;
}
