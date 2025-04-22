/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:36 by tlay              #+#    #+#             */
/*   Updated: 2025/04/22 17:24:46 by tlay             ###   ########.fr       */
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

void	free_cmds(t_cmd *cmd)
{
	t_cmd		*current;
	t_cmd		*next;
	t_inofile	*file;
	t_inofile	*next_file;
	int			i;

	current = cmd;
	while (current)
	{
		// Libérer les arguments
		if (current->cmd)
		{
			i = 0;
			while (current->cmd[i])
				free(current->cmd[i++]);
			free(current->cmd);
		}
		// Libérer les redirections
		file = current->file;
		while (file)
		{
			next_file = file->next;
			if (file->filename)
				free(file->filename);
			free(file);
			file = next_file;
		}
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_limiter(t_limiter *limiter)
{
	if (limiter != NULL)
	{
		free(limiter->str);
		free(limiter);
	}
}

void	free_limiter_list(t_limiter **limiter)
{
	t_limiter	*current;
	t_limiter	*next;

	if (limiter == NULL)
		return ;
	current = *limiter;
	while (current)
	{
		next = current->next;
		free_limiter(current);
		current = next;
	}
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

void	free_commands(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = cmds;
	while (current)
	{
		if (current->cmd)
		{
			i = 0;
			while (current->cmd[i])
			{
				free(current->cmd[i]);
				i++;
			}
			free(current->cmd);
		}
		free_redirection(current->file);
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdups(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s) + 1;
	dup = malloc(len);
	if (dup)
		ft_memcpy(dup, s, len);
	return (dup);
}
