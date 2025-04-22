/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:57:41 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/21 10:35:54 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_already_export(t_envt *node, t_envt *current, char *key, char *str)
{
	while (current != NULL)
	{
		if (update_existing_node(current, key, str) == 1)
		{
			free(node);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	write_export(char *str)
{
	write(2, "bash: export: '", 16);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
}
