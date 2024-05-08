/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:39 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/07 15:12:13 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
#include "struct.h" //quizas esto no ero es donde esta la structura que voy a usar asi que...

void	put_command_list(t_cmd *list_cmd, t_test *list)
{
	t_cmd *tmp;
	t_cmd *new;
	t_test tmp_word;

	new = ft_calloc(1, sizeof(t_cmd));
	new->ok = do_open(list, new);




	if(!(*list))
		*list = new;
	else
	{
		tmp = *list;
		tmp->out_fd == 1;
		tmp_word = list->word;

		while (tmp->next != NULL)
		{
			do_open(tmp_word);
			tmp = tmp->next;
		}
		tmp->next = new;
		new->before = tmp;
	}
}
