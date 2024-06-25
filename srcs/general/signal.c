/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:50:06 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/25 12:15:26 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "signalm.h"
#include <signal.h>

static void	norm_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 1;
	}
	return ;
}

static void	interact_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit = 131;
	}
	return ;
}

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_exit = 130;
		exit(130);
	}
	return ;
}

void	set_signals(int mode)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 0)
		sa.sa_handler = &norm_handler;
	else if (mode == 1)
		sa.sa_handler = &interact_handler;
	else if (mode == 2)
		sa.sa_handler = &heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
	if (!mode || mode == 2)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
		sigaction(SIGQUIT, &sa, NULL);
}
