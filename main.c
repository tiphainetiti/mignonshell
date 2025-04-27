/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:29 by tlay              #+#    #+#             */
/*   Updated: 2025/04/27 15:54:38 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_sig;

void	init_minishell(t_data *data, char **env)
{
	if (init_data(data) == 1)
		exit_shell(data, 0, 1);
	if (get_env(&(data->envt), env) == -1)
		exit_shell(data, 0, 1);
	if (get_export(&(data->export), &(data->envt)) == -1)
		exit_shell(data, 0, 1);
}

void	do_minishell(t_data *data, char *input)
{
	t_token	*token;

	token = tokenize(input, data);
	// print_tokens(token);
	if (!token)
		return (free(input));
	add_history(input);
	if (!check_syntax(token, data))
		return (free_tokens(token), free(input));
	token = expand_tokens(token, data);
	if (!build_commands(data, token))
		return (free_tokens(token), free(input));
	// print_commands(data->cmd);
	exec(data);
	if (data->pid)
		free(data->pid);
	if (data->path != NULL)
		free(data->path);
	free(input);
	data->nb_cmd = 0;
	return ;
}

void	error_input(t_data data)
{
	printf("exit\n");
	if (data.envt)
		delete_envt(&(data.envt));
	if (data.export)
		delete_export(&(data.export));
	rl_clear_history();
	exit(0);
}

void	shell_loop(t_data data)
{
	char	*input;

	while (1)
	{
		g_sig = 0;
		handle_signal(0);
		data.infile = STDIN_FILENO;
		data.outfile = STDOUT_FILENO;
		input = readline("minishell^^ $ ");
		if (g_sig == 1)
			data.exit_code = 130;
		if (!input)
			error_input(data);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		else
			do_minishell(&data, input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (argc == 1)
	{
		init_minishell(&data, env);
		shell_loop(data);
		rl_clear_history();
		free_envt(data.envt);
		exit(data.exit_code);
	}
	else
	{
		printf("Wrong number of arguments.\n");
		return (0);
	}
}
