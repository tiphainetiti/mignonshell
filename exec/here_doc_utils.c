/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:37:44 by ocussy            #+#    #+#             */
/*   Updated: 2024/09/23 16:34:00 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_filename(t_data *data, char *filename)
{
	char	*suffix;
	int		i;

	i = 0;
	ft_strlcpy(filename, "heredoc", ft_strlen("heredoc") + 1);
	while (access(filename, F_OK) == 0)
	{
		i++;
		ft_strlcpy(filename, "heredoc", ft_strlen("heredoc") + 1);
		suffix = ft_itoa(i);
		if (!suffix)
		{
			free(filename);
			exit_shell(data, 0, 1);
		}
		ft_strlcat(filename, suffix, ft_strlen(filename) + ft_strlen(suffix)
			+ 1);
		free(suffix);
	}
	return (filename);
}

int	ft_open_file(t_data *data, char **filename)
{
	int	file;

	*filename = malloc(sizeof(char) * 17);
	if (!*filename)
		exit_shell(data, 2, 1);
	*filename = search_filename(data, *filename);
	file = open(*filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (file == -1)
	{
		free(*filename);
		ft_putstr_fd("Erreur lors de l'ouverture du fichier.\n", 2);
		data->exit_code = 1;
	}
	return (file);
}
