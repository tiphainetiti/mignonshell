/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:30:53 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 14:36:02 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	convert_redirection_type(char *token_value)
{
	if (ft_strncmp(token_value, "<", 2) == 0)
		return (INFILE);
	else if (ft_strncmp(token_value, ">", 2) == 0)
		return (OUTFILE);
	else if (ft_strncmp(token_value, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(token_value, "<<", 2) == 0)
		return (HERE_DOC);
	else
		return (-1);
}

// Adds a new file node to the end of the command's file list
static void	append_file_to_cmd(t_cmd *cmd, t_inofile *new_file)
{
	t_inofile	*current;

	if (!cmd->file)
		cmd->file = new_file;
	else
	{
		current = cmd->file;
		while (current->next)
			current = current->next;
		current->next = new_file;
	}
	cmd->nb_file++;
}

// Add redirection (t_inofile) to a cmd (input, output, append or heredoc)
void	add_redirection(t_cmd *cmd, char *filename, int type)
{
	t_inofile	*new_file;
	char		*unquoted_filename;

	new_file = malloc(sizeof(t_inofile));
	if (!new_file)
		return ;
	unquoted_filename = remove_quotes(filename, cmd);
	if (!unquoted_filename)
	{
		free(new_file);
		return ;
	}
	new_file->filename = unquoted_filename;
	new_file->type = type;
	new_file->next = NULL;
	append_file_to_cmd(cmd, new_file);
}
