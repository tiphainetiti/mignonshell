/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:49:44 by tlay              #+#    #+#             */
/*   Updated: 2025/04/23 19:02:50 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create empty command
t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = malloc(sizeof(char *));
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd[0] = NULL;
	cmd->file = NULL;
	cmd->nb_file = 0;
	cmd->next = NULL;
	return (cmd);
}

// Remove quotes from command or file
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	int		in_single_quotes;
	int		in_doubles_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_doubles_quotes = 0;
	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !in_single_quotes)
			in_doubles_quotes = !in_doubles_quotes;
		else if (str[i] == '\'' && !in_doubles_quotes)
			in_single_quotes = !in_single_quotes;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

// Add a argument to the command
void	add_arg_to_command(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_cmd;
	char	*unquoted_arg;

	i = 0;
	while (cmd->cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd)
		return ;
	i = 0;
	while (cmd->cmd[i])
	{
		new_cmd[i] = cmd->cmd[i];
		i++;
	}
	unquoted_arg = remove_quotes(arg);
	if (!unquoted_arg)
		return (free(new_cmd));
	new_cmd[i] = unquoted_arg;
	new_cmd[i + 1] = NULL;
	free(cmd->cmd);
	cmd->cmd = new_cmd;
}

// Add redirection (t_inofile) to a cmd
void	add_redirection(t_cmd *cmd, char *filename, int type)
{
	t_inofile	*new_file;
	t_inofile	*current;
	char		*unquoted_filename;

	new_file = malloc(sizeof(t_inofile));
	if (!new_file)
		return ;
	unquoted_filename = remove_quotes(filename);
	if (!unquoted_filename)
	{
		free(new_file);
		return ;
	}
	new_file->filename = unquoted_filename;
	new_file->type = type;
	new_file->next = NULL;
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

bool	build_commands(t_data *data, t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;
	t_token	*current;
	int		redir_type;
	t_cmd	*new_cmd;

	cmd_head = NULL;
	current_cmd = NULL;
	current = tokens;
	current_cmd = create_command();
	if (!current_cmd)
		return (false);
	cmd_head = current_cmd;
	while (current)
	{
		if (current->type == COMMAND)
			add_arg_to_command(current_cmd, current->value);
		else if (current->type == REDIRECTION)
		{
			if (current->next && current->next->type == COMMAND)
			{
				redir_type = convert_redirection_type(current->value);
				if (redir_type != -1)
				{
					add_redirection(current_cmd, current->next->value,
						redir_type);
					current = current->next;
				}
				else
					return (false);
			}
		}
		else if (current->type == PIPE)
		{
			new_cmd = create_command();
			if (!new_cmd)
				return (false);
			current_cmd->next = new_cmd;
			current_cmd = new_cmd;
		}
		current = current->next;
	}
	data->cmd = cmd_head;
	data->nb_cmd = 0;
	current_cmd = cmd_head;
	while (current_cmd)
	{
		data->nb_cmd++;
		current_cmd = current_cmd->next;
	}
	free_tokens(tokens);
	return (true);
}
