/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:56 by tlay              #+#    #+#             */
/*   Updated: 2025/04/25 16:05:38 by tlay             ###   ########.fr       */
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
	char *value;          // Valeur du token (mot, opérateur)
	size_t type;          // Type du token (WORD, PIPE, REDIR_IN, etc.)
	struct s_token *next; // Pointeur vers le token suivant (liste chaînée)

}						t_token;

typedef struct s_inofile
{
	char *filename;         // Nom du fichier
	int type;               // Type de redirection (IN, OUT, APPEND, HEREDOC)
	struct s_inofile *next; // Redirection suivante
}						t_inofile;

typedef struct s_cmd
{
	char **cmd;             // Tableau d'arguments (cmd[0] = commande)
	struct s_inofile *file; // Liste des redirections
	int nb_file;            // Nombre de redirections
	int was_quoted;         // Il y avait des quotes en token
	struct s_cmd *next;     // Commande suivante dans un pipeline

}						t_cmd;
// Fonction: Structure finale après parsing, prête pour l'exécution.
// cmd est un tableau de strings terminé par NULL
// Le premier élément est la commande, les suivants sont les arguments
// Contient les redirections associées à cette commande

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

typedef struct s_cmd_str_token
{
	char				*cmd_str;
	t_cmd				**last_cmd;
	t_token				**token;
	t_data				*data;
	t_cmd				**cmd;
}						t_cmd_str_token;

// Only parsing
typedef struct handle_cmd_str_args
{
	t_cmd				**last_cmd;
	t_token				**token;
	t_data				*data;
	t_cmd				**cmd;
	t_token				*tmp;
}						t_handle_cmd_str_args;

typedef struct s_process_token_args
{
	char				**cursor;
	bool				*expect_command;
	bool				*expect_file;
	t_data				*data;
	char				*input;
}						t_process_token_args;

typedef struct s_process_token2_args
{
	t_cmd				**last_cmd;
	t_token				**token;
	t_data				*data;
	t_cmd				**cmd;
	t_token				*tmp;
}						t_process_token2_args;

#endif