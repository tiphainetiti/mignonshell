/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:37:44 by ocussy            #+#    #+#             */
/*   Updated: 2025/05/02 18:55:04 by tlay             ###   ########.fr       */
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

// char	*get_env_var(char *var_name, t_envt *envt)
// {
// 	t_envt	*current;
// 	char	**parts;
// 	char	*result;

// 	current = envt;
// 	while (current)
// 	{
// 		parts = ft_split(current->str, '=');
// 		if (!parts)
// 			return (NULL);
// 		if (ft_strcmp(parts[0], var_name) == 0)
// 		{
// 			result = ft_strdup(parts[1] ? parts[1] : "");
// 			ft_free_tab(parts);
// 			return (result);
// 		}
// 		ft_free_tab(parts);
// 		current = current->next;
// 	}
// 	return (ft_strdup(""));
// }

// char	*expand_heredoc_line(char *line, t_envt *envt)
// {
// 	char	*result;
// 	int		i;
// 	int		start;
// 	char	*var_name;
// 	char	*var_value;

// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	start = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$' && line[i + 1] && ft_isalnum(line[i + 1]))
// 		{
// 			ft_strjoin_part(&result, line, start, i - start);
// 			start = i + 1;
// 			i++;
// 			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
// 				i++;
// 			var_name = ft_substr(line, start, i - start);
// 			var_value = get_env_var(var_name, envt);
// 			ft_strjoin_free(&result, var_value);
// 			free(var_name);
// 			free(var_value);
// 			start = i;
// 		}
// 		else
// 			i++;
// 	}
// 	ft_strjoin_part(&result, line, start, i - start);
// 	return (result);
// }

// void	ft_strjoin_part(char **dest, const char *src, int start, int len)
// {
// 	char	*temp;
// 	char	*part;

// 	if (len <= 0)
// 		return ;
// 	part = ft_substr(src, start, len);
// 	if (!part)
// 		return ;
// 	temp = ft_strjoin(*dest, part);
// 	free(*dest);
// 	free(part);
// 	*dest = temp;
// }

// void	ft_strjoin_free(char **dest, char *str)
// {
// 	char	*temp;

// 	temp = ft_strjoin(*dest, str);
// 	free(*dest);
// 	*dest = temp;
// }
