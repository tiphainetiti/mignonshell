/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:53:57 by tlay              #+#    #+#             */
/*   Updated: 2025/05/01 13:25:35 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/* Get variable name expansion ($NAME) from env appends it to the result */
static void	handle_var_name(t_expand_state *state, int var_len, int var_start)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_substr(state->value, var_start, var_len);
	var_value = get_expanded(var_name, var_len, state->env);
	if (var_value)
	{
		state->result = append_to_result(state->result, var_value);
		free(var_value);
	}
	free(var_name);
	state->block_start = state->i;
}

static void	handle_literal_dollar(t_expand_state *state)
{
	char	*temp;

	temp = ft_strjoin(state->result, "$");
	free(state->result);
	state->result = temp;
	state->block_start = state->i;
}

/* After '$' : Check if there is text between the quotes */
static int	check_quoted_expansion(t_expand_state *state)
{
	char	quoted_char;
	int		new_i;

	if (state->value[state->i + 1] == '"' || state->value[state->i + 1] == '\'')
	{
		quoted_char = state->value[state->i + 1];
		new_i = handle_quoted_expansion(state->value, state->i, quoted_char,
				&state->result);
		if (new_i != state->i)
		{
			state->i = new_i;
			state->block_start = state->i;
			return (1);
		}
	}
	return (0);
}

void	process_dollar(t_expand_state *state)
{
	int	var_start;
	int	var_len;

	if (state->i > state->block_start)
		state->result = join_block(state->result, state->value,
				state->block_start, state->i);
	if (check_quoted_expansion(state))
		return ;
	state->i++;
	if (state->value[state->i] == '?')
	{
		hande_exit_code_expand(state);
		return ;
	}
	var_start = state->i;
	var_len = get_var_name_length(state->value, state->i);
	state->i += var_len;
	if (var_len > 0)
		handle_var_name(state, var_len, var_start);
	else
		handle_literal_dollar(state);
}
