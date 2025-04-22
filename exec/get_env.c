/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:24:51 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/14 16:53:04 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envt(t_envt *envt)
{
	t_envt	*current;
	t_envt	*next;

	current = envt;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	make_struct_env(t_envt *node, t_envt *current, t_envt **envt)
{
	if (*envt == NULL || envt == NULL)
		*envt = node;
	else
	{
		current = *envt;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
}

int	get_env(t_envt **envt, char **env)
{
	int		i;
	t_envt	*current;
	t_envt	*node;

	*envt = NULL;
	current = *envt;
	node = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		node = (t_envt *)malloc(sizeof(t_envt));
		if (!node)
			return (-1);
		node->str = ft_strdup(env[i]);
		node->next = NULL;
		make_struct_env(node, current, envt);
		i++;
	}
	return (0);
}

char	**make_env_tab(t_envt *envt)
{
	char	**tab_envt;
	int		i;
	t_envt	*tmp;
	t_envt	*tmp2;

	i = 0;
	tmp = envt;
	tmp2 = envt;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tab_envt = malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (!tab_envt)
		return (NULL);
	while (tmp2)
	{
		tab_envt[i] = ft_strdup(tmp2->str);
		tmp2 = tmp2->next;
		i++;
	}
	tab_envt[i] = NULL;
	return (tab_envt);
}
