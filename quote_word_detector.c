#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
void	print_word_double_quotes(char *div_str, char *word, int *i)
{
	int j;
	int quote;

	printf("double quotes\n");
	j = 0;
	quote = 2;
	while(div_str[*i])
	{
		if(div_str[*i] == '\"')
			quote--;
		if(quote == 0)
		{
			end_word(div_str, word, i, &j);
			break;
		}
		word[j] = div_str[*i];
		printf("(double) word leter added : %c\n", word[j]);
		(*i)++;
		j++;
	}
}

void	print_word_simple_quotes(char *div_str, char *word, int *i)
{
	int j;
	int quote;

	printf("simple quotes\n");
	j = 0;
	quote = 2;
	while(div_str[*i])
	{
		if(div_str[*i] == '\'')
			quote--;
		if(quote == 0)
		{
			end_word(div_str, word, i, &j);
			break;
		}
		word[j] = div_str[*i];
		printf("(simple) word leter added : %c\n", word[j]);
		(*i)++;
		j++;
	}
}

void	check_quotes(char *div_str, char *word, int *i)
{
	int 	count;

	count = *i;
	while(div_str[count])
	{
		if(div_str[count] == '\'')
		{
			print_word_simple_quotes(div_str, word, i);
			break;
		}
		else if(div_str[count] == '\"')
		{
			print_word_double_quotes(div_str, word, i);
			break;
		}
		count++;
	}
	print_word(div_str, word, i);
}
