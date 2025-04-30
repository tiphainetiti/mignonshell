/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:02:07 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 14:40:39 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Check if arg has multiple consecutive '/' : 1-yes 0-no
static int	has_multiple_slashes(char *str)
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

// From the start : Get root directory and pass slashes
static void	process_path_start(t_path_params *params, char *normalized)
{
	if (params->path[params->i] == '/')
	{
		normalized[params->j++] = '/';
		params->i++;
		while (params->path[params->i] == '/')
			params->i++;
	}
}

// Process a path segment, handling consecutive slashes
static void	process_path_segment(t_path_params *params, char *normalized)
{
	while (params->path[params->i] && (params->i < (int)params->len
			- params->final_slashes))
	{
		if (params->path[params->i] == '/')
		{
			normalized[params->j++] = '/';
			params->i++;
			while (params->path[params->i] == '/'
				&& (params->i < (int)params->len - params->final_slashes))
				params->i++;
		}
		else
			normalized[params->j++] = params->path[params->i++];
	}
}

/* Normalizes a path by removing consecutive slashes, ex :
	/////////bin//////ls */
static char	*normalize_path(const char *path)
{
	t_path_params	params;
	char			*normalized;

	params.i = 0;
	params.j = 0;
	params.path = path;
	params.len = ft_strlen(path);
	params.final_slashes = number_of_final_slashes(path);
	normalized = malloc(sizeof(char) * params.len + 1);
	if (!normalized)
		return (NULL);
	process_path_start(&params, normalized);
	process_path_segment(&params, normalized);
	return (copy_final_slashes(normalized, params.final_slashes, params.j));
}

/* Handles path normalization for the first argument if needed, ex :
	///bin//////ls */
char	*normalize_first_arg(char *arg, int arg_position)
{
	char	*normalized_arg;

	normalized_arg = NULL;
	if (arg_position == 0 && arg[0] == '/' && has_multiple_slashes(arg))
	{
		normalized_arg = normalize_path(arg);
		if (normalized_arg)
		{
			free(arg);
			return (normalized_arg);
		}
	}
	return (arg);
}
