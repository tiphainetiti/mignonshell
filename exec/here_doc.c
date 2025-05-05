/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:11:02 by ocussy            #+#    #+#             */
/*   Updated: 2025/05/06 00:51:23 by tlay             ###   ########.fr       */
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

static void	handle_eof_heredoc(t_data *data)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file",
		2);
	ft_putstr_fd(" (wanted `", 2);
	if (data->limiter && data->limiter->str)
		ft_putstr_fd(data->limiter->str, 2);
	ft_putstr_fd("')\n", 2);
	data->exit_code = 0;
}

static int	check_line_status(t_data *data, char *line)
{
	if (!line && g_sig != 666)
	{
		handle_eof_heredoc(data);
		return (1);
	}
	else if (!line || g_sig == 666)
	{
		if (line)
			free(line);
		return (1);
	}
	return (0);
}

void	ft_make_file(t_data *data, int file)
{
	char	*line;

	line = NULL;
	data->tmp_heredoc = dup(STDIN_FILENO);
	handle_signal(1);
	g_sig = 0;
	while (g_sig != 666)
	{
		if (g_sig != 666)
			line = readline("> ");
		if (check_line_status(data, line))
			break ;
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
