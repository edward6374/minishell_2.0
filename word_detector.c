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

void	end_word(char *div_str, char *word, int *i, int *j)
{
	word[*j] = div_str[*i];
	printf("(end word) last letter added: %c\n", word[*j]);
	(*j)++;
	word[*j] = '\0';
	printf("-%s-\n", word);
	ft_bzero(word, *j);
	*j = 0;
	(*i)++;
	if(div_str[*i] != '\0')
		check_quotes(div_str, word, i);

}

void	print_word(char *div_str, char *word, int *i)
{
	int j;
	int quote;

	j = 0;
	quote = 0;
	while(div_str[*i])
	{
		if(div_str[*i] == '\'' || div_str[*i] == '\"' )
			quote++;
		if(div_str[*i] == ' ' && quote == 0)
			(*i)++;
		if((div_str[*i] != ' ' && (div_str[*i+1] == ' ' || div_str[*i+1] == '\0' || div_str[*i+1] == '<' || div_str[*i+1] == '>'))&& quote % 2 == 0)
			end_word(div_str, word, i, &j);
		else
		{
			word[j] = div_str[*i];
			printf("(print word) word leter added: %c\n", word[j]);
			j++;
			(*i)++;
		}
	}
}

void	dividing_words(char *div_str)
{
	int i;
	char word[200];

	i = 0;
	while(div_str[i])
	{
		if(div_str[i] == '\"' || div_str[i] == '\'' || div_str[i] == '<' || div_str[i] == '>')
		{
			i = 0;
			check_quotes(div_str, word, &i);
		}
		else if(div_str[i] == ' ')
			i++;
		else
			print_word(div_str, word, &i);
	}
}

//como lo voy a hacer con pasos
//1. coger las palabras separadas por espacios y <> ✅
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
