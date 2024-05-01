/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:09:52 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/25 19:35:52 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

char *ft_strcopy(char *str)
{
	char copy[2000];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(copy[i])
	{
		str[j] = copy[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return(str);
}
int	check_file(char *word, char sign)
{
	int		i;
	char	cwd[1024]; //path maximo lo que tambien pondremos en el size_t
	char	*path;// el path tiene hasta la carpeta pero no el archivo, hay
		      //  que anadir al path la barrita / y luego el nombre del archivo.     🚨LEE ESTO🚨
		      // pero solo si al inicio hay la barra NO HACER EL PATH  no habra trolleos LO HA DICHO VALERIO Y ESTA MIRANDO ESTO AHORA MISMO
	if (word[0] != '/')
	{
		path = getcwd(cwd, 1024);
	}
	else
		path = word;
	if(sign == '>')
		i = access(path, W_OK); // hay que comprobar que exita igualmente en caso de que no se pueda ni leer ni escribir, si falla comprueba 🚨
	if(sign == '<')
		i = access(path, R_OK);
	return(i);
}
//no lo he probado pero no va. Preguntale a valerio que significa los heredoc
void	open(t_test *list)
{
	t_test tmp_word;
	char str[2000];
	int i;
	char	sign;
	
	i = 0;
	tmp_word = list->words;
	while(tmp_word)
	{
		if(tmp_word->str[i] == '>' ||  tmp_word->str[i] == '<')
		{
			sign = tmp_word->str[0];
			//if(tmp_word->str[1] == '>')
			//	i++;
			str = ft_strcopy(tmp_word->next->str)
			if(check_files(str, sign) == 0) // en caso de que no sea cero tiene que retornar para saber cuales NO se pueden abrir 🚨
							// de hecho con que no se abra uno todo el resto de detras ya nada, ni se miran 🚨
				//funcion de abrir
		}
		tmp_word->next;
	}
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
 *
 *  3. Si la redireccion > significa output hay que escribir
 *   					 < 					hay que leer
 *   					 >>					hay que escribir
 * 4. El tema de los heredocs:
 *    La cosa esta en que los heredocs se dancuando hay doble simbolo. Ahora
 *    mismo el codigo solo funciona con un solo simbolo. Hay varias cosas que
 *    se me ocurren hacer. 1 es hacer una string la cual pueda almacenar 
 *    los dos simbolos o simplemente hacer un prev en la funcion check_file 
 *    para comprovar que simbolo es y si hay mas de uno.
 *    2.hacer otra fucion nueva solo para el casi de que la palabra tenga un segundo caracter.
 *
 *    Realmente no creo que haya dos simbolos mal puestos pero puede que haya que comprobarlo
