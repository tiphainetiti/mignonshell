/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:42:46 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 14:44:36 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_limiter(t_limiter *limiter)
{
	if (limiter != NULL)
	{
		free(limiter->str);
		free(limiter);
	}
}

void	free_limiter_list(t_limiter **limiter)
{
	t_limiter	*current;
	t_limiter	*next;

	if (limiter == NULL)
		return ;
	current = *limiter;
	while (current)
	{
		next = current->next;
		free_limiter(current);
		current = next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdups(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s) + 1;
	dup = malloc(len);
	if (dup)
		ft_memcpy(dup, s, len);
	return (dup);
}
