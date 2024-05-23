/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:39 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/23 20:39:41 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"

static void print_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmds;
	printf("\n");
	while (tmp)
	{
		printf("Command number: %i\n", tmp->n);
		printf("Ok: %i\n", tmp->ok);
		printf("In fd: %i\n", tmp->in_fd);
		printf("Out fd: %i\n", tmp->out_fd);
		printf("Command: %s\n", tmp->cmd);
		printf("Error file: %s\n", tmp->err_f);
		i = -1;
		if (tmp->args)
		{
			while (tmp->args[++i])
				printf("Arg %i: %s\n", i, tmp->args[i]);
		}
		printf("Heredoc or not? %i\n", tmp->hdoc->yes);
		printf("First heredoc? %i\n", tmp->hdoc->first);
		printf("Stop word: %s\n\n", tmp->hdoc->stop);
		tmp = tmp->next;
	}
}

int	parser(t_min *tk, char *line)//pasado main
{
	t_test	*list;

	// poner las funciones para controlar las comillas
	// y las redirecciones, y si falla algo, retornar 2
	list = dividing_pipe(line, 0);
	check_dollar(tk, list);
	deleting(list);
	tk->cmds = get_command_list(tk, list);
	print_cmds(tk->cmds);
	return (0);
}

// Cosas que estan mal:
// las comillas tienen que ser numero par, SIEMPRE!!!❗️❗️❗️❗️❗️❗️❗️
// Las dos comillas, entonces si hay simple y doble,
// hay que contar las dos! ✍️
//
// Las redirecciones: estan mal si despues de un < o > o << o >> no hay una palabra
// pero hay otra redireccion o un pipe, y controlar
// tambien que si antes de un pipe tienes otro pipe o no tienes palabras, esta mal
