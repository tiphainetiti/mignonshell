/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:55 by tlay              #+#    #+#             */
/*   Updated: 2025/04/30 16:48:21 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = 1;
	disable_echoctl();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	exit(0);
}

void	handle_signal(int i)
{
	if (i == 0)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 1)
	{
		signal(SIGINT, &heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		signal(SIGINT, &double_prompt_handler);
		signal(SIGQUIT, &handle_sigquit_command);
	}
}
