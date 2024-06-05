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

void	free_one_cmd(t_cmd *tmp)
{
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->args)
		free_double_void(tmp->args);
	if (tmp->err_f)
		free(tmp->err_f);
	if (tmp->in_fd != 0)
		close(tmp->in_fd);
	if (tmp->out_fd != 1)
		close(tmp->out_fd);
}

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
		if (err == SYNTAX)
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
			free_commands(&tk->cmds, 0);
		tk->num_cmds = 0;
	}
	free(line);
}

int	loop_main(t_min *tk)
{
	int		i;
	char	*line;

	line = readline("\033[38;5;200mminitxell \033[0;0m");
	// line = readline("minitxell ");
	if (!line)
	{
		if (isatty(STDIN_FILENO))
		{
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
		{
			printf("Here\n");
			exit_error(g_error_array[MALLOC], MALLOC);
		}
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
