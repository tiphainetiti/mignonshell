/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:57:07 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 16:39:35 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Handles the result of empty quoted expansions ($"" or $'')
 * Returns either a literal $ or empty string
 */
char	*empty_quoted_expansion(char *result, t_quotes quotes)
{
	char	*temp;

	temp = NULL;
	if (quotes.inside_double_quotes)
		temp = ft_strjoin(result, "$");
	else
		temp = ft_strdup(result);
	return (temp);
}

static int	process_content(t_quote_exp *exp)
{
	char	*content;
	char	*temp;
	int		end;

	end = exp->i + 2;
	while (exp->value[end] && exp->value[end] != exp->quote_char)
		end++;
	if (exp->value[end] != exp->quote_char)
		return (exp->i);
	if (end == exp->i + 2)
		temp = empty_quoted_expansion(*(exp->result), exp->quotes);
	else
	{
		content = ft_substr(exp->value, exp->i + 2, end - (exp->i + 2));
		temp = ft_strjoin(*(exp->result), content);
		free(content);
	}
	free(*(exp->result));
	*(exp->result) = temp;
	return (end + 1);
}

/**
 * Process a $ followed by quotes ($"..." or $'...')
 * Returns position after the closing quote or original position if invalid
 */
int	handle_quoted_expansion(char *value, int i, char quote_char, char **result)
{
	t_quote_exp	exp;
	int			j;

	j = 0;
	exp.quotes = (t_quotes){0, 0};
	while (j < i)
		update_quotes_state(value[j++], &exp.quotes);
	exp.value = value;
	exp.i = i;
	exp.quote_char = quote_char;
	exp.result = result;
	return (process_content(&exp));
}
