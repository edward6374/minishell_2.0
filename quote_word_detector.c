#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

int	check_quotes(char *div_str, char *word, int i)
{
	int 	count;

	count = 0;
	while(div_str[count])
	{
		if(div_str[count] == "\'")
		{
			print_word_simple_quotes(div_str, word, &i)
			break;
		}
		else if(div_str[count] == "\"")
		{
			print_word_double_quotes(div_str, word, &i);
			break;
		}
		count++;
	}

}
/*
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("entro en check_quotes\n");
	while(div_str[i])
	{
		if(div_str[i] == '\"' || div_str[i] == '\'')
		{
			j++;
			if(
		}
		i++;
	}
	printf("quotes: %d\n", j);
	return(j);
}*/
