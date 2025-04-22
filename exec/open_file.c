/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:01:32 by ocussy            #+#    #+#             */
/*   Updated: 2025/04/22 17:32:34 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_open(t_data *data, t_inofile *current, int fd)
{
	if (fd == -1 && errno == ENOENT && data->error_file == 0)
	{
		printf("bash: %s: No such file or directory\n", current->filename);
		data->exit_code = 1;
	}
	if (fd == -1 && errno == EISDIR && data->error_file == 0)
	{
		printf("bash: %s: Is a directory\n", current->filename);
		data->exit_code = 1;
	}
	if (fd == -1 && errno == ENOTDIR && data->error_file == 0)
	{
		printf("bash: %s: Not a directory\n", current->filename);
		data->exit_code = 1;
	}
}

int	open_input_file(t_data *data, t_inofile *current)
{
	int			fd;
	char		*filename_heredoc;
	t_limiter	*tmp;
	int			type;

	fd = 0;
	type = current->type;
	if (type == INFILE)
	{
		fd = open(current->filename, O_RDONLY);
		error_open(data, current, fd);
	}
	else if (type == HERE_DOC && data->limiter != NULL)
	{
		tmp = data->limiter;
		filename_heredoc = ft_init_file(data);
		fd = open(filename_heredoc, O_RDONLY);
		unlink(filename_heredoc);
		free(filename_heredoc);
		data->limiter = data->limiter->next;
		free_limiter(tmp);
	}
	if (g_sig == 666)
		close(fd);
	return (fd);
}

int	open_output_file(t_data *data, t_inofile *current)
{
	int	fd;
	int	type;

	type = current->type;
	if (type == OUTFILE)
	{
		fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		error_open(data, current, fd);
	}
	else if (type == APPEND)
	{
		fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		error_open(data, current, fd);
	}
	else
		fd = -1;
	return (fd);
}
