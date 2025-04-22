/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:12:17 by tlay              #+#    #+#             */
/*   Updated: 2025/04/17 16:07:32 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// t_cmd	*create_command(void)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return (NULL);
// 	// Allouer le tableau d'arguments avec juste NULL
// 	cmd->cmd = malloc(sizeof(char *));
// 	if (!cmd->cmd)
// 	{
// 		free(cmd);
// 		return (NULL);
// 	}
// 	cmd->cmd[0] = NULL;
// 	cmd->file = NULL;
// 	cmd->nb_file = 0;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// void	add_arg_to_command(t_cmd *cmd, char *arg)
// {
// 	int		i;
// 	char	**new_cmd;

// 	// Compter les arguments existants
// 	i = 0;
// 	while (cmd->cmd[i])
// 		i++;
// 	// Créer un tableau plus grand
// 	new_cmd = malloc(sizeof(char *) * (i + 2));
// 	if (!new_cmd)
// 		return ;
// 	// Copier les arguments existants
// 	i = 0;
// 	while (cmd->cmd[i])
// 	{
// 		new_cmd[i] = cmd->cmd[i];
// 		i++;
// 	}
// 	// Ajouter le nouvel argument
// 	new_cmd[i] = ft_strdup(arg);
// 	new_cmd[i + 1] = NULL;
// 	// Remplacer l'ancien tableau
// 	free(cmd->cmd);
// 	cmd->cmd = new_cmd;
// }

// void	add_redirection(t_cmd *cmd, int type, char *filename)
// {
// 	t_inofile	*new_file;
// 	t_inofile	*current;

// 	// Créer la nouvelle redirection
// 	new_file = malloc(sizeof(t_inofile));
// 	if (!new_file)
// 		return ;
// 	new_file->filename = ft_strdup(filename);
// 	new_file->type = type;
// 	new_file->next = NULL;
// 	// Ajouter à la fin de la liste des redirections
// 	if (!cmd->file)
// 	{
// 		cmd->file = new_file;
// 	}
// 	else
// 	{
// 		current = cmd->file;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_file;
// 	}
// 	// Incrémenter le compteur de redirections
// 	cmd->nb_file++;
// }

// int	convert_redirection_type(char *token_value)
// {
// 	if (ft_strcmp(token_value, "<") == 0)
// 		return (INFILE);
// 	else if (ft_strcmp(token_value, ">") == 0)
// 		return (OUTFILE);
// 	else if (ft_strcmp(token_value, ">>") == 0)
// 		return (APPEND);
// 	else if (ft_strcmp(token_value, "<<") == 0)
// 		return (HERE_DOC);
// 	return (-1); // Type non reconnu
// }

// bool	build_commands(t_data *data)
// {
// 	t_cmd	*cmd_head;
// 	t_cmd	*current_cmd;
// 	t_token	*current;
// 	int		redir_type;
// 	t_cmd	*new_cmd;

// 	cmd_head = NULL;
// 	current_cmd = NULL;
// 	current = data->token;
// 	// Créer la première commande
// 	current_cmd = create_command();
// 	if (!current_cmd)
// 		return (false);
// 	cmd_head = current_cmd;
// 	while (current)
// 	{
// 		if (current->type == COMMAND)
// 		{
// 			add_arg_to_command(current_cmd, current->value);
// 		}
// 		else if (current->type == REDIRECTION)
// 		{
// 			// Le token suivant doit être le nom du fichier
// 			if (current->next && current->next->type == COMMAND)
// 			{
// 				redir_type = convert_redirection_type(current->value);
// 				if (redir_type != -1)
// 				{
// 					add_redirection(current_cmd, redir_type,
// 						current->next->value);
// 					current = current->next; // Saute le token filename
// 				}
// 			}
// 			else
// 			{
// 				// Erreur: pas de nom de fichier après la redirection
// 				return (false);
// 			}
// 		}
// 		else if (current->type == PIPE)
// 		{
// 			// Créer une nouvelle commande
// 			new_cmd = create_command();
// 			if (!new_cmd)
// 				return (false);
// 			current_cmd->next = new_cmd;
// 			current_cmd = new_cmd;
// 		}
// 		current = current->next;
// 	}
// 	// Stocker la liste des commandes dans data
// 	data->cmd = cmd_head;
// 	// Compter le nombre de commandes
// 	data->nb_cmd = 0;
// 	current_cmd = cmd_head;
// 	while (current_cmd)
// 	{
// 		data->nb_cmd++;
// 		current_cmd = current_cmd->next;
// 	}
// 	return (true);
// }

// void	free_commands(t_cmd *cmd)
// {
// 	t_cmd	*current;
// 	t_cmd	*next;
// 	int		i;

// 	current = cmd;
// 	while (current)
// 	{
// 		// Libérer les arguments
// 		if (current->cmd)
// 		{
// 			i = 0;
// 			while (current->cmd[i])
// 			{
// 				free(current->cmd[i]);
// 				i++;
// 			}
// 			free(current->cmd);
// 		}
// 		// Libérer les redirections
// 		free_redirections(current->file);
// 		// Passer à la commande suivante
// 		next = current->next;
// 		free(current);
// 		current = next;
// 	}
// }

// void	free_redirections(t_inofile *file)
// {
// 	t_inofile	*current;
// 	t_inofile	*next;

// 	current = file;
// 	while (current)
// 	{
// 		if (current->filename)
// 			free(current->filename);
// 		next = current->next;
// 		free(current);
// 		current = next;
// 	}
// }

// // Après l'expansion
// data->token = expand_tokens(data->token, data);

// // Construction des commandes
// if (!build_commands(data))
// {
//     // Gestion d'erreur: impossible de construire les commandes
//     return (false);
// }

// // À partir d'ici, data->cmd contient toutes tes commandes structurées
// // Prêt pour l'exécution