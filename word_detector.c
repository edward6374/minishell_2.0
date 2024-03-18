/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:10 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/16 17:44:29 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
/* si pongo: "hola" adios, no va correctarmente*/
int	check_quotes(char *div_str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("entro en check_quotes\n");
	while(div_str[i])
	{
		if(div_str[i] == '\"' || div_str[i] == '\'')
			j++;
		i++;
	}
	printf("quotes: %d\n", j);
	return(j);
}

void	end_word(char *div_str, char *word, int *i, int *j)
{
	word[*j] = div_str[*i];
	printf("last letter added: %c\n", word[*j]);
	(*j)++;
	word[*j] = '\0';
	printf("%s\n", word);
	ft_bzero(word, *j);
	*j = 0;
	(*i)++;
}

void	print_word(char *div_str, char *word, int *i, int j)
{
	while(div_str[*i])
	{
		if(div_str[*i] == ' ')
			(*i)++;
		if(div_str[*i] != ' ' && (div_str[*i+1] == ' ' || div_str[*i+1] == '\0'))
			end_word(div_str, word, i, &j);
		else
		{
			word[j] = div_str[*i];
			printf("word leter added: %c\n", word[j]);
			j++;
			(*i)++;
		}
	}
}

void	print_word_between_quotes(char *div_str, char *word, int *i, int j)
{
	int quote;
	
	printf("entro es print between\n");
	quote = check_quotes(div_str);
	while(div_str[*i])
	{
		if(div_str[*i] == '\"' || div_str[*i] == '\'')
		{
			
			quote--;
			(*i)++;
		}
		word[j] = div_str[*i];
		printf("word leter added : %c\n", word[j]);
		if((div_str[*i] == ' ' && quote == 0) || quote == 0)
			end_word(div_str, word, i, &j);
		(*i)++;
		j++;
	}
	//word[j] = '\0';
	//printf("%s\n", word);
}

void	dividing_words(char *div_str)
{
	int i;
	int j;
	char word[200];

	i = 0;
	j = 0;
	while(div_str[i])
	{
		if(div_str[i] == '\"' || div_str[i] == '\'')//cuando encuentre comillas
			print_word_between_quotes(div_str, word, &i, j);
		else if(div_str[i] == ' ')
			i++;
		else
			print_word(div_str, word, &i, j);
	}
//	if(div_str[i] == '\0')
//		printf("word: %s\n", word);
	
}

//como lo voy a hacer con pasos
//1. coger las palabras separadas por espacios
//	1.1 espacio al inicio y al final se quitan
//		_hola_ --> hola
//	1.2 si hay muchos espacios al inicio y al final da igual, lo de dentro es una palabra
//		 _____hola___adios______ --> hola adios (dos palabras)
//	1.3 si los espacios estan entre comillas se cuentan como palabra
//		(recordemos que las comillas se quitan, pero eso mas adelante)
//		_"___hola__adios_"___ --> ___hola__adios_
//	1.4 en el pipe_separation no habra cosas raras como comillas sinn cerrar o errores
//		estranos porque voy a hacer un corrector de errores, asi que nah.
//	1.5 los espacios definen las palabras
//		"hola_que_tal"_"bien_y_tu"_"pues_mal" --> hola_que_tal bien_y_tu pues_mal (3)
//2. borrar comillas
//3. meter las palabras en la lista
//4. hacer el prev y el next y todo


//He creado una estructura que se puede usar como nueva lista. Puede parece
//incomodo al principio pero para luego pasarlo a los comandosa sera mas
//facil. Lo que hay que hacer ahora es:
//1. Que es una palabra? --> caracteres que estan determinados por espacios
//si los espacios estan antes que las comillas, lo de dentroo de las comillas
//es una palabra.
//		1.
//		ejemplo: _hola""que'ta  l'_abc
//		todo esto seria una palabra
//		abc es otra palabra
//		2.
//		ejemplo: hola""que'ta  l'abc
//		esto es todo una palabra
//
//2. Se de ben quitar las comillas.
//		ejemplo: "hola que tal"
//		         "kkk''lk"
//		resultado: hola que tal
//		           kkklk
//
