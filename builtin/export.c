/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:04:43 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/25 17:42:49 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_identifier(t_data *data, char *str)
{
	int	j;

	j = 0;
	while (str[j] == '_')
		j++;
	if (str[0] == '=' || (ft_isalpha(str[j]) == 0 && str[j] != '='))
	{
		write_export(str);
		data->exit_code = 1;
		return (0);
	}
	while (str[j] && str[j] != '=')
	{
		if (ft_isalnum(str[j]) == 0 && str[j] != '_')
		{
			write_export(str);
			data->exit_code = 1;
			return (0);
		}
		j++;
	}
	return (1);
}

void	process_export(t_data *data, t_export **export, char *str)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		key = ft_strndup(str, equal_sign - str);
		value = ft_strdup(equal_sign + 1);
		add_node_envt(data, &data->envt, key, value);
		if (check_already_node(export, key, value) == 0)
			add_node_sorted(export, key, value);
	}
	else
	{
		key = ft_strdup(str);
		value = NULL;
		if (check_already_node(export, key, value) == 0)
			add_node_sorted(export, key, value);
	}
	free(key);
	free(value);
}

void	make_export(t_data *data, t_export **export)
{
	char	*str;
	int		i;

	i = 1;
	if (print_export(data, export) == 1)
		return ;
	str = data->cmd->cmd[i];
	while (str)
	{
		if (!validate_identifier(data, str))
			return ;
		process_export(data, export, str);
		i++;
		str = data->cmd->cmd[i];
	}
	data->exit_code = 0;
}

void	execute_export(t_data *data)
{
	if (data->outfile != STDOUT_FILENO)
	{
		if (data->outfile == -1)
		{
			print_exit_shell(data, 4);
			return ;
		}
		if (dup2(data->outfile, STDOUT_FILENO))
			close(data->outfile);
	}
	make_export(data, &data->export);
}
