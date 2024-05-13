/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:39 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/13 20:16:27 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
#include "struct.h" //quizas esto no ero es donde esta la structura que voy a usar asi que...

void	put_command_list(t_cmd **list_cmd, t_test *node)
{
	t_word *tmp_words;
	t_cmd *new;
	char *path;
	int i;
//Quizas hay que hacer otro while al principio para que vueva entrar y luego coger mas comandos o quizas no, hay que pensar🧠
	tmp_words = node->words;
	new = ft_calloc(1, sizeof(t_cmd));
	new->ok = do_open(node, new);
	if(new->ok == 0)
	{
		i = 0;
		while(tmp->words != NULL)
		{//solo hay que comprobar la palabra que esta despues de las redurecciones.
			while(tmp->words->str[i])
			{
				if(tmp_words->str[i-1] == '<' || tmp_words->str[i-1] == '>')
				{
					path = get_path(tmp_words->str[i])
					if(access(path, X_OK) != 0)
					{
						new->cmd = tmp_words->str;//quizas no puedo igular dos str por la cara❌
					//	new->ok = 2 sera un numero de algo
					}
					else
					{
						new->cmd = path;
						break;
					}
				}
				i++;
			}
			new->n = new-> + 1;
			tmp->words = tmp_words->next
		}
	}
}


void	get_command_list(t_cmd *list_cmd, t_test *list)
{
	t_test	*tmp;
	t_cmd	*list_cmd;

	*list_cmd = NULL;
	tmp = list;
	while (tmp != NULL)
	{
		put_command_list(&list_cmd, tmp);
		tmp = tmp->next;
	}
}

