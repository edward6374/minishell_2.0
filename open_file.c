/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:09:52 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/24 19:27:03 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

//esto seguramente no funcione nada
int	check_file(char word)
{
	/*todo esto se puede borrar, lo que tienes que hacer es una funcion que con el acces, poniendo en el primer parametro el resutado de la funcion getcwd y en el segundo un char * que sea el path maximo (mmirar apuntes),  todo eso pasarlo a la funcion y segun lo que devuelva retornar el numero para hacer el open. en plan si es 1 es error y si es bien 0.
	t_test tmp;
	int	 i;
// declarar el path para despues usar el getwd;
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
}*/

void	open(t_test *list)
{
	t_test tmp_word;
	char str[200];
	int i;
	int j;

	tmp_word = list->word;
	i = 0;
	j = 0;
	while(tmp_word[i])
	{
		if(tmp_word[i] == '>' || tmp_word[i] '<')
		{
			i++;
			if(tmp_word[i] == '>' && tmp_word[i+1] == '>')
				i++;
		}
		str[j] = tmp_word[i];
	}
	str[j] = '\0';
	check_file(str);
	/* aqui queda la parte de hacer el open en caso de que el archivo se pueda abrir*/
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

/* 🧠pensado🧠
 * 1. No se si tmp deberia ser lits->word o mas bie list->str, ya que
 * deberia recorrer caracter por caratcter para saber si hay un > >> o <.
 * De momento coger las str ya que en las palabras no entra ese simbolito 
 * y jamas lo encotraria. Pero quizas si que puedo usar las palabras.
 * Tendria que saber cuantos caracteres tiene cada palabra y de ahi ir a
 *  la str y tirar para atras hasta encontrar un simbolo y de ahi saber 
 *  que esa es la palabra. La cosa esta en que si hay un espacio o otra
 *  cosa tendria que saltaro o cancelarllo.
 *
 *  2.Nueva info, no se puede pasar la palabra sin mas, para que el acces
 *  funcione le ienes que pasar el path, es decir donde esta, para saber
 *  eso hay una funcion que es la getcwd, de ahi haras una str dodne estara
 *  la palabra sin los simbolos y ver si se abre. Hay que revisar la funcio
 *  acces para saber como funciona lo de pasarle el path
