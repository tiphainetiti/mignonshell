/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:06:12 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/15 15:35:31 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_node_sorted(t_export **head, char *key, char *value)
{
	t_export	*new_node;
	t_export	*current;

	new_node = create_export_node(key, value);
	if (!new_node)
		return ;
	if (*head == NULL || ft_strcmp((*head)->key, key) > 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL && ft_strcmp(current->next->key, key) <= 0)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

int	check_already_node(t_export **export, char *key, char *value)
{
	t_export	*current;

	current = *export;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value != NULL)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	update_existing_node(t_envt *current, char *key, char *str)
{
	char	**tab_str;

	tab_str = ft_split(current->str, '=');
	if (tab_str && ft_strncmp(tab_str[0], key, ft_strlen(key)) == 0
		&& tab_str[0][ft_strlen(key)] == '\0')
	{
		free(current->str);
		current->str = ft_strdup(str);
		free(str);
		ft_free_tab(tab_str);
		return (1);
	}
	else
	{
		ft_free_tab(tab_str);
		return (0);
	}
}

void	add_node_envt(t_data *data, t_envt **envt, char *key, char *value)
{
	t_envt	*node;
	t_envt	*current;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(value)
				+ 2));
	if (!str)
		exit_shell(data, 2, 1);
	node = (t_envt *)malloc(sizeof(t_envt));
	if (!node)
		exit_shell(data, 2, 1);
	ft_strlcpy(str, key, ft_strlen(key) + 1);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, value, ft_strlen(str) + ft_strlen(value) + 1);
	current = *envt;
	if (check_already_export(node, current, key, str) == 1)
		return ;
	node->str = ft_strdup(str);
	node->next = *envt;
	*envt = node;
	free(str);
}

int	print_export(t_data *data, t_export **export)
{
	t_export	*tmp;

	tmp = *export;
	if (ft_size_tab(data->cmd->cmd) == 1)
	{
		while (tmp)
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s\n", tmp->key);
			tmp = tmp->next;
		}
		data->exit_code = 0;
		return (1);
	}
	return (0);
}
