/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inofile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:44:45 by ocussy            #+#    #+#             */
/*   Updated: 2025/04/22 17:32:13 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_inofile(t_data *data, t_inofile *current, int fd)
{
	if (data->error_file == 0)
	{
		if (current->type == INFILE || current->type == HERE_DOC)
			data->infile = fd;
		if (current->type == OUTFILE || current->type == APPEND)
			data->outfile = fd;
	}
	if (fd == -1 && errno == EACCES)
		data->file_name = current->filename;
}

int	*get_inofile(t_data *data, t_cmd *cmd, int *fd_array)
{
	int			i;
	t_inofile	*current;
	int			nb_file;

	i = 0;
	current = cmd->file;
	nb_file = cmd->nb_file;
	while (i < nb_file)
	{
		if (current->type == INFILE || current->type == HERE_DOC)
			fd_array[i] = open_input_file(data, current);
		else if (current->type == OUTFILE || current->type == APPEND)
			fd_array[i] = open_output_file(data, current);
		save_inofile(data, current, fd_array[i]);
		if (fd_array[i] == -1)
			data->error_file = 1;
		if (errno == EACCES || errno == ENOENT || g_sig == 666)
			break ;
		i++;
		current = current->next;
	}
	fd_array[i] = -1;
	fd_array[i + 1] = 0;
	return (fd_array);
}

void	close_fd(t_data *data, int *fd_array)
{
	int	i;

	i = 0;
	while (fd_array[i] != -1)
	{
		if (fd_array[i] != data->infile && fd_array[i] != data->outfile)
			close(fd_array[i]);
		i++;
	}
	if (fd_array[ft_size_tab_int(fd_array) + 1] != 0)
	{
		i = 0;
		while (fd_array[i])
		{
			if (fd_array[i] != -1)
				close(fd_array[i]);
			i++;
		}
	}
}

void	get_fd_array(t_data *data)
{
	int	*fd_array;

	fd_array = malloc(sizeof(int) * (data->cmd->nb_file + 2));
	if (!fd_array)
		exit_shell(data, 2, 1);
	data->error_file = 0;
	fd_array = get_inofile(data, data->cmd, fd_array);
	if (ft_size_tab_int(fd_array) != (data->cmd->nb_file))
	{
		close_fd(data, fd_array);
		free(fd_array);
		data->exit_code = 1;
		return ;
	}
	close_fd(data, fd_array);
	free(fd_array);
}
