/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:43:06 by tlay              #+#    #+#             */
/*   Updated: 2025/04/29 19:30:28 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Handles path normalization for the first argument if needed, ex :
/////bin//////ls
static char	*normalize_first_arg(char *arg, int arg_position)
{
	char	*normalized_arg;

	normalized_arg = NULL;
	if (arg_position == 0 && arg[0] == '/' && has_multiple_slashes(arg))
	{
		normalized_arg = normalize_path(arg);
		if (normalized_arg)
		{
			free(arg);
			return (normalized_arg);
		}
	}
	return (arg);
}

// Copies existing command arguments to a new array
static char	**create_expanded_cmd_array(t_cmd *cmd, int size)
{
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_cmd[i] = cmd->cmd[i];
		i++;
	}
	return (new_cmd);
}

// Add an argument to the command
void	add_arg_to_command(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_cmd;
	char	*unquoted_arg;

	i = 0;
	while (cmd->cmd[i])
		i++;
	new_cmd = create_expanded_cmd_array(cmd, i);
	if (!new_cmd)
		return ;
	unquoted_arg = remove_quotes(arg, cmd);
	if (!unquoted_arg)
		return (free(new_cmd));
	unquoted_arg = normalize_first_arg(unquoted_arg, i);
	new_cmd[i] = unquoted_arg;
	new_cmd[i + 1] = NULL;
	free(cmd->cmd);
	cmd->cmd = new_cmd;
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

// Redirection must be followed by a type COMMAND
static bool	handle_redirection_token(t_cmd *cmd, t_token **current)
{
	int	redir_type;

	if ((*current)->next && (*current)->next->type == COMMAND)
	{
		redir_type = convert_redirection_type((*current)->value);
		if (redir_type != -1)
		{
			add_redirection(cmd, (*current)->next->value, redir_type);
			*current = (*current)->next;
			return (true);
		}
	}
	return (false);
}

// Pipe token : Create a new command
static bool	handle_pipe_token(t_cmd **cmd)
{
	t_cmd	*new_cmd;

	new_cmd = create_command();
	if (!new_cmd)
		return (false);
	(*cmd)->next = new_cmd;
	*cmd = new_cmd;
	return (true);
}

// Go though each tokens
static bool	process_token_list(t_cmd *current_cmd, t_token *current)
{
	while (current)
	{
		if (current->type == COMMAND)
			add_arg_to_command(current_cmd, current->value);
		else if (current->type == REDIRECTION)
		{
			if (!handle_redirection_token(current_cmd, &current))
				return (false);
		}
		else if (current->type == PIPE)
		{
			if (!handle_pipe_token(&current_cmd))
				return (false);
		}
		current = current->next;
	}
	return (true);
}

/* Counts commands in linked list and assigns to data structure */
static void	count_and_assign_commands(t_data *data, t_cmd *cmd_head)
{
	t_cmd	*current;

	current = cmd_head;
	while (current)
	{
		data->nb_cmd++;
		current = current->next;
	}
	data->cmd = cmd_head;
}

bool	build_commands(t_data *data, t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;

	current_cmd = create_command();
	if (!current_cmd)
		return (false);
	cmd_head = current_cmd;
	if (!process_token_list(current_cmd, tokens))
		return (false);
	count_and_assign_commands(data, cmd_head);
	free_tokens(tokens);
	return (true);
}

// Add a argument to the command
// void	add_arg_to_command(t_cmd *cmd, char *arg)
// {
// 	int		i;
// 	char	**new_cmd;
// 	char	*unquoted_arg;
// 	char	*normalized_arg;

// 	normalized_arg = NULL;
// 	i = 0;
// 	while (cmd->cmd[i])
// 		i++;
// 	new_cmd = malloc(sizeof(char *) * (i + 2));
// 	if (!new_cmd)
// 		return ;
// 	i = 0;
// 	while (cmd->cmd[i])
// 	{
// 		new_cmd[i] = cmd->cmd[i];
// 		i++;
// 	}
// 	unquoted_arg = remove_quotes(arg, cmd);
// 	if (!unquoted_arg)
// 		return (free(new_cmd));
// 	if (i == 0 && unquoted_arg[0] == '/' && has_multiple_slashes(unquoted_arg))
// 	{
// 		normalized_arg = normalize_path(unquoted_arg);
// 		if (normalized_arg)
// 		{
// 			free(unquoted_arg);
// 			unquoted_arg = normalized_arg;
// 		}
// 	}
// 	new_cmd[i] = unquoted_arg;
// 	new_cmd[i + 1] = NULL;
// 	free(cmd->cmd);
// 	cmd->cmd = new_cmd;
// }

// static char	*normalize_path(const char *path)
// {
// 	int		i;
// 	int		j;
// 	int		final_slashes;
// 	size_t	len;
// 	char	*normalized;

// 	i = 0;
// 	j = 0;
// 	final_slashes = number_of_final_slashes(path);
// 	len = ft_strlen(path);
// 	normalized = malloc(len + 1);
// 	if (!normalized)
// 		return (NULL);
// 	if (path[i] == '/')
// 	{
// 		normalized[j++] = '/';
// 		i++;
// 		while (path[i] == '/')
// 			i++;
// 	}
// 	while (path[i] && (i < (int)len - final_slashes))
// 	{
// 		if (path[i] == '/')
// 		{
// 			normalized[j++] = '/';
// 			i++;
// 			while (path[i] == '/' && (i < (int)len - final_slashes))
// 				i++;
// 		}
// 		else
// 			normalized[j++] = path[i++];
// 	}
// 	return (copy_final_slashes(normalized, final_slashes, j));
// }

// bool	build_commands(t_data *data, t_token *tokens)
// {
// 	t_cmd	*cmd_head;
// 	t_cmd	*current_cmd;
// 	t_token	*current;
// 	int		redir_type;
// 	t_cmd	*new_cmd;

// 	cmd_head = NULL;
// 	current_cmd = NULL;
// 	current = tokens;
// 	current_cmd = create_command();
// 	if (!current_cmd)
// 		return (false);
// 	cmd_head = current_cmd;
// 	while (current)
// 	{
// 		if (current->type == COMMAND)
// 			add_arg_to_command(current_cmd, current->value);
// 		else if (current->type == REDIRECTION)
// 		{
// 			if (current->next && current->next->type == COMMAND)
// 			{
// 				redir_type = convert_redirection_type(current->value);
// 				if (redir_type != -1)
// 				{
// 					add_redirection(current_cmd, current->next->value,
// 						redir_type);
// 					current = current->next;
// 				}
// 				else
// 					return (false);
// 			}
// 		}
// 		else if (current->type == PIPE)
// 		{
// 			new_cmd = create_command();
// 			if (!new_cmd)
// 				return (false);
// 			current_cmd->next = new_cmd;
// 			current_cmd = new_cmd;
// 		}
// 		current = current->next;
// 	}
// 	data->cmd = cmd_head;
// 	data->nb_cmd = 0;
// 	current_cmd = cmd_head;
// 	while (current_cmd)
// 	{
// 		data->nb_cmd++;
// 		current_cmd = current_cmd->next;
// 	}
// 	free_tokens(tokens);
// 	return (true);
// }
