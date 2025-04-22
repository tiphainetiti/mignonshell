/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:03:08 by tlay              #+#    #+#             */
/*   Updated: 2025/04/02 15:03:25 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*copy;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	copy = malloc((n + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (i < n && src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
