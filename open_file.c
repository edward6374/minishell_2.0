/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:09:52 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/14 19:52:30 by mehernan         ###   ########.fr       */
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
	int i;

	i = 0;
	if(access(path, F_OK) == 0)//para comprobar que existe ✅
	{
		if(sign == '>')
		{
			if((i = access(path, W_OK)) == 0)
				list_cmd->out_fd = open(path, O_WRONLY | O_TRUNC | O_CREA, 0644);
			else
				return(1);
		}
		if(sign == '<')
		{
			if((i = access(path, R_OK)) == 0)
				list_cmd->in_fd = open(path, O_RDONLY);
			else
				return(1); // si falla no retorno nada porque quiero que en la lista se quede vacio
		}
		return(0);// en vez de uno quizas hay que retornar otra cosa, pero la cuestion es que no se retonre el fd del open
	}
	return(1);
}

int do_open(t_test *node, t_cmd *cmd)
{
	int		i;
	char	*path;
	char	sign;
	t_word	*tmp_word;
	
	i = 0;
	tmp_word = node->words;
	while(tmp_word)
	{
		if(tmp_word->str[i] == '>' ||  tmp_word->str[i] == '<')
		{
			sign = tmp_word->str[0];
			path = get_path(tmp_word->next->str);
			//str = ft_strcopy(tmp_word->next->str);
			if(check_files(path, sign) != 0)// si es 0 no se cumplira el if pero ya habra entrado😉
			{
				cmd->err_f = ft_strdup(tmp_word->next->str);
				return(1); // hay que revisar que retornar, pongo 1 ya que lo que retorna es el contador del ok de la lista
			}
//			take_fd(path, sign, new);    no se que es esto, estoy lost
		}
//		cmd->n = cmd->n + 1;
//		cmd = cmd->next;
		tmp_word = tmp_word->next;
	}
	return (0);
}
// recuerda que si en cuelquier momento haces retur porque algo falla 
