/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:23:10 by tlay              #+#    #+#             */
/*   Updated: 2025/04/02 15:12:48 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int	ft_putchar(int c);
int	ft_print_char(int c);
int	ft_print_hexa(unsigned int nb, char input);
int	ft_print_nbr(long long nbr);
int	ft_print_ptr(void *ptr);
int	ft_print_str(char *str);
int	ft_printf(const char *str, ...);
int	ft_print_unsigned(unsigned int nb);

#endif