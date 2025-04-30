/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:36 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 14:45:01 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int			i;
	t_inofile	*current_file;
	t_inofile	*next_file;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		i = 0;
		while (cmd->cmd[i] != NULL)
		{
			free(cmd->cmd[i]);
			i++;
		}
		free(cmd->cmd);
	}
	current_file = cmd->file;
	while (current_file)
	{
		next_file = current_file->next;
		free(current_file->filename);
		free(current_file);
		current_file = next_file;
	}
	free(cmd);
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *cmd;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
	cmd = NULL;
}

void	free_redirection(t_inofile *file)
{
	t_inofile	*current;
	t_inofile	*next;

	current = file;
	while (current)
	{
		if (current->filename)
			free(current->filename);
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

// Fonction pour afficher les tokens (debug)
void	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	printf("\n--- TOKENS ---\n");
	while (current)
	{
		printf("Token %d: [%s] - Type: ", i++, current->value);
		if (current->type == COMMAND)
			printf("COMMAND\n");
		else if (current->type == PIPE)
			printf("PIPE\n");
		else if (current->type == REDIRECTION)
			printf("REDIRECTION\n");
		else
			printf("UNKNOWN (%zu)\n", current->type);
		current = current->next;
	}
	printf("-------------\n\n");
}

// Print command structures
void	print_commands(t_cmd *cmds)
{
	t_cmd		*current_cmd;
	t_inofile	*current_file;
	int			cmd_idx;
	int			arg_idx;

	current_cmd = cmds;
	cmd_idx = 0;
	printf("\n=== COMMANDS ===\n");
	while (current_cmd)
	{
		printf("Command %d:\n", cmd_idx++);
		if (current_cmd->cmd)
		{
			printf("  Arguments:\n");
			arg_idx = 0;
			while (current_cmd->cmd[arg_idx])
			{
				printf("    [%d]: %s\n", arg_idx, current_cmd->cmd[arg_idx]);
				arg_idx++;
			}
		}
		else
			printf("  No arguments\n");
		printf("  Redirections (%d):\n", current_cmd->nb_file);
		current_file = current_cmd->file;
		while (current_file)
		{
			printf("    Type: ");
			if (current_file->type == INFILE)
				printf("INPUT (<)");
			else if (current_file->type == OUTFILE)
				printf("OUTPUT (>)");
			else if (current_file->type == APPEND)
				printf("APPEND (>>)");
			else if (current_file->type == HERE_DOC)
				printf("HEREDOC (<<)");
			else
				printf("UNKNOWN (%d)", current_file->type);
			printf(", File: '%s'\n", current_file->filename);
			current_file = current_file->next;
		}
		if (current_cmd->next)
			printf("  [PIPE] -> Command %d\n", cmd_idx);
		printf("\n");
		current_cmd = current_cmd->next;
	}
	printf("===============\n\n");
}
