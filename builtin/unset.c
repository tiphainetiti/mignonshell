/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:08:52 by tlay              #+#    #+#             */
/*   Updated: 2025/05/01 14:55:34 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_export(t_export **export, char *var)
{
	t_export	*current;
	t_export	*prev;

	current = *export;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			if (!prev)
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

void	unset_envt(t_envt **envt, char *var)
{
	t_envt	*current;
	t_envt	*prev;
	char	**tab_var;

	current = *envt;
	prev = NULL;
	while (current)
	{
		tab_var = ft_split(current->str, '=');
		if (tab_var && ft_strcmp(tab_var[0], var) == 0)
		{
			if (!prev)
				*envt = current->next;
			else
				prev->next = current->next;
			free(current->str);
			free(current);
			ft_free_tab(tab_var);
			return ;
		}
		prev = current;
		current = current->next;
		ft_free_tab(tab_var);
	}
}

void	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		unset_export(&data->export, cmd->cmd[i]);
		unset_envt(&data->envt, cmd->cmd[i]);
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
	ft_unset(data, data->cmd);
}
