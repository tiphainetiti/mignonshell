/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:48:55 by tlay              #+#    #+#             */
/*   Updated: 2025/05/06 01:14:24 by tlay             ###   ########.fr       */
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

void	handle_sigquit_command(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_sig = 131;
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

void	print_error_message(char *filename, char *error_text)
{
	char	*message;

	message = ft_strjoin3("minishell: ", filename, error_text);
	if (message)
	{
		write(2, message, ft_strlen(message));
		free(message);
	}
}
