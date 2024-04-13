/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:51:04 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/13 21:11:15 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	deleting(t_test *list)
{
	t_word *tmp;
	int i;

	i = 0;
	while(list != NULL)
	{
		tmp = list->word;
		while(tmp != NULL)
		{
			while(tmp->str[i])
			{
				if(tmp->str[i] == '\"' || tmp->str[i] == '\'')
					// todo esto del comentario va aqui
				i++;
			}
		}
	}
}
//string statica en plan char hola[20000]
//coges la word la copias en a variable sin las comillas
//hacer malloc de la string nueva de la varuiable, 
//free de la tmp->str osea la word
//haces un strdup de la string nueva 
/*free tmp->str   tmp->str = ft_strdup(hola) */
