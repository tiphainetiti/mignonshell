/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:04:16 by tlay              #+#    #+#             */
/*   Updated: 2025/04/22 17:37:51 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Get USER len
int	get_var_name_length(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - start);
}

// Substract block and join with older block
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

// Get expanded value in env
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

char	*expand_variables(char *value, t_data *data)
{
	t_envt		*env;
	t_quotes	quotes;
	int			i;
	int			block_start;
	char		*result;
	char		*temp;
	int			var_start;
	int			var_len;
	char		*var_name;
	char		*var_value;
	char		*exit_code;

	env = data->envt;
	quotes.inside_double_quotes = 0;
	quotes.inside_single_quotes = 0;
	i = 0;
	block_start = 0;
	result = ft_strdup("");
	while (value[i])
	{
		update_quotes_state(value[i], &quotes);
		// Expansion de variables
		if (value[i] == '$' && !quotes.inside_single_quotes)
		{
			// Copie d'abord le texte entre block_start et i
			if (i > block_start)
				result = join_block(result, value, block_start, i);
			i++; // Saute le $
			// Traite le cas spécial $?
			if (value[i] == '?')
			{
				exit_code = ft_itoa(data->exit_code);
				temp = ft_strjoin(result, exit_code);
				free(result);
				free(exit_code);
				result = temp;
				i++;
				block_start = i;
				continue ;
			}
			// Détermine la longueur du nom de variable
			var_start = i;
			var_len = get_var_name_length(value, i);
			i += var_len;
			if (var_len > 0)
			{
				// Extraction du nom de variable
				var_name = ft_substr(value, var_start, var_len);
				var_value = get_expanded(var_name, var_len, env);
				// Ajout au résultat
				if (var_value)
				{
					result = append_to_result(result, var_value);
					free(var_value);
				}
				free(var_name);
				block_start = i;
				continue ;
			}
			else
			{
				// $ sans nom de variable valide - on le traite comme littéral
				temp = ft_strjoin(result, "$");
				free(result);
				result = temp;
				block_start = i;
				continue ;
			}
		}
		i++;
	}
	if (i > block_start)
		result = join_block(result, value, block_start, i);
	return (result);
}

t_token	*expand_tokens(t_token *tokens, t_data *data)
{
	t_token	*current;
	t_token	*head;
	char	*expanded;

	current = tokens;
	head = tokens;
	while (current)
	{
		if (current->type == COMMAND)
		{
			expanded = expand_variables(current->value, data);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
	return (head);
}
