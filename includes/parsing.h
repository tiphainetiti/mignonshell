/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:44 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 15:31:21 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/************************		PARSING		************************/

// cmds.c
bool	build_commands(t_data *data, t_token *tokens);

// cmds_utils_1.c
t_cmd	*create_command(void);
int		was_quoted(char *str, char *result);
char	*copy_final_slashes(char *normalized, int final_slashes, int j);
int		number_of_final_slashes(const char *path);
void	count_and_assign_commands(t_data *data, t_cmd *cmd_head);

// cmds_utils_2.c
char	**create_expanded_cmd_array(t_cmd *cmd, int size);

// cmds_redir.c
int		convert_redirection_type(char *token_value);
void	add_redirection(t_cmd *cmd, char *filename, int type);

// cmds_quotes.c
char	*remove_quotes(char *str, t_cmd *cmd);

// cmds_path.c
char	*normalize_first_arg(char *arg, int arg_position);

// expand.c
char	*expand_variables(char *value, t_data *data);
t_token	*skip_empty_token(t_token *current, t_token *prev, t_token **head);
t_token	*expand_tokens(t_token *token, t_data *data);

// expand_utils_1.c
int		get_var_name_length(const char *str, int start);
char	*join_block(char *result, const char *value, int block_start,
			int block_end);
char	*get_expanded(char *var_name, int var_len, t_envt *envt);
char	*append_to_result(char *result, char *to_append);
void	update_quotes_state(char current_char, t_quotes *quotes);

// expand_utils_2.c
void	process_dollar(t_expand_state *state);

// expand_utils_3.c
char	*empty_quoted_expansion(char *result, t_quotes quotes);
int		handle_quoted_expansion(char *value, int i, char quote_char,
			char **result);

// syntax.c
bool	check_syntax(t_token *tokens, t_data *data);

// syntax_utils_1.c
bool	print_syntax_error(char *value, t_data *data);
bool	print_quotes_error(char quotes_type, t_data *data);
bool	check_token_quotes(t_token *token, int *in_quotes, char *quotes_type);
void	get_quotes_state(char c, int *in_quotes, char *quotes_type);

// syntax_utils_2.c
bool	check_redirection_pipe(t_token *current, t_data *data);
bool	check_special_redir_case(t_token *current, t_data *data, t_token **ptr);
bool	check_redir_target(t_token *current, t_data *data);

// tokens.c
t_token	*tokenize(char *input, t_data *data);

// tokens_utils.c
bool	is_whitespace(char c);
bool	is_special_char(char c);
t_token	*create_token(char *value, int type);
void	check_heredoc(char *temp, t_data *data);

// utils_1.c
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd **cmd);
void	free_redirection(t_inofile *file);
void	free_tokens(t_token *tokens);
void	print_tokens(t_token *tokens);
void	print_commands(t_cmd *cmds);

// utils_2.c
void	free_limiter(t_limiter *limiter);
void	free_limiter_list(t_limiter **limiter);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdups(const char *s);

// // old
// t_cmd		*pars_cmd(t_token **token, t_data *data);
// t_token		*create_token(char *value, size_t type);
// void		append_token(t_token **head, t_token *token);
// t_token		*tokenize(char *input, t_data *data);
// int			ft_strcmp(char *s1, char *s2);
// void		free_cmd(t_cmd *cmd);
// int			count_pipe(t_token *token);
// bool		check_syntax_errors(t_data *data, char *input);
// int			init_data(t_data *data);
// void		add_limiter(t_limiter **limiter, char *str);
// char		*ft_strdups(const char *s);
// int			is_separator(char c);
// bool		is_redirection(const char *str);
// bool		check_quotes_closed(const char *input);
// char		**split_with_quotes(const char *input, size_t *num_tokens);
// size_t		identify_type(char *value);
// char		*expand_variable(char *token, t_data *data);
// void		free_limiter(t_limiter *limiter);

// void		free_token_list(t_token **head);
// char		*expand_variable_main_loop(char *expanded, char *cursor,
// 				t_data *data, t_quotes *quotes);
// void		free_cmd_list(t_cmd **cmd);
// char		*handle_single_quotes_main(char *expanded, char **cursor,
// 				int *inside_single_quotes);
// char		*handle_double_quotes_main(char *expanded, char **cursor,
// 				int *inside_double_quotes);
// char		*process_cursor(char *expanded, char **cursor, t_data *data,
// 				t_quotes *quotes);
// void		free_limiter_list(t_limiter **limiter);
// void		skip_whitespace(char **cursor);
// bool		only_spaces_left(const char *str);
// bool		is_end_of_string(char *cursor);
// void		skip_spaces(char **cursor);
// bool		is_parenthesis(char c);
// bool		is_sep(char c);
// void		advance_cursor(char **cursor);
// bool		process_token(t_process_token_args args);
// char		*handle_double_quotes_main(char *expanded, char **cursor,
// 				int *inside_double_quotes);
// char		*handle_single_quotes_main(char *expanded, char **cursor,
// 				int *inside_single_quotes);
// char		*handle_dollar_sign_main(char *expanded, char **cursor,
// 				t_data *data);
// char		*handle_dollar_sign_main2(char *expanded, char **cursor,
// 				t_data *data);
// char		*append_char(char *expanded, char **cursor);
// char		*handle_consecutive_quotes_main(char *expanded, char **cursor);
// char		*handle_double_quotes_main_loop(char *expanded, char **cursor,
// 				int *inside_double_quotes);
// char		*handle_single_quotes_main_loop(char *expanded, char **cursor,
// 				int *inside_single_quotes);
// char		*handle_dollar_sign_main_loop(char *expanded, char **cursor,
// 				t_data *data);
// char		*handle_dollar_sign_main_loop2(char *expanded, char **cursor,
// 				t_data *data);
// char		*append_char_main(char *expanded, char **cursor);
// bool		is_numeric(char c);
// char		*find_env_value(t_envt *env, char *key);
// char		*handle_end_of_string(char *expanded);
// char		*handle_question_mark(char *expanded, char **cursor, t_data *data);
// char		*handle_alnum_or_underscore(char *expanded, char **cursor,
// 				t_data *data);
// char		*handle_default_case(char *expanded);
// char		*handle_num(char *expanded, char **cursor, t_data *data);
// char		*handle_double_quote(char *expanded, char **cursor);
// char		*append_char_to_expanded(char *expanded, char c);
// char		*handle_dollar_sign(char *expanded, char **cursor, t_data *data);
// char		*handle_dollar_sign2(char *expanded, char **cursor, t_data *data);
// char		*handle_double_quotes(char *expanded, char **cursor,
// 				int *inside_double_quotes);
// char		*handle_single_quotes(char *expanded, char **cursor,
// 				int *inside_single_quotes);
// char		*handle_consecutive_quotes(char *expanded, char **cursor);
// int			should_append_token(t_token *token);
// int			get_redirection_type(char *value);
// t_cmd		*init_cmd(void);
// char		*append_token_value(char *cmd_str, char *token_value);
// int			is_redirection_token(t_token *token);
// const char	*skip_separators(const char *str);
// void		free_tokens(char **tokens, size_t i);
// t_cmd		*initialize_cmd(void);
// size_t		calculate_token_length(const char **str);
// void		add_inofile(t_cmd *cmd, char *filename, int type);
// char		*allocate_token(size_t length);
// size_t		count_tokens(const char *str);
// char		**allocate_tokens2(size_t count);
// char		*extract_token(const char **str);
// int			handle_pipe2(t_cmd **last_cmd, t_token **token, t_cmd **cmd);
// char		**process_cmd_str(char *cmd_str, size_t *num_tokens);
// void		handle_redirections(t_cmd *cmd, t_token **token,
// 				t_limiter **limiter);
// char		*concat_token(t_token **token);
// void		update_quote_state(const char **str, int *in_quotes,
// 				char *quote_char);
// char		*handle_dollar_signe_d_quotes(char *expanded, char **cursor);
// char		*handle_dollar_sign(char *expanded, char **cursor, t_data *data);
// char		*handle_dollar_signe2_s_quotes(char *expanded, char **cursor,
// 				t_data *data);
// char		*tolong(char *filename, int type, t_inofile *new_inofile);

#endif
