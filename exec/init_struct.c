/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:12:51 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 15:29:18 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_data(t_data *data)
{
	data->nb_cmd = 0;
	data->tmp_fd = -1;
	data->token = NULL;
	data->envt = NULL;
	data->cmd = NULL;
	data->export = NULL;
	data->limiter = NULL;
	data->path = NULL;
	data->pid = NULL;
	data->exit_code = 0;
	data->lst_char_split = 0;
	data->is_heredoc = 0;
	data->fd[READ_FD] = -1;
	data->fd[WRITE_FD] = -1;
	return (0);
}

void	make_struct_export(t_export *node, t_export *current_export,
		t_export **export)
{
	if (*export == NULL || export == NULL)
		*export = node;
	else
	{
		current_export = *export;
		while (current_export->next != NULL)
			current_export = current_export->next;
		current_export->next = node;
	}
}

t_export	*create_export_node(char *key, char *value)
{
	t_export	*node;

	node = (t_export *)malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value != NULL)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	split_env_var(char *str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		*key = ft_strndup(str, equal_sign - str);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(str);
		*value = NULL;
	}
}

int	get_export(t_export **export, t_envt **envt)
{
	t_envt	*current_envt;
	char	*key;
	char	*value;

	current_envt = *envt;
	*export = NULL;
	while (current_envt)
	{
		split_env_var(current_envt->str, &key, &value);
		add_node_sorted(export, key, value);
		free(key);
		free(value);
		current_envt = current_envt->next;
	}
	return (0);
}
