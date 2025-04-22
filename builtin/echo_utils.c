/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:04:25 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/04 17:10:18 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_and_cleanup_spaces(char *cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\x01')
			cmd[j] = ' ';
		else if (cmd[j] == ' ' || cmd[j] == '\t' || cmd[j] == '\n')
		{
			while (cmd[j + 1] == ' ' || cmd[j + 1] == '\t'
				|| cmd[j + 1] == '\n')
			{
				ft_memmove(&cmd[j + 1], &cmd[j + 2], strlen(cmd) - j - 1);
			}
		}
		j++;
	}
}

void	restore_spaces(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		replace_and_cleanup_spaces(cmd[i]);
		i++;
	}
}
