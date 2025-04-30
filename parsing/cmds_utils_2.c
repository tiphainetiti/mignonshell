/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:41:21 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 14:41:36 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Copies existing command arguments to a new array
char	**create_expanded_cmd_array(t_cmd *cmd, int size)
{
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_cmd[i] = cmd->cmd[i];
		i++;
	}
	return (new_cmd);
}
