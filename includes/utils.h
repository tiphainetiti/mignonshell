/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:28:05 by tlay              #+#    #+#             */
/*   Updated: 2025/05/05 19:26:57 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// init_struct

int			init_data(t_data *data);
void		make_struct_export(t_export *node, t_export *current_export,
				t_export **export);
t_export	*create_export_node(char *key, char *value);
int			get_export(t_export **export, t_envt **envt);
void		split_env_var(char *str, char **key, char **value);

// get_env

void		free_envt(t_envt *envt);
void		make_struct_env(t_envt *node, t_envt *current, t_envt **envt);
int			get_env(t_envt **envt, char **env);
char		**make_env_tab(t_envt *envt);

// get_inofile

void		save_inofile(t_data *data, t_inofile *current, int fd);
int			*get_inofile(t_data *data, t_cmd *cmd, int *fd_array);
void		close_fd(t_data *data, int *fd_array);
void		get_fd_array(t_data *data);

// open_file

void		error_open(t_data *data, t_inofile *current, int fd);
int			open_input_file(t_data *data, t_inofile *current);
int			open_output_file(t_data *data, t_inofile *current);

// get_path

char		**get_all_path(t_data *data, t_envt *envt, char *word);
char		**make_good_path(t_data *data, char **tab_path, char *word);
void		check_command_split(t_data *data, char *cmd);
void		get_path(t_data *data);

// signaux
void		handle_signal(int i);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		setup_signal_handling(void);
void		disable_echoctl(void);

// heredoc_utils

char		*search_filename(t_data *data, char *filename);
int			ft_open_file(t_data *data, char **filename);
void		ft_process_file(t_data *data, int file);
char		*ft_init_file(t_data *data);
// char		*get_env_var(char *var_name, t_envt *envt);
// char		*expand_heredoc_line(char *line, t_envt *envt);
// void		ft_strjoin_part(char **dest, const char *src, int start, int len);
// void		ft_strjoin_free(char **dest, char *str);

// here_doc

void		heredoc_handler(int sig);
int			ft_process_line(t_data *data, char *line, int file);
void		ft_make_file(t_data *data, int file);

#endif