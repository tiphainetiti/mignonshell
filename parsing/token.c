/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:43:58 by tlay              #+#    #+#             */
/*   Updated: 2025/04/28 16:54:11 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static void	handle_special_token(char **input, char *start, char **temp,
		int *type)
{
	if (*start == '|')
		*type = PIPE;
	else
		*type = REDIRECTION;
	if ((**input == '>' && *(*input + 1) == '>') || (**input == '<' && *(*input
				+ 1) == '<'))
	{
		*temp = ft_substr(start, 0, 2);
		*input += 2;
	}
	else
	{
		*temp = ft_substr(start, 0, 1);
		*input += 1;
	}
}

static void	handle_word_token(char **input, char *start, char **temp)
{
	int		in_quotes;
	char	quote_type;

	in_quotes = 0;
	quote_type = 0;
	while (**input && (in_quotes || (!is_whitespace(**input)
				&& !is_special_char(**input))))
	{
		if (**input == '"' || **input == '\'')
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_type = **input;
			}
			else if (**input == quote_type)
				in_quotes = 0;
		}
		*input += 1;
	}
	*temp = ft_substr(start, 0, *input - start);
}

static void	extract_token(char **input, t_token **tokens, t_data *data)
{
	char	*start;
	char	*temp;
	int		type;
	t_token	*new_token;

	start = *input;
	temp = NULL;
	if (is_special_char(**input))
	{
		handle_special_token(input, start, &temp, &type);
		check_heredoc(temp, data);
	}
	else
	{
		handle_word_token(input, start, &temp);
		type = COMMAND;
	}
	if (temp)
	{
		new_token = create_token(temp, type);
		if (new_token)
			add_token_to_list(tokens, new_token);
		free(temp);
	}
}

t_token	*tokenize(char *input, t_data *data)
{
	t_token	*token;
	char	*cursor;

	token = NULL;
	cursor = input;
	data->is_heredoc = 0;
	while (*cursor)
	{
		while (*cursor && is_whitespace(*cursor))
			cursor++;
		if (*cursor)
			extract_token(&cursor, &token, data);
	}
	return (token);
}

// static void	extract_token(char **input, t_token **tokens, t_data *data)
// {
// 	char	*start;
// 	char	*temp;
// 	int		type;
// 	int		in_quotes;
// 	char	quote_type;
// 	t_token	*new_token;

// 	in_quotes = 0;
// 	quote_type = 0;
// 	start = *input;
// 	// Handle special characters
// 	if (is_special_char(**input))
// 	{
// 		if (*start == '|')
// 			type = PIPE;
// 		else
// 			type = REDIRECTION;
// 		// Handle >> and <<
// 		if ((**input == '>' && *(*input + 1) == '>') || (**input == '<'
// 				&& *(*input + 1) == '<'))
// 		{
// 			temp = ft_substr(start, 0, 2);
// 			*input += 2;
// 			// Set heredoc flag if needed
// 			if (ft_strncmp(temp, "<<", 2) == 0)
// 				data->is_heredoc = 1;
// 		}
// 		else
// 		{
// 			temp = ft_substr(start, 0, 1);
// 			*input += 1;
// 		}
// 	}
// 	else
// 	{
// 		// Extract word token until whitespace or special char
// 		while (**input && (in_quotes || (!is_whitespace(**input)
// 					&& !is_special_char(**input))))
// 		{
// 			// Quote handling
// 			if (**input == '"' || **input == '\'')
// 			{
// 				if (!in_quotes)
// 				{
// 					in_quotes = 1;
// 					quote_type = **input;
// 				}
// 				else if (**input == quote_type)
// 					in_quotes = 0;
// 			}
// 			*input += 1;
// 		}
// 		temp = ft_substr(start, 0, *input - start);
// 		type = COMMAND;
// 	}
// 	if (temp)
// 	{
// 		new_token = create_token(temp, type);
// 		if (new_token)
// 			add_token_to_list(tokens, new_token);
// 		free(temp);
// 	}
// }