/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:25:08 by tlay              #+#    #+#             */
/*   Updated: 2025/04/22 14:23:42 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "defines.h"
# include "exec.h"
# include "include.h"
# include "parsing.h"
# include "structures.h"
# include "utils.h"

extern int	g_sig;

// main
void		split_env_var(char *str, char **key, char **value);
int			main(int argc, char **argv, char **env);

#endif
