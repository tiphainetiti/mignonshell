/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:16:27 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 16:43:07 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_sig(char *line, t_data *data, int i)
{
	if (i == 1)
		free(line);
	exit_shell(data, 0, 1);
}

char	*ft_while_gnl(char *temp, char *line, char *buffer)
{
	temp = ft_strjoin(line, buffer);
	free(line);
	free(buffer);
	line = temp;
	return (line);
}

int	init_pid(t_data *data)
{
	int	i;

	i = 0;
	data->pid = malloc(sizeof(int) * data->nb_cmd);
	if (!data->pid)
	{
		perror("malloc");
		return (1);
	}
	while (i < data->nb_cmd)
	{
		data->pid[i] = -1;
		i++;
	}
	return (0);
}

void	double_prompt_handler(int sig)
{
	(void)sig;
	g_sig = 130;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
}

void	execute_command(t_data *data, int i)
{
	if (i == (data->nb_cmd - 1))
		execute_last_command(data);
	else
		execute_command_with_pipe(data, i);
	if (data->fd[WRITE_FD] != -1)
		close(data->fd[WRITE_FD]);
	if (data->tmp_fd != -1)
		close(data->tmp_fd);
	data->tmp_fd = data->fd[READ_FD];
	if (i == data->nb_cmd - 1 && data->fd[READ_FD] != -1)
		close(data->fd[READ_FD]);
	if (data->outfile != STDOUT_FILENO && data->outfile != -1)
		close(data->outfile);
	if (data->infile != STDIN_FILENO && data->infile != -1)
		close(data->infile);
}
