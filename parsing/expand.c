/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:04:16 by tlay              #+#    #+#             */
/*   Updated: 2025/04/27 17:27:32 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*result_quoted_expansion(char *result, t_quotes quotes)
{
	char	*temp;

	temp = NULL;
	if (quotes.inside_double_quotes)
		temp = ft_strjoin(result, "$");
	else
		temp = ft_strdup(result);
	return (temp);
}

// i + 2 = start
int	handle_quoted_expansion(char *value, int i, char quote_char, char **result)
{
	char		*content;
	char		*temp;
	t_quotes	quotes;

	int end, j;
	j = 0;
	quotes = (t_quotes){0, 0};
	while (j < i)
		update_quotes_state(value[j++], &quotes);
	end = i + 2;
	while (value[end] && value[end] != quote_char)
		end++;
	if (value[end] != quote_char)
		return (i);
	if (end == i + 2)
		temp = result_quoted_expansion(*result, quotes);
	else
	{
		content = ft_substr(value, i + 2, end - (i + 2));
		temp = ft_strjoin(*result, content);
		free(content);
	}
	free(*result);
	*result = temp;
	return (end + 1);
}

char	*expand_variables(char *value, t_data *data)
{
	t_envt		*env;
	t_quotes	quotes;
	int			i;
	int			block_start;
	char		*result;
	char		*temp;
	char		*var_name;
	char		*var_value;
	char		*exit_code;
	int			var_start;
	int			var_len;
	char		quoted_char;
	int			new_i;

	env = data->envt;
	quotes = (t_quotes){0, 0};
	i = 0;
	block_start = 0;
	result = ft_strdup("");
	while (value[i])
	{
		update_quotes_state(value[i], &quotes);
		// Gestion des variables
		if (value[i] == '$' && !quotes.inside_single_quotes)
		{
			// Copier le texte avant le $
			if (i > block_start)
				result = join_block(result, value, block_start, i);
			if (value[i + 1] == '"' || value[i + 1] == '\'')
			{
				quoted_char = value[i + 1];
				new_i = handle_quoted_expansion(value, i, quoted_char, &result);
				if (new_i != i)
				{
					i = new_i;
					block_start = i;
					continue ;
				}
			}
			i++; // Passer le $
			// Cas spécial: $?
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
			// Extraire le nom de variable
			var_start = i;
			var_len = get_var_name_length(value, i);
			i += var_len;
			if (var_len > 0)
			{
				var_name = ft_substr(value, var_start, var_len);
				var_value = get_expanded(var_name, var_len, env);
				// Si la variable existe, ajouter sa valeur
				// Si elle n'existe pas, ne rien ajouter (chaîne vide)
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
				// $ sans nom de variable - le traiter comme littéral
				temp = ft_strjoin(result, "$");
				free(result);
				result = temp;
				block_start = i;
				continue ;
			}
		}
		i++;
	}
	// Ajouter tout caractère restant
	if (i > block_start)
		result = join_block(result, value, block_start, i);
	return (result);
}

t_token	*skip_empty_token(t_token *current, t_token *prev, t_token **head)
{
	t_token	*next;

	next = current->next;
	if (prev)
		prev->next = current->next;
	else
		*head = current->next;
	free(current->value);
	free(current);
	return (next);
}

t_token	*expand_tokens(t_token *token, t_data *data)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;
	char	*expanded;
	int		i;

	current = token;
	head = token;
	i = 0;
	prev = NULL;
	while (current)
	{
		if (current->type == COMMAND)
		{
			expanded = expand_variables(current->value, data);
			free(current->value);
			current->value = expanded;
			if (expanded && *expanded)
			{
				i = 0;
				while (expanded && is_whitespace(expanded[i]))
					i++;
				if (!expanded[i])
				{
					current = skip_empty_token(current, prev, &head);
					continue ;
				}
			}
			else if (!expanded || !*expanded)
			{
				current = skip_empty_token(current, prev, &head);
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
	return (head);
}

// A REVOIR : NORME GOOD ???
/*
static int	is_only_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str && is_whitespace(str[i]))
		i++;
	return (!str[i]);
}

static t_token	*process_command_token(t_token *current, t_token *prev,
		t_token **head, t_data *data)
{
	char	*expanded;

	expanded = expand_variables(current->value, data);
	free(current->value);
	current->value = expanded;
	if (!expanded || !*expanded || is_only_whitespace(expanded))
		return (skip_empty_token(current, prev, head));
	return (current);
}

t_token	*expand_tokens(t_token *token, t_data *data)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;

	current = token;
	head = token;
	prev = NULL;
	while (current)
	{
		if (current->type == COMMAND)
		{
			current = process_command_token(current, prev, &head, data);
			if (prev && prev->next != current)
				continue ;
		}
		prev = current;
		current = current->next;
	}
	return (head);
}*/