/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:26:58 by tlay              #+#    #+#             */
/*   Updated: 2025/05/01 14:41:13 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structures.h"

// builtin

int			execute_builtin_command(t_data *data, char *cmd);
int			parsing_builtin(t_data *data);

// cd_utils

void		set_oldpwd(t_data *data, char **oldpwd, char *pwd);
void		set_newpwd(t_data *data, char **pwd, char *path);
void		set_pwds_env(t_data *data, t_envt *envt, char *path);
void		set_pwds_export(t_export *export, char *new_pwd);
void		error_cd(t_data *data, char *path);

// cd

void		change_directory_and_update_env(t_data *data, char *path);
char		*get_home_path(t_envt *env);
void		handle_cd_path(t_data *data, t_cmd *cmd, t_envt *env);
void		make_cd(t_data *data, t_cmd *cmd);
void		execute_cd(t_data *data);

// echo

void		write_echo_output(t_data *data, int start, int option);
int			find_option(char *cmd);
void		make_echo(t_data *data);
void		execute_echo(t_data *data);

// echo_utils

void		restore_spaces(char **cmd);

// env

int			find_command_path(char **path);
int			find_env_command_path(t_data *data);
void		make_env(t_data *data);
void		execute_env(t_data *data);

// exit

long long	ft_natoi(t_data *data, const char *nptr);
int			check_overflow(t_data *data, char *str);
int			handle_exit_code(t_data *data, int tmp);
void		make_exit(t_data *data, int tmp);
void		execute_exit(t_data *data, int tmp);

// export

int			validate_identifier(t_data *data, char *str);
void		process_export(t_data *data, t_export **export, char *str);
void		make_export(t_data *data, t_export **export);
void		execute_export(t_data *data);

// export_utils

void		add_node_sorted(t_export **head, char *key, char *value);
int			check_already_node(t_export **export, char *key, char *value);
int			update_existing_node(t_envt *current, char *key, char *str);
void		add_node_envt(t_data *data, t_envt **envt, char *key, char *value);
int			print_export(t_data *data, t_export **export);

// export_utils_2

int			check_already_export(t_envt *node, t_envt *current, char *key,
				char *str);
void		write_export(char *str);

// pwd

int			validate_pwd_args(t_data *data);
void		get_pwd(t_data *data);
void		execute_pwd(t_data *data);

// unset
void		unset_export(t_export **export, char *var);
void		unset_envt(t_envt **envt, char *var);
void		ft_unset(t_data *data, t_cmd *cmd);
void		execute_unset(t_data *data);

#endif