/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:30:46 by tlay              #+#    #+#             */
/*   Updated: 2025/04/02 14:36:59 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
size_t	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}
/*
int	main(void)
{
	char str[] = "hello maurice 1!";

	printf("%d\n", ft_strlen(str));
	return (0);
}*/