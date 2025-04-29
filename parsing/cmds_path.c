/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:02:07 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 19:18:16 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// From the start : Get root directory and pass slashes
static void	process_path_start(t_path_params *params, char *normalized)
{
	if (params->path[params->i] == '/')
	{
		normalized[params->j++] = '/';
		params->i++;
		while (params->path[params->i] == '/') /*
			&&(i < (int)len - final_slashes) ???*/
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

// Normalizes a path by removing consecutive slashes, ex : /////////bin//////ls
char	*normalize_path(const char *path)
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
