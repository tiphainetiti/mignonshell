/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:03:25 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 14:51:04 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isprint(int ch)
{
	if (ch >= ' ' && ch <= '~')
		return (1);
	return (0);
}
/*
int	main(void)
{
	char test = 't';
	if (ft_isprint(test))
		printf("%c is printable\n", test);
	else
		printf("%c is not printable\n", test);
	return (0);
}*/