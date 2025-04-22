/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:52:52 by tlay              #+#    #+#             */
/*   Updated: 2025/04/02 14:55:01 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen_gnl(char *str);
int		ft_strchr_gnl(char *s, char ch);
char	*ft_substr_gnl(char *s, int start, int len);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *s);
char	*get_next_line(int fd);

#endif