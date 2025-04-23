/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:04:16 by tlay              #+#    #+#             */
/*   Updated: 2025/04/23 18:09:25 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Get USER len
int	get_var_name_length(const char *str, int start)
{
	int	i;

	i = start;
	if (str[start] >= '0' && str[start] <= '9')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '*'))
		i++;
	return (i - start);
}

// Substract block and join with older block
char	*join_block(char *result, const char *value, int block_start,
		int block_end)
{
	char	*block;
	char	*temp;

	block = ft_substr(value, block_start, block_end - block_start);
	temp = ft_strjoin(result, block);
	free(result);
	free(block);
	return (temp);
}

// Get expanded value in env
char	*get_expanded(char *var_name, int var_len, t_envt *envt)
{
	t_envt	*env;
	char	*expanded;

	env = envt;
	expanded = NULL;
	while (env)
	{
		if (ft_strncmp(env->str, var_name, var_len) == 0
			&& env->str[var_len] == '=')
		{
			expanded = ft_substr(env->str, var_len + 1, ft_strlen(env->str)
					- var_len - 1);
			break ;
		}
		env = env->next;
	}
	return (expanded);
}

char	*append_to_result(char *result, char *to_append)
{
	char	*temp;

	temp = ft_strjoin(result, to_append);
	free(result);
	return (temp);
}

void	update_quotes_state(char current_char, t_quotes *quotes)
{
	if (current_char == '"' && !quotes->inside_single_quotes)
		quotes->inside_double_quotes = !quotes->inside_double_quotes;
	else if (current_char == '\'' && !quotes->inside_double_quotes)
		quotes->inside_single_quotes = !quotes->inside_single_quotes;
}

// char	*expand_variables(char *value, t_data *data)
// {
// 	t_envt		*env;
// 	t_quotes	quotes;
// 	int			i;
// 	int			block_start;
// 	char		*result;
// 	char		*temp;
// 	int			var_start;
// 	int			var_len;
// 	char		*var_name;
// 	char		*var_value;
// 	char		*exit_code;
// 	char		*quoted_content;
// 	int			start_quote;
// 	int			end_quote;

// 	env = data->envt;
// 	quotes.inside_double_quotes = 0;
// 	quotes.inside_single_quotes = 0;
// 	i = 0;
// 	block_start = 0;
// 	result = ft_strdup("");
// 	while (value[i])
// 	{
// 		update_quotes_state(value[i], &quotes);
// 		// Expansion de variables
// 		if (value[i] == '$' && !quotes.inside_single_quotes)
// 		{
// 			// Copie d'abord le texte entre block_start et i
// 			if (i > block_start)
// 				result = join_block(result, value, block_start, i);
// 			start_quote = i + 1;         // Position du premier "
// 			end_quote = start_quote + 1; // Commencer à chercher après le "
// 			while (value[end_quote] && value[end_quote] != '"')
// 				end_quote++;
// 			// Si on a trouvé le guillemet fermant
// 			if (value[end_quote] == '"')
// 			{
// 				// Ajouter le contenu entre guillemets (sans les guillemets)
// 				quoted_content = ft_substr(value, start_quote + 1, end_quote
// 						- start_quote - 1);
// 				temp = ft_strjoin(result, quoted_content);
// 				free(result);
// 				free(quoted_content);
// 				result = temp;
// 				// Avancer après le guillemet fermant
// 				i = end_quote + 1;
// 				block_start = i;
// 				continue ;
// 			}
// 			i++; // Saute le $
// 			// Traite le cas spécial $?
// 			if (value[i] == '?')
// 			{
// 				exit_code = ft_itoa(data->exit_code);
// 				temp = ft_strjoin(result, exit_code);
// 				free(result);
// 				free(exit_code);
// 				result = temp;
// 				i++;
// 				block_start = i;
// 				continue ;
// 			}
// 			// Détermine la longueur du nom de variable
// 			var_start = i;
// 			var_len = get_var_name_length(value, i);
// 			i += var_len;
// 			if (var_len > 0)
// 			{
// 				// Extraction du nom de variable
// 				var_name = ft_substr(value, var_start, var_len);
// 				// printf("var_name : %s\n", var_name);
// 				var_value = get_expanded(var_name, var_len, env);
// 				// printf("var_value : %s\n", var_value);
// 				// Ajout au résultat
// 				if (var_value)
// 				{
// 					result = append_to_result(result, var_value);
// 					free(var_value);
// 				}
// 				free(var_name);
// 				block_start = i;
// 				continue ;
// 			}
// 			else
// 			{
// 				// $ sans nom de variable valide - on le traite comme littéral
// 				temp = ft_strjoin(result, "$");
// 				free(result);
// 				result = temp;
// 				block_start = i;
// 				continue ;
// 			}
// 		}
// 		i++;
// 	}
// 	if (i > block_start)
// 		result = join_block(result, value, block_start, i);
// 	return (result);
// }

int	handle_quoted_expansion(char *value, int i, char quote_char, char **result,
		int *new_i)
{
	int		start;
	int		end;
	char	*content;
	char	*temp;

	start = i + 2;
	end = start;
	while (value[end] && value[end] != quote_char)
		end++;
	if (value[end] == quote_char)
	{
		content = ft_substr(value, start, end - start);
		temp = ft_strjoin(*result, content);
		free(content);
		free(*result);
		*result = temp;
		*new_i = end + 1;
		return (1);
	}
	return (0);
}

char	*expand_variables(char *value, t_data *data)
{
	t_envt		*env;
	t_quotes	quotes;
	int			i;
	int			block_start;
	char		*result;
	char		*temp;
	char		*var_name;
	char		*var_value;
	char		*exit_code;
	int			var_start;
	int			var_len;
	char		quoted_char;
	int			new_i;

	env = data->envt;
	quotes.inside_double_quotes = 0;
	quotes.inside_single_quotes = 0;
	i = 0;
	block_start = 0;
	result = ft_strdup("");
	while (value[i])
	{
		update_quotes_state(value[i], &quotes);
		// Gestion des variables
		if (value[i] == '$' && !quotes.inside_single_quotes)
		{
			// Copier le texte avant le $
			if (i > block_start)
				result = join_block(result, value, block_start, i);
			if (value[i + 1] == '"' || value[i + 1] == '\'')
			{
				quoted_char = value[i + 1];
				if (handle_quoted_expansion(value, i, quoted_char, &result,
						&new_i))
				{
					i = new_i;
					block_start = i;
					continue ;
				}
			}
			i++; // Passer le $
			// Cas spécial: $?
			if (value[i] == '?')
			{
				exit_code = ft_itoa(data->exit_code);
				temp = ft_strjoin(result, exit_code);
				free(result);
				free(exit_code);
				result = temp;
				i++;
				block_start = i;
				continue ;
			}
			// Extraire le nom de variable
			var_start = i;
			var_len = get_var_name_length(value, i);
			i += var_len;
			if (var_len > 0)
			{
				var_name = ft_substr(value, var_start, var_len);
				var_value = get_expanded(var_name, var_len, env);
				// Si la variable existe, ajouter sa valeur
				// Si elle n'existe pas, ne rien ajouter (chaîne vide)
				if (var_value)
				{
					result = append_to_result(result, var_value);
					free(var_value);
				}
				free(var_name);
				block_start = i;
				continue ;
			}
			else
			{
				// $ sans nom de variable - le traiter comme littéral
				temp = ft_strjoin(result, "$");
				free(result);
				result = temp;
				block_start = i;
				continue ;
			}
		}
		i++;
	}
	// Ajouter tout caractère restant
	if (i > block_start)
		result = join_block(result, value, block_start, i);
	return (result);
}

t_token	*skip_empty_token(t_token *current, t_token *prev, t_token **head)
{
	t_token	*next;

	next = current->next;
	if (prev)
		prev->next = current->next;
	else
		*head = current->next;
	free(current->value);
	free(current);
	return (next);
}

t_token	*expand_tokens(t_token *token, t_data *data)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;
	char	*expanded;
	int		i;

	current = token;
	head = token;
	i = 0;
	prev = NULL;
	while (current)
	{
		if (current->type == COMMAND)
		{
			expanded = expand_variables(current->value, data);
			free(current->value);
			current->value = expanded;
			if (expanded && *expanded)
			{
				i = 0;
				while (expanded && is_whitespace(expanded[i]))
					i++;
				if (!expanded[i])
				{
					current = skip_empty_token(current, prev, &head);
					continue ;
				}
			}
			else if (!expanded || !*expanded)
			{
				current = skip_empty_token(current, prev, &head);
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
	return (head);
}
