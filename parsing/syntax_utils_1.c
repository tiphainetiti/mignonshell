/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:45:23 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 13:58:11 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	print_syntax_error(char *value, t_data *data)
{
	data->exit_code = 2;
	if (!value)
		value = "|";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("'\n", 2);
	return (false);
}

bool	print_quotes_error(char quotes_type, t_data *data)
{
	data->exit_code = 2;
	ft_putstr_fd("minishell: syntax error: unexpected EOF while looking", 2);
	ft_putstr_fd(" for matching `", 2);
	ft_putchar_fd(quotes_type, 2);
	ft_putstr_fd("'\n", 2);
	return (false);
}

bool	check_token_quotes(t_token *token, int *in_quotes, char *quotes_type)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		get_quotes_state(token->value[i], in_quotes, quotes_type);
		i++;
	}
	return (true);
}

void	get_quotes_state(char c, int *in_quotes, char *quotes_type)
{
	if (c == '"' || c == '\'')
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quotes_type = c;
		}
		else if (c == *quotes_type)
			*in_quotes = 0;
	}
}
