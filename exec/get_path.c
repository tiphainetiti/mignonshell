/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:39:48 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/23 16:07:12 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_all_path(t_data *data, t_envt *envt, char *word)
{
	t_envt	*current;
	char	**tab_path;
	char	**good_path;
	char	*str_path;

	current = envt;
	while (current && ft_strncmp(current->str, "PATH=",
			ft_strlen("PATH=")) != 0)
		current = current->next;
	if (current == NULL && data->cmd->cmd[0][0] != '/')
	{
		data->exit_code = 1;
		return (NULL);
	}
	str_path = current->str + 5;
	tab_path = ft_split(str_path, ':');
	if (tab_path == NULL)
		return (NULL);
	good_path = make_good_path(data, tab_path, word);
	ft_free_tab(tab_path);
	return (good_path);
}

char	**make_good_path(t_data *data, char **tab_path, char *word)
{
	int		size_word;
	char	**final_tab;
	int		i;

	size_word = (int)ft_strlen(word);
	i = 0;
	final_tab = malloc(sizeof(char *) * (ft_size_tab(tab_path) + 1));
	if (!final_tab)
		exit_shell(data, 2, 1);
	while (tab_path[i] != NULL)
	{
		final_tab[i] = malloc(sizeof(char) * ft_strlen(tab_path[i]) + size_word
				+ 2);
		if (!final_tab[i])
		{
			ft_free_tab(final_tab);
			exit_shell(data, 2, 1);
		}
		ft_strlcpy(final_tab[i], tab_path[i], ft_strlen(tab_path[i]) + 1);
		ft_strlcat(final_tab[i], "/", ft_strlen(tab_path[i]) + 2);
		ft_strlcat(final_tab[i], word, ft_strlen(final_tab[i]) + size_word + 1);
		i++;
	}
	final_tab[i] = NULL;
	return (final_tab);
}

void	check_command_split(t_data *data, char *cmd)
{
	char	**command_split;

	command_split = ft_split(cmd, ' ');
	if (ft_size_tab(command_split) > 1)
	{
		data->path = NULL;
		ft_free_tab(command_split);
		return ;
	}
	if (data->path == NULL)
	{
		if (command_split[0] != NULL)
		{
			if (access(command_split[0], F_OK | X_OK | R_OK) != -1)
				data->path = ft_strdup(command_split[0]);
		}
	}
	ft_free_tab(command_split);
}

int	search_slash(t_data *data)
{
	if (ft_strcmp(data->cmd->cmd[0], "./minishell") == 0)
		return (0);
	if (ft_strlen(data->cmd->cmd[0]) >= 3)
	{
		if (data->cmd->cmd[0][0] == '.'
		|| (data->cmd->cmd[0][0] == '/' && data->cmd->cmd[0][1] == '/'))
			return (1);
	}
	return (0);
}

void	get_path(t_data *data)
{
	char	**good_path;
	int		i;

	i = 0;
	data->path = NULL;
	if (search_slash(data) == 1)
		return ;
	good_path = get_all_path(data, data->envt, data->cmd->cmd[0]);
	if (data->cmd->cmd[0][0] == '/')
	{
		ft_free_tab(good_path);
		good_path = NULL;
	}
	while (good_path != NULL && good_path[i])
	{
		if (access(good_path[i], F_OK | R_OK | X_OK) != -1)
		{
			data->path = ft_strdup(good_path[i]);
			break ;
		}
		i++;
	}
	check_command_split(data, data->cmd->cmd[0]);
	ft_free_tab(good_path);
}
