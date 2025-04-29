/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:47:45 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 13:51:51 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_redirection_pipe(t_token *current, t_data *data)
{
	if (current->next && current->next->type == PIPE)
		return (print_syntax_error(current->next->value, data));
	return (true);
}

bool	check_special_redir_case(t_token *current, t_data *data, t_token **ptr)
{
	if (ft_strcmp(current->value, "<") == 0 && ft_strcmp(current->next->value,
			">") == 0)
	{
		if (!current->next->next)
			return (print_syntax_error("newline", data));
		if (current->next->next->type != COMMAND)
			return (print_syntax_error(current->next->next->value, data));
		*ptr = current->next;
		return (true);
	}
	return (print_syntax_error(current->next->value, data));
}

bool	check_redir_target(t_token *current, t_data *data)
{
	if (!current->next)
		return (print_syntax_error("newline", data));
	if (current->next->type != COMMAND)
		return (print_syntax_error(current->next->value, data));
	return (true);
}
