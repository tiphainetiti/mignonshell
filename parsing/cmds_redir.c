/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:30:53 by tlay              #+#    #+#             */
/*   Updated: 2025/05/05 19:50:43 by tlay             ###   ########.fr       */
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

t_inofile	*create_inofile(char *filename, int type)
{
	t_inofile	*new_inofile;

	new_inofile = malloc(sizeof(t_inofile));
	if (!new_inofile)
		return (NULL);
	if (type == HERE_DOC)
		new_inofile->filename = ft_strdup("heredoc");
	else
		new_inofile->filename = ft_strdup(filename);
	if (!new_inofile->filename)
	{
		free(new_inofile);
		return (NULL);
	}
	new_inofile->type = type;
	new_inofile->next = NULL;
	return (new_inofile);
}

static void	add_limiter(t_limiter **limiter, char *str, int quoted)
{
	t_limiter	*new_limiter;
	t_limiter	*current;

	if (!str)
		return ;
	new_limiter = malloc(sizeof(t_limiter));
	if (!new_limiter)
		return ;
	new_limiter->str = ft_strdups(str);
	if (!new_limiter->str)
	{
		free(new_limiter);
		return ;
	}
	new_limiter->quoted = quoted;
	new_limiter->next = NULL;
	if (*limiter == NULL)
		*limiter = new_limiter;
	else
	{
		current = *limiter;
		while (current->next != NULL)
			current = current->next;
		current->next = new_limiter;
	}
}

// Add redirection (t_inofile) to a cmd (input, output, append or heredoc)
void	add_redirection(t_cmd *cmd, char *filename, int type,
		t_limiter **limiter)
{
	t_inofile	*new_file;
	char		*unquoted_filename;
	int			quoted;

	quoted = 0;
	unquoted_filename = remove_quotes(filename, cmd);
	if (!unquoted_filename)
		return ;
	quoted = was_quoted(filename, unquoted_filename);
	new_file = create_inofile(unquoted_filename, type);
	if (!new_file)
		return (free(unquoted_filename));
	append_file_to_cmd(cmd, new_file);
	if (type == HERE_DOC)
		add_limiter(limiter, unquoted_filename, quoted);
	free(unquoted_filename);
}
