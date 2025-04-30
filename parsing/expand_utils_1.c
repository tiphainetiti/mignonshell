/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:22:22 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 16:35:57 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Get NAME_VAR len*/
int	get_var_name_length(const char *str, int start)
{
	int	i;

	i = start;
	if (str[start] >= '0' && str[start] <= '9')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '*'))
		i++;
	return (i - start);
}

/* Substract block and join with older block */
char	*join_block(char *result, const char *value, int block_start,
		int block_end)
{
	char	*block;
	char	*temp;

	block = ft_substr(value, block_start, block_end - block_start);
	temp = ft_strjoin(result, block);
	free(result);
	free(block);
	return (temp);
}

/* Get expanded value in env */
char	*get_expanded(char *var_name, int var_len, t_envt *envt)
{
	t_envt	*env;
	char	*expanded;

	env = envt;
	expanded = NULL;
	while (env)
	{
		if (ft_strncmp(env->str, var_name, var_len) == 0
			&& env->str[var_len] == '=')
		{
			expanded = ft_substr(env->str, var_len + 1, ft_strlen(env->str)
					- var_len - 1);
			break ;
		}
		env = env->next;
	}
	return (expanded);
}

char	*append_to_result(char *result, char *to_append)
{
	char	*temp;

	temp = ft_strjoin(result, to_append);
	free(result);
	return (temp);
}

void	update_quotes_state(char current_char, t_quotes *quotes)
{
	if (current_char == '"' && !quotes->inside_single_quotes)
		quotes->inside_double_quotes = !quotes->inside_double_quotes;
	else if (current_char == '\'' && !quotes->inside_double_quotes)
		quotes->inside_single_quotes = !quotes->inside_single_quotes;
}
