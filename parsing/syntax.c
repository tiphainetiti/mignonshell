/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:19:52 by tlay              #+#    #+#             */
/*   Updated: 2025/04/23 13:43:48 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	print_syntax_error(char *value, t_data *data)
{
	data->exit_code = 2;
	if (!value)
		value = "|";
	printf("minishell: syntax error near unexpected token `%s'\n", value);
	return (false);
}

bool	print_quotes_error(char quotes_type, t_data *data)
{
	data->exit_code = 2;
	return (printf("minishell: syntax error: unexpected EOF while looking for matching `%c'\n",
			quotes_type), false);
}

static bool	syntax_first_pipe(t_token *tokens, t_data *data)
{
	if (tokens && tokens->type == PIPE)
		return (print_syntax_error(NULL, data));
	return (true);
}

static bool	syntax_pipe(t_token *tokens, t_data *data)
{
	t_token	*current;

	if (!tokens)
		return (true);
	current = tokens;
	// if (current->type == PIPE)
	// 	return (print_syntax_error(NULL, data));
	while (current && current->next)
	{
		if (current->type == PIPE)
		{
			if (current->next->type == PIPE)
				return (print_syntax_error(NULL, data));
			// if (current->next->type == REDIRECTION)
			// 	return (print_syntax_error(current->next->value, data));
		}
		current = current->next;
	}
	// Check last token
	if (current && current->type == PIPE)
		return (print_syntax_error(NULL, data));
	return (true);
}

static bool	syntax_redir(t_token *tokens, t_data *data)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == REDIRECTION)
		{
			// Vérifier d'abord si une redirection est suivie d'un pipe
			if (current->next && current->next->type == PIPE)
				return (print_syntax_error(current->next->value, data));
			// Ensuite vérifier les autres cas
			else if (current->next && current->next->type == REDIRECTION)
			{
				if (ft_strcmp(current->value, "<") == 0
					&& ft_strcmp(current->next->value, ">") == 0)
				{
					if (!current->next->next)
						return (print_syntax_error("newline", data));
					if (current->next->next->type != COMMAND)
						return (print_syntax_error(current->next->next->value,
								data));
					current = current->next;
				}
				else
					return (print_syntax_error(current->next->value, data));
			}
			else if (!current->next)
				return (print_syntax_error("newline", data));
			else if (current->next->type != COMMAND)
				return (print_syntax_error(current->next->value, data));
		}
		current = current->next;
	}
	return (true);
}

static bool	syntax_quotes(t_token *tokens, t_data *data)
{
	t_token	*current;
	int		in_quotes;
	char	quotes_type;
	int		i;

	current = tokens;
	in_quotes = 0;
	quotes_type = 0;
	while (current)
	{
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == '"' || current->value[i] == '\'')
			{
				if (!in_quotes)
				{
					in_quotes = 1;
					quotes_type = current->value[i];
				}
				else if (current->value[i] == quotes_type)
					in_quotes = 0;
			}
			i++;
		}
		current = current->next;
	}
	if (in_quotes == 1)
		return (print_quotes_error(quotes_type, data));
	return (true);
}

bool	check_syntax(t_token *tokens, t_data *data)
{
	if (!syntax_first_pipe(tokens, data) || !syntax_pipe(tokens, data)
		|| !syntax_redir(tokens, data) || !syntax_quotes(tokens, data))
		return (false);
	return (true);
}
