/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:38:43 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/23 16:00:07 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		if (tab[i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_size_tab_int(int *tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i] != -1)
	{
		i++;
	}
	return (i);
}

int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	delete_envt(t_envt **data)
{
	t_envt	*store;
	t_envt	*new;

	new = *data;
	while (new)
	{
		store = new->next;
		free(new->str);
		free(new);
		new = store;
	}
	*data = NULL;
}

void	delete_export(t_export **export)
{
	t_export	*store;
	t_export	*new;

	new = *export;
	while (new)
	{
		store = new->next;
		free(new->key);
		free(new->value);
		free(new);
		new = store;
	}
	*export = NULL;
}
