/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:01:29 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 19:01:55 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Process quotes in a string and copy non-quote chars to result
static void	process_quotes(char *str, char *result, int *j, t_quotes *quotes)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !quotes->inside_single_quotes)
			quotes->inside_double_quotes = !quotes->inside_double_quotes;
		else if (str[i] == '\'' && !quotes->inside_double_quotes)
			quotes->inside_single_quotes = !quotes->inside_single_quotes;
		else
			result[(*j)++] = str[i];
		i++;
	}
	result[*j] = '\0';
}

// Remove quotes from command or file
char	*remove_quotes(char *str, t_cmd *cmd)
{
	int			i;
	int			j;
	char		*result;
	t_quotes	quotes;

	i = 0;
	j = 0;
	quotes = (t_quotes){0, 0};
	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	process_quotes(str, result, &j, &quotes);
	cmd->was_quoted = was_quoted(str, result);
	return (result);
}
