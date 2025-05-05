/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:29:55 by ocussy            #+#    #+#             */
/*   Updated: 2025/05/06 00:59:33 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_directory_and_update_env(t_data *data, char *path)
{
	char	*current_pwd;

	if (chdir(path) == -1)
	{
		error_cd(data, path);
		return ;
	}
	current_pwd = getcwd(NULL, 0);
	if (current_pwd == NULL)
	{
		perror("cd: error retrieving current directory\n");
		return ;
	}
	set_pwds_env(data, data->envt, current_pwd);
	set_pwds_export(data->export, current_pwd);
	free(current_pwd);
	data->exit_code = 0;
}

char	*get_home_path(t_envt *env)
{
	while (env && ft_strncmp(env->str, "HOME=", 5) != 0)
		env = env->next;
	if (!env)
	{
		write(2, "bash: cd: HOME not set\n", 24);
		return (NULL);
	}
	return (env->str + 5);
}

void	handle_cd_path(t_data *data, t_cmd *cmd, t_envt *env)
{
	char	*path_home;

	if (ft_size_tab(cmd->cmd) == 2)
		change_directory_and_update_env(data, cmd->cmd[1]);
	else if (ft_size_tab(cmd->cmd) == 1)
	{
		path_home = get_home_path(env);
		if (path_home)
			change_directory_and_update_env(data, path_home);
		else
			data->exit_code = 1;
	}
	else
	{
		write(2, "bash: cd: too many arguments\n", 30);
		data->exit_code = 1;
	}
}

void	make_cd(t_data *data, t_cmd *cmd)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (current_pwd == NULL)
	{
		printf("cd: error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
		while (current_pwd == NULL)
		{
			if (current_pwd != NULL)
				break ;
			chdir("..");
			current_pwd = getcwd(NULL, 0);
		}
		set_pwds_env(data, data->envt, current_pwd);
		set_pwds_export(data->export, current_pwd);
		free(current_pwd);
		data->exit_code = 0;
		return ;
	}
	free(current_pwd);
	handle_cd_path(data, cmd, data->envt);
}

void	execute_cd(t_data *data)
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
	if (data->cmd->cmd[1] != NULL)
	{
		if (ft_strncmp(data->cmd->cmd[1], "-", 1) == 0
			&& ft_strlen(data->cmd->cmd[1]))
			get_pwd(data);
		else
			make_cd(data, data->cmd);
	}
	else
		make_cd(data, data->cmd);
}
