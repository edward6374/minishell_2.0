#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"

typedef struct s_test
{
    int pos;
    char *str;
    struct s_test *prev;
    struct s_test *next;
} t_test;

int main()
{
	char	*input;
	t_test	*list;
	t_test	*new;
	int		i;
	int 	j;
	int		count_for_malloc;
	char	*div_str;
	int 	controll_readline;

	list = NULL;
	i = 0;
	div_str = NULL;
	count_for_malloc = 0;
	controll_readline = 0;
	// Loop to continuously read input until "exit" is entered
	while(1)
	{
/*el problema es que cuando se hace contineu pierde el resto del input porque hace readline, hay buscar
una manera de que no haga readline si input tiene algo mas despues de un. Lo que ha ahora NO VA. Hace
loop infinito|*/
		if(controll_readline != 1)
		{
			input = readline("Enter a command: ");
			controll_readline = 1;
		}
		if(ft_strcmp(input, "\0") == 0)//in case you enter nothing it has to show you the promp again
		{
			free(input);
			continue;
		}
		if (input == NULL)
		{
			 printf("\nExiting...\n");
			break;
		}
		j = 0;
		while(input[count_for_malloc] != '|' && input[count_for_malloc] != '\0')//to reservate memory with malloc
			count_for_malloc++;
		div_str = malloc((count_for_malloc + 1) * (sizeof(char)));
		while(input[i] != '|'&& input[i] != '\0')//to safe every comand on strinig (not necessery to controlle space
		{
			printf("bucando pipe\n");
			div_str[j] = input[i];
			i++;
			j++;
		}
		if(list == NULL)
		{
			new = ft_calloc(1, sizeof(t_test));
			new->pos = 0; // no es 0 pero un contador pero hay que hacer ++ o buscar alguna manera.
			new->str = div_str;
			printf("metido en new: %s\n", div_str);
			list = new;
			new->prev = NULL;
			new = ft_calloc(1, sizeof(t_test));
		}
		printf("cuanto es pos: %d\n", new->pos);
		if(list != NULL)
		{
			new = ft_calloc(1, sizeof(t_test));
			new->str = div_str;
			printf("segundo metido en new: %s\n", div_str);
			list->next = new;
			new->prev = list;
			new = ft_calloc(1, sizeof(t_test));
		}
		new->pos++; //no se si es asi o +1
		free(div_str);
		printf("cuanto es pos2: %d\n", new->pos);
		if (ft_strcmp(div_str, "exit") == 0)//check if user wnts to exit
		{
			printf("if del exit\n");
			printf("Exiting...\n");
			free(input);// Free the memory allocated by readline
			break;
		}
		if(input[i] == '|')
		{
			printf("IF DEL DIV\n");
			i++;
			continue;
			printf("div ahora es: %s\n", div_str);
		}
		else if(input[0] == '\0')
		{
			add_history(input);
			free(div);
			free(input);
			break;
		}
	}
	return 0;
}
