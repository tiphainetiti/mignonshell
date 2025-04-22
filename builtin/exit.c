/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:02:42 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:42:46 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	ft_natoi(t_data *data, const char *nptr)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	data->lst_char_split = nptr[i];
	return (result * sign);
}

int	check_overflow(t_data *data, char *str)
{
	if (str[0] == '-')
	{
		if (ft_strlen(str) > 20 || ft_strcmp(str, "-9223372036854775808") > 0)
		{
			write(2, "bash: exit: ", 12);
			ft_putstr_fd(str, 2);
			write(2, ": numeric argument required\n", 29);
			data->exit_code = 2;
			return (1);
		}
	}
	else
	{
		if (ft_strlen(str) > 19 || ft_strcmp(str, "9223372036854775807") > 0)
		{
			write(2, "check overflow exit\nbash: exit: ", 33);
			ft_putstr_fd(str, 2);
			write(2, ": numeric argument required\n", 29);
			data->exit_code = 2;
			return (1);
		}
	}
	return (0);
}

int	handle_exit_code(t_data *data, int tmp)
{
	if (ft_size_tab(data->cmd->cmd) > 2)
	{
		write(2, "exit\nbash: exit: too many arguments\n", 37);
		data->exit_code = 1;
		return (1);
	}
	data->exit_code = ft_natoi(data, data->cmd->cmd[1]) % 256;
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	write(1, "exit\n", 6);
	exit_shell(data, 0, data->exit_code);
	return (0);
}

void	make_exit(t_data *data, int tmp)
{
	if (ft_size_tab(data->cmd->cmd) > 1)
	{
		if ((ft_natoi(data, data->cmd->cmd[1]) == 0
				&& ft_strcmp(data->cmd->cmd[1], "0") != 0)
			|| data->lst_char_split != 0)
		{
			write(2, "exit\nbash: exit: ", 18);
			ft_putstr_fd(data->cmd->cmd[1], 2);
			write(2, ": numeric argument required\n", 29);
			dup2(tmp, STDOUT_FILENO);
			close(tmp);
			exit_shell(data, 0, 2);
		}
		if (check_overflow(data, data->cmd->cmd[1]) == 1)
		{
			close(tmp);
			exit_shell(data, 0, data->exit_code);
		}
		if (handle_exit_code(data, tmp) == 1)
			return ;
	}
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	write(1, "exit\n", 6);
	exit_shell(data, 0, data->exit_code);
}

void	execute_exit(t_data *data, int tmp)
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
	make_exit(data, tmp);
}
