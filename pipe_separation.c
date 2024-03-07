#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
/*hay que intentar simplemnte coger la estring y printearla por las palabritas separadas por pipes.
Si se puede hacer eso, solo quedara hacer una fucion como la ft_lstadd_back_bonus.c del libft
para separar las cosas. O algo rollo esto:

Idea de lo que hay que hacer: Se complica la cosa cn el prev y el next de la lista. Lo que he
pensado es pasar todo lo que hay de listas incluida la estructura a otro archivo. Ahi tendre
que (con el pos) ordenar, si hay solo 1pos no habra ni next ni prev si hay mas si. Ademas que
el pos lo puedes sacar de la estructura y simplemente hazerlo variable normal.

// Print the contents of the list
    printf("Contents of the list:\n");
    t_test *temp = list;
    while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->next;
    }
para meter las cosas en la lista*/
typedef struct s_test
{
    int pos;
    char *str;
    struct s_test *prev;
    struct s_test *next;
} t_test;

void	*put_list(char *div_str)//a ver
{
    t_test	*list;
	t_test	*new;
	t_test	pos;

	list = NULL;
	pos = .
	if(div_str!)
		break;
	while(pos !< 1)
	{
		list->str = div_str
	}
/*    while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->next;
    }*/
}
void	pos_num(char *input)//to know how many positions will be
{
	int i;
	t_test pos;
	
	pos = 1;
	i = 0;
	while(input[i]!)
	{
		if(input[i] == '|')
			pos++;
		i++;
	}
}
int main()
{
	char	*input;
	int		i;
	int 	j;
	int		count_for_malloc;
	char	*div_str;

	i = 0;
	div_str = NULL;
	count_for_malloc = 0;
	while(1)
	{
		input = readline("Enter a command: ");
		if (input == NULL)
		{
			printf("\nExiting...\n");
			break;
		}
		else if(ft_strcmp(input, "\0") == 0)//in case you enter nothing it has to show you the promp again
		{
			free(input);
			continue;
		}
		if (ft_strcmp(input, "exit") == 0)//check if user wnts to exit
		{
			printf("Exiting...\n");
			free(input);// Free the memory allocated by readline
			break;
		}
		add_history(input);
		//while para coger cada palabra despues del pipe
		i = 0;
		pos_num(input);
		while (input[i])
		{
			count_for_malloc = i;
			while(input[count_for_malloc] != '|' && input[count_for_malloc] != '\0')//to reservate memory with malloc
				count_for_malloc++;
			printf("%d\t%d\n", i, count_for_malloc);
			div_str = malloc((count_for_malloc - i + 1) * (sizeof(char)));
			j = 0;
			while(input[i] != '|' && input[i] != '\0')//to safe every comand on strinig (not necessery to controlle space
			{
				printf("buscando pipe\n");
				div_str[j] = input[i];
				i++;
				j++;
			}
			printf("%s\n", div_str);
// NO		put_list(div_strs);// here we should send the string to the function that will allocateit in the list
			free(div_str);
			if(input[i] != '\0')
				i++;
		}
		free(input);
	}
	return 0;
}
