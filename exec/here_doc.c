/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:11:02 by ocussy            #+#    #+#             */
/*   Updated: 2025/05/02 18:54:25 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	g_sig = 666;
}

static void	process_heredoc_line(char *line, int file)
{
	write(file, line, ft_strlen(line));
	write(file, "\n", 1);
	free(line);
}

void	ft_make_file(t_data *data, int file)
{
	char	*line;

	data->tmp_heredoc = dup(STDIN_FILENO);
	handle_signal(1);
	g_sig = 0;
	while (g_sig != 666)
	{
		if (g_sig != 666)
			line = readline("> ");
		if (!line || g_sig == 666)
		{
			if (line)
				free(line);
			break ;
		}
		if (data->limiter->str && ft_strcmp(line, data->limiter->str) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, file);
	}
	dup2(data->tmp_heredoc, STDIN_FILENO);
	close(data->tmp_heredoc);
}

void	ft_process_file(t_data *data, int file)
{
	if (file != -1)
	{
		ft_make_file(data, file);
		if (close(file) == -1)
		{
			ft_putstr_fd("Erreur lors de la fermeture du fichier.\n", 2);
			data->exit_code = 1;
		}
	}
}

char	*ft_init_file(t_data *data)
{
	char	*filename;
	int		file;

	file = ft_open_file(data, &filename);
	ft_process_file(data, file);
	return (filename);
}
