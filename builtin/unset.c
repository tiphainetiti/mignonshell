/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:36:46 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:42:56 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_export(t_export **export, char *str)
{
	t_export	*current;
	t_export	*prev;

	current = *export;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, str) == 0)
		{
			if (prev == NULL)
				*export = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	unset_env(t_envt **envt, char *str)
{
	t_envt	*current;
	t_envt	*prev;
	char	**tab_str;

	current = *envt;
	prev = NULL;
	while (current)
	{
		tab_str = ft_split(current->str, '=');
		if (ft_strncmp(tab_str[0], str, ft_strlen(tab_str[0])) == 0)
		{
			if (prev == NULL)
				*envt = current->next;
			else
				prev->next = current->next;
			free(current->str);
			free(current);
			ft_free_tab(tab_str);
			return ;
		}
		prev = current;
		current = current->next;
		ft_free_tab(tab_str);
	}
}

void	make_unset(t_data *data, t_cmd *cmd, t_export **export)
{
	int	i;

	i = 1;
	while (cmd->cmd[i] != NULL)
	{
		unset_export(export, cmd->cmd[i]);
		unset_env(&data->envt, cmd->cmd[i]);
		data->exit_code = 0;
		i++;
	}
}

void	execute_unset(t_data *data)
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
	make_unset(data, data->cmd, &data->export);
}
