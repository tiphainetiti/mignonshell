/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:56 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 18:25:20 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"
# include <stdbool.h>
# include <unistd.h>

typedef struct s_envt
{
	char				*str;
	struct s_envt		*next;
}						t_envt;

typedef struct s_export
{
	char				*key;
	char				*value;
	struct s_export		*next;
}						t_export;

typedef struct s_token
{
	char				*value;
	size_t				type;
	struct s_token		*next;

}						t_token;

typedef struct s_inofile
{
	char				*filename;
	int					type;
	struct s_inofile	*next;
}						t_inofile;

typedef struct s_cmd
{
	char				**cmd;
	struct s_inofile	*file;
	int					nb_file;
	int					was_quoted;
	struct s_cmd		*next;

}						t_cmd;

typedef struct s_limiter
{
	char				*str;
	struct s_limiter	*next;

}						t_limiter;

typedef enum e_type
{
	COMMAND,
	REDIRECTION,
	PIPE,
	SEPARATOR,
	HEREDOC
}						t_type;

typedef struct s_quotes
{
	int					inside_double_quotes;
	int					inside_single_quotes;
}						t_quotes;

// Global
typedef struct s_data
{
	int					nb_cmd;
	t_token				*token;
	t_envt				*envt;
	t_cmd				*cmd;
	t_limiter			*limiter;
	t_export			*export;
	char				*path;
	int					infile;
	int					outfile;
	int					*pid;
	int					fd[2];
	int					tmp_fd;
	int					exit_code;
	char				lst_char_split;
	int					is_heredoc;
	int					tmp_heredoc;
	int					nb_heredoc;
	char				*file_name;
	int					error_file;

}						t_data;

typedef struct s_expand_state
{
	t_quotes			quotes;
	int					i;
	int					block_start;
	char				*result;
	char				*value;
	t_data				*data;
	t_envt				*env;
}						t_expand_state;

// Structure to hold expansion parameters
typedef struct s_quote_exp
{
	char				*value;
	int					i;
	char				quote_char;
	char				**result;
	t_quotes			quotes;
}						t_quote_exp;

// Structure for path normalization parameters
typedef struct s_path_params
{
	const char			*path;
	int					i;
	int					j;
	int					final_slashes;
	size_t				len;
}						t_path_params;

#endif