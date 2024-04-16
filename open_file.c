/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:09:52 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/16 18:59:53 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

//esto seguramente no funcione nada
void	check_file(t_test *list)
{
	t_test tmp;
	int	 i;

	tmp = list->word;
	while(tmp != NULL)
	{
		if((i = open(tmp, O_RDONLY)) = -1)
			tmp = tmp->next;
		if((i = open(tmp, O_RDONLY)) = 0)
		{
			return(
		}
	}
}

void	open()
{

}

/*Buena, voy a explicar lo que hay que hacer aqui.
 * ❶ Solamente se deve abrir si la palabra va detras de un > >> <
 * ❷ En vez de open mejor usar acces, tienes que leer como se usa
 * ❸ La check_files nada de recorrer la lista, simplemente se pasa
 *   lo que hay despues de > >> <
 * ❹ En la segunda fucion hay que recorrer la funcion para encontrar
 *    > >> < y luego mandarla para saber si es un file o un directori.
 * ❺ La primera funcion tiene que devolver un numero y luego en el
 *   open ya se abre. Si se devuelve 0 se abre y ya.
 * */
