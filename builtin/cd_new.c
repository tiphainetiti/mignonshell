/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:27:10 by tlay              #+#    #+#             */
/*   Updated: 2025/05/02 18:49:35 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_var_env(t_envt *envt, char *var)
{
	t_envt	*current;
	char	**env_var;

	current = envt;
	while (current)
	{
		env_var = ft_split(envt->str, '=');
		if (env_var && ft_strcmp(env_var[0], var) == 0)
			return (current->str);
		current = current->next;
	}
	return (NULL);
}

int	check_directory_access(const char *path, t_data *data)
{
	struct stat	file_stat;

	if (access(path, F_OK) == -1 && errno == ENOENT)
		return (1);
}
