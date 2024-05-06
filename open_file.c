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
/*⚠️ela funcion open es llamada por el archivo que checkea los comandos⚠️
⚠️eeste archivo sera finalizado cuando se cree lo de los comandos⚠️*/
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

char	*get_path(char *word)
{
	char	*path;

	if (word[0] != '/')
	{
		path = getcwd(cwd, 1024);
		//i = ft_strlen(path); // arreglo de la barra y nombre del archivo✅
		path[ft_strlen(path)] = '/';
		path = ft_strjoin(path, word)
	}
	else
		path = ft_strdup(word);
	return (path);
}

int	check_file(char *path, char sign)
{
//	int		i;
//	char	cwd[1024]; //path maximo lo que tambien pondremos en el size_t
//	char	*path;
//
//	if (word[0] != '/')
//	{
//		path = getcwd(cwd, 1024);
//		i = ft_strlen(path); // arreglo de la barra y nombre del archivo✅
//		path[i] = '/';
//		path = ft_strjoin(path, word)
//		i = 0;
//	}
//	else
//		path = word;
	if(acces(path, F_OK) == 0)//para comprobar que existe ✅
	{
		if(sign == '>')
			i = access(path, W_OK); 
		if(sign == '<')
			i = access(path, R_OK);
		return(i);
	}
	return(1); // pongo 1 en representacion del -1 que puede dar error 
}

void	do_open(t_test *list)
{
	t_test tmp_word;
	//char str[2000];
	char	*path;
	int i;
	char	sign;
	
	i = 0;
	tmp_word = list->words;
	while(tmp_word)
	{
		if(tmp_word->str[i] == '>' ||  tmp_word->str[i] == '<')
		{
			sign = tmp_word->str[0];
			path = get_path(tmp_word->next->str);
			//str = ft_strcopy(tmp_word->next->str);
			if(check_files(path, sign) == 1)// si es 0 no se cumplira el if pero ya habra entrado😉
				return(1); // hay que revisar que retornar, pongo 1 en consideracion al -1 porque puede dar error
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
 *    Realmente no creo que haya dos simbolos mal puestos pero puede que haya que comprobarlo*/

/*🪐pensando🪐
 * Yo habia planificado todo que cuando devolviera del check_file si todo iba bien haria open
 * El problema es que se necesila el path y mas cosas que no se encuentran en la funcion de
 * do_open, por lo tanto o lo hago todo en la funcion de check_files (y de ahi llamo a otra
 * funcion o como sea) o me busco otra manera que no se me ocurre ahora. Porque retonrnar el path
 * no se puede ya que do_open tienque retornar si se puede abrir o no. Total, que mejor hacer
 * eso.
 
 
