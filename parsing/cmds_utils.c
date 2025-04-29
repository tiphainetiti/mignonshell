/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:17:09 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 19:05:25 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create empty command
t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = malloc(sizeof(char *));
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd[0] = NULL;
	cmd->file = NULL;
	cmd->nb_file = 0;
	cmd->was_quoted = 0;
	cmd->next = NULL;
	return (cmd);
}

int	was_quoted(char *str, char *result)
{
	if (ft_strlen(result) < ft_strlen(str))
		return (1);
	return (0);
}

char	*copy_final_slashes(char *normalized, int final_slashes, int j)
{
	while (final_slashes > 0)
	{
		normalized[j++] = '/';
		final_slashes--;
	}
	normalized[j] = '\0';
	return (normalized);
}

// Check if arg has multiple consecutive '/' : 1-yes 0-no
int	has_multiple_slashes(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] && str[i + 1])
	{
		if (str[i] == '/' && str[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	number_of_final_slashes(const char *path)
{
	int	i;
	int	len;
	int	result;

	len = ft_strlen(path);
	i = len - 1;
	result = 0;
	while (i > 0 && path[i] == '/')
	{
		result++;
		i--;
	}
	return (result);
}
