/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/02 18:29:42 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signalm.h"
#include "g_error.h"

unsigned char	g_exit = 0;

t_min	*init_struct(char *env[])
{
	t_min	*tk;

	tk = ft_calloc(1, sizeof(t_min));
	if (!tk)
		return (NULL);
	if (take_env(tk, env))
	{
		free(tk);
		return (NULL);
	}
	return (tk);
}

void	program(t_min *tk, char *line)
{
	int	err;

	add_history(line);
	err = parser(tk, line);
	if (err != NONE)
	{
		if (err)
		{
			end_program(&line, err);
			return ;
		}
		err = execute_commands(tk);
		if (err == MALLOC)
			exit_error(g_error_array[err - 1], err);
		else if (err)
		{
			end_program(&line, err);
			return ;
		}
		if (tk->cmds)
			free_commands(&tk->cmds);
		tk->num_cmds = 0;
	}
	free(line);
}

// line = readline("minitxell ");
int	loop_main(t_min *tk)
{
	int		i;
	char	*line;

	line = readline("\033[38;5;200mminitxell \033[0;0m");
	if (!line)
	{
		if (isatty(STDIN_FILENO))
		{
			free_all(tk, 0);
			i = write(2, "exit\n", 6);
			if (i == 0)
				exit(1);
		}
		return (1);
	}
	else if (line && line[0] == '\0')
	{
		free(line);
		return (0);
	}
	program(tk, line);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	int		result;
	t_min	*tk;

	(void)argv;
	if (argc == 1)
	{
		tk = init_struct(env);
		if (!tk)
			exit_error(g_error_array[0], MALLOC);
		init_pwd(tk);
		set_term();
		while (42)
		{
			set_signals(0);
			result = loop_main(tk);
			if (result == 1)
				exit(0);
		}
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
