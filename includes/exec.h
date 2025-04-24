/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:18 by tlay              #+#    #+#             */
/*   Updated: 2025/04/24 16:18:02 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec

void	exit_shell(t_data *data, int i, int j);
void	callexecve(t_data *data);
void	setup_and_execute_command(t_data *data);
void	make_one_command(t_data *data);
void	exec(t_data *data);

// utils_exec_3

void	wait_parent(t_data *data);
void	do_execve(t_data *data, char **tab);
void	no_command(t_data *data);
void	print_exit_shell(t_data *data, int i);
void	print_exit_shell_dir(t_data *data, int i);
void	handle_sigquit_command(int sig);

// pipe

void	child(t_data *data, int i);
void	setup_fds(t_data *data);
void	execute_last_command(t_data *data);
void	execute_command_with_pipe(t_data *data, int i);
void	make_command_pipe(t_data *data);

// utils_exec_2

void	ft_exit_sig(char *line, t_data *data, int i);
char	*ft_while_gnl(char *temp, char *line, char *buffer);
int		init_pid(t_data *data);
void	double_prompt_handler(int sig);
void	execute_command(t_data *data, int i);

// utils_exec

int		ft_size_tab(char **tab);
void	ft_free_tab(char **tab);
void	delete_envt(t_envt **data);
int		ft_size_tab_int(int *tab);
void	delete_export(t_export **export);

#endif