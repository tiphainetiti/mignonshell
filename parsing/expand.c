/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:04:16 by tlay              #+#    #+#             */
/*   Updated: 2025/04/28 15:05:18 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Initialize the expansion state structure with default values */
static void	init_expand_state(t_expand_state *state, char *value, t_data *data)
{
	state->quotes = (t_quotes){0, 0};
	state->i = 0;
	state->block_start = 0;
	state->result = ft_strdup("");
	state->value = value;
	state->data = data;
	state->env = data->envt;
}

/* Returns a new string with all expansions applied */
char	*expand_variables(char *value, t_data *data)
{
	t_expand_state	state;

	init_expand_state(&state, value, data);
	while (value[state.i])
	{
		update_quotes_state(value[state.i], &state.quotes);
		if (value[state.i] == '$' && !state.quotes.inside_single_quotes)
			process_dollar(&state);
		else
			state.i++;
	}
	if (state.i > state.block_start)
		state.result = join_block(state.result, value, state.block_start,
				state.i);
	return (state.result);
}

/* Removes the empty token (current) from the linked list */
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

/* Check if empty string or only spaces : 1-true 0-false */
static int	is_empty_after_expansion(char *expanded)
{
	int	i;

	if (!expanded || !*expanded)
		return (1);
	i = 0;
	while (expanded && is_whitespace(expanded[i]))
		i++;
	return (!expanded[i]);
}

/* Main function */
t_token	*expand_tokens(t_token *token, t_data *data)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;
	char	*expanded;

	current = token;
	head = token;
	prev = NULL;
	while (current)
	{
		if (current->type == COMMAND)
		{
			expanded = expand_variables(current->value, data);
			free(current->value);
			current->value = expanded;
			if (is_empty_after_expansion(expanded))
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

// char	*expand_variables(char *value, t_data *data)
// {
// 	t_envt		*env;
// 	t_quotes	quotes;
// 	int			i;
// 	int			block_start;
// 	char		*result;
// 	char		*temp;
// 	char		*var_name;
// 	char		*var_value;
// 	char		*exit_code;
// 	int			var_start;
// 	int			var_len;
// 	char		quoted_char;
// 	int			new_i;

// 	env = data->envt;
// 	quotes = (t_quotes){0, 0};
// 	i = 0;
// 	block_start = 0;
// 	result = ft_strdup("");
// 	while (value[i])
// 	{
// 		update_quotes_state(value[i], &quotes);
// 		// Gestion des variables
// 		if (value[i] == '$' && !quotes.inside_single_quotes)
// 		{
// 			// Copier le texte avant le $
// 			if (i > block_start)
// 				result = join_block(result, value, block_start, i);
// 			if (value[i + 1] == '"' || value[i + 1] == '\'')
// 			{
// 				quoted_char = value[i + 1];
// 				new_i = handle_quoted_expansion(value, i, quoted_char, &result);
// 				if (new_i != i)
// 				{
// 					i = new_i;
// 					block_start = i;
// 					continue ;
// 				}
// 			}
// 			i++; // Passer le $
// 			// Cas spécial: $?
// 			if (value[i] == '?')
// 			{
// 				exit_code = ft_itoa(data->exit_code);
// 				temp = ft_strjoin(result, exit_code);
// 				free(result);
// 				free(exit_code);
// 				result = temp;
// 				i++;
// 				block_start = i;
// 				continue ;
// 			}
// 			// Extraire le nom de variable
// 			var_start = i;
// 			var_len = get_var_name_length(value, i);
// 			i += var_len;
// 			if (var_len > 0)
// 			{
// 				var_name = ft_substr(value, var_start, var_len);
// 				var_value = get_expanded(var_name, var_len, env);
// 				// Si la variable existe, ajouter sa valeur
// 				// Si elle n'existe pas, ne rien ajouter (chaîne vide)
// 				if (var_value)
// 				{
// 					result = append_to_result(result, var_value);
// 					free(var_value);
// 				}
// 				free(var_name);
// 				block_start = i;
// 				continue ;
// 			}
// 			else
// 			{
// 				// $ sans nom de variable - le traiter comme littéral
// 				temp = ft_strjoin(result, "$");
// 				free(result);
// 				result = temp;
// 				block_start = i;
// 				continue ;
// 			}
// 		}
// 		i++;
// 	}
// 	// Ajouter tout caractère restant
// 	if (i > block_start)
// 		result = join_block(result, value, block_start, i);
// 	return (result);
// }