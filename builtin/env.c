/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:58:17 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:42:43 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_command_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (ft_strcmp(path[i], "/usr/bin/env") == 0 || ft_strcmp(path[i],
				"/bin/env") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	find_env_command_path(t_data *data)
{
	char	**path;
	int		index;

	path = get_all_path(data, data->envt, "env");
	if (!path)
	{
		data->exit_code = 127;
		return (0);
	}
	index = find_command_path(path);
	if (index == -1)
	{
		ft_putstr_fd("The command could not be located because '/usr/bin:/bin'",
			2);
		ft_putstr_fd("is not included in the PATH environment", 2);
		ft_putstr_fd("variable.\nenv: command not found\n", 2);
		data->exit_code = 127;
		ft_free_tab(path);
		return (0);
	}
	ft_free_tab(path);
	return (1);
}

void	make_env(t_data *data)
{
	t_envt	*tmp;

	if (data->cmd->cmd[1] != NULL)
	{
		data->exit_code = 127;
		printf("env: '%s': No such file or directory\n", data->cmd->cmd[1]);
		return ;
	}
	if (!find_env_command_path(data))
		return ;
	tmp = data->envt;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
		data->exit_code = 0;
	}
}

void	execute_env(t_data *data)
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
	make_env(data);
}
