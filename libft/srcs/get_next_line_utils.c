/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:51:36 by tlay              #+#    #+#             */
/*   Updated: 2025/04/02 14:59:00 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(char *s, char ch)
{
	unsigned int	i;

	i = 0;
	if (!s || !ch)
		return (0);
	while (s[i])
	{
		if (s[i] == ch)
			return (1);
		i++;
	}
	if (s[i] == ch)
		return (1);
	return (0);
}

char	*ft_substr_gnl(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		len = 0;
	else if (start + len > ft_strlen_gnl(s))
		len = ft_strlen_gnl(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_gnl(char *s)
{
	size_t	size;
	size_t	i;
	char	*table;

	size = 0;
	i = 0;
	while (s[size])
		size++;
	table = (char *)malloc((size + 1) * sizeof(char));
	if (!table)
		return (NULL);
	while (s[i] && i < size)
	{
		table[i] = s[i];
		i++;
	}
	table[i] = '\0';
	return (table);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	size;
	char	*table;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	table = (char *)malloc((size + 1) * sizeof(char));
	if (table == NULL)
		return (NULL);
	while (s1[i])
	{
		table[i] = s1[i];
		i++;
	}
	while (s2[j])
		table[i++] = s2[j++];
	table[i] = '\0';
	return (table);
}
