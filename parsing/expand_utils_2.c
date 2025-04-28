/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:53:57 by tlay              #+#    #+#             */
/*   Updated: 2025/04/28 15:30:43 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Join a literal $ to result when there is no valid var_name */
static void	invalid_var(t_expand_state *state)
{
	char	*temp;

	temp = ft_strjoin(state->result, "$");
	free(state->result);
	state->result = temp;
}

/**
 * Handles variable name expansion ($NAME)
 * Retrieves the variable value from environment and appends it to result
 * Handles empty variables and variables without values
 */
static void	handle_var_with_name(t_expand_state *state)
{
	int		var_start;
	int		var_len;
	char	*var_name;
	char	*var_value;

	var_start = state->i;
	var_len = get_var_name_length(state->value, var_start);
	state->i += var_len;
	if (var_len > 0)
	{
		var_name = ft_substr(state->value, var_start, var_len);
		var_value = get_expanded(var_name, var_len, state->env);
		if (var_value)
		{
			state->result = append_to_result(state->result, var_value);
			free(var_value);
		}
		free(var_name);
	}
	else
		invalid_var(state);
	state->block_start = state->i;
}

/**
 * Expands the exit code ($?) to its numeric value
 * Appends the exit code to the result and updates state
 */
static void	hande_exit_code_expand(t_expand_state *state)
{
	char	*exit_code;
	char	*temp;

	exit_code = ft_itoa(state->data->exit_code);
	temp = ft_strjoin(state->result, exit_code);
	free(state->result);
	free(exit_code);
	state->result = temp;
	state->i++;
	state->block_start = state->i;
}

/**
 * Wrapper function to handle $ followed by quotes in the expansion state
 * Updates the state with the new position after processing
 */
static void	process_quoted_expansion(t_expand_state *state)
{
	char	quoted_char;
	int		new_i;

	quoted_char = state->value[state->i + 1];
	new_i = handle_quoted_expansion(state->value, state->i, quoted_char,
			&state->result);
	if (new_i != state->i)
	{
		state->i = new_i;
		state->block_start = state->i;
	}
}

/**
 * Main handler for $ symbol in the input
 * Routes to appropriate expansion function based on what follows the $
 */
void	process_dollar(t_expand_state *state)
{
	if (state->i > state->block_start)
		state->result = join_block(state->result, state->value,
				state->block_start, state->i);
	if (state->value[state->i + 1] == '"' || state->value[state->i + 1] == '\'')
	{
		process_quoted_expansion(state);
		return ;
	}
	state->i++;
	if (state->value[state->i] == '?')
		hande_exit_code_expand(state);
	else
		handle_var_with_name(state);
}
