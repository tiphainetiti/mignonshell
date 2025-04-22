/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:45:24 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:42:52 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_pwd_args(t_data *data)
{
	if (data->cmd->cmd[1] != NULL)
	{
		if (ft_strncmp(data->cmd->cmd[1], "-", 1) == 0
			&& (int)ft_strlen(data->cmd->cmd[1]) > 1)
		{
			printf("bash: %s: invalid option\n", data->cmd->cmd[1]);
			data->exit_code = 2;
			return (0);
		}
	}
	return (1);
}

void	get_pwd(t_data *data)
{
	char	*pwd;

	if (!validate_pwd_args(data))
		return ;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("Cannot get current working directory path\n", 2);
		data->exit_code = 127;
	}
	else
	{
		ft_putstr(pwd);
		write(1, "\n", 1);
		data->exit_code = 0;
		free(pwd);
	}
}

void	execute_pwd(t_data *data)
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
	get_pwd(data);
}
