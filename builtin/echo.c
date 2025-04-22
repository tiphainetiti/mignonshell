/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:42:49 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:42:39 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	contains_special_char(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\x01')
			{
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	write_echo_output(t_data *data, int start, int option)
{
	int		i;
	char	**cmd;

	cmd = data->cmd->cmd;
	if (contains_special_char(cmd))
	{
		restore_spaces(cmd);
	}
	i = start;
	while (data->cmd->cmd[i])
	{
		write(STDOUT_FILENO, data->cmd->cmd[i], ft_strlen(data->cmd->cmd[i]));
		if (errno == ENOSPC)
		{
			write(2, "bash: echo: write error: No space left on device\n", 50);
			data->exit_code = 2;
			return ;
		}
		i++;
		if (data->cmd->cmd[i] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (option == 1)
		write(STDOUT_FILENO, "\n", 1);
	data->exit_code = 0;
}

int	find_option(char *cmd)
{
	int	i;

	i = 0;
	if (cmd != NULL)
	{
		while (ft_strncmp(cmd + i, "-", 1) == 0)
			i++;
		if (i != 1)
			return (1);
		while (ft_strncmp(cmd + i, "n", 1) == 0)
			i++;
		if (i != (int)ft_strlen(cmd))
			return (1);
		else
			return (0);
	}
	else
		return (1);
}

void	make_echo(t_data *data)
{
	int	i;
	int	option;

	i = 1;
	if (ft_size_tab(data->cmd->cmd) == 1)
	{
		if (write(STDOUT_FILENO, "\n", 1) < 0)
		{
			write(2, "bash: echo: write error: No space left on device\n", 50);
			data->exit_code = 2;
		}
		return ;
	}
	while (find_option(data->cmd->cmd[i]) == 0)
		i++;
	option = i;
	write_echo_output(data, i, option);
}

void	execute_echo(t_data *data)
{
	if (data->outfile != STDOUT_FILENO)
	{
		if (data->outfile == -1)
		{
			print_exit_shell(data, 4);
			return ;
		}
		if (dup2(data->outfile, STDOUT_FILENO))
			close(data->outfile);
	}
	if (g_sig == 1)
	{
		data->exit_code = 130;
		g_sig = 0;
	}
	make_echo(data);
}
