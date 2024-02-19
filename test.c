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

	list = NULL;
	i = 0;
	div_str = NULL;
	count_for_malloc = 0;
	// Loop to continuously read input until "exit" is entered
	while(1)
	{
		input = readline("Enter a command: ");
		printf("primer while\n");
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
		{
			//printf("en el while\n");
			count_for_malloc++;
		}
		div_str = malloc((count_for_malloc + 1) * (sizeof(char)));
		while(input[i] != '|'&& input[i] != '\0')//to safe every comand on string
		{
			printf("bucando pipe\n");
			div_str[j] = input[i];
			i++;
			j++;
		}
/*el problema es con el pos++ porque no va hacia delante, revisa */
		//printf("cuanto es pos: %d\n", new->pos);
//		if(new->pos == 0)
//		{
//			printf("en caso de que pos sea 0\n");
			new = ft_calloc(1, sizeof(t_test));
			new->pos = 0; // no es 0 pero un contador pero hay que hacer ++ o buscar alguna manera.
			new->str = div_str;
//			printf("metido en new: %s\n", div_str);
			list = new;
			new->prev = NULL;
			new = ft_calloc(1, sizeof(t_test));
			//new->pos++;
//		}
		printf("cuanto es pos: %d\n", new->pos);
		if(new->pos > 0 )
		{
			printf("en caso que pos sea mayor que 0\n");
			new = ft_calloc(1, sizeof(t_test));
			new->next->str = div_str;
			printf("segundo metido en new: %s\n", div_str);
			list->next = new;
			new->prev = list;
			new = ft_calloc(1, sizeof(t_test));
		}
		new->pos++; //no se si es asi o +1
/*solo funciona si el exit esta solo sin nigun espacio y sim pipe al final, revisar esto*/
		if (ft_strcmp(div_str, "exit") == 0)//check if user wnts to exit
		{
			printf("if del exit\n");
			printf("Exiting...\n");
			free(input);// Free the memory allocated by readline
			break;
		}
		if((input[i] == '|' || input[i] == '\0') && new->pos > 0)
		{
			i++;
			continue;
		}
		/*
		if(input[i] == '|')
		{
			printf("div era: %s\n", div_str);
			printf("IF DEL DIV\n");
			j = 0;
			free(div_str);
			i++;
			while(input[i] != '|' && input[i] != '\0')
			{
				div_str[j] = input[i];
				i++;
				j++;
			}
			new->str = div_str;
			printf("div ahora es: %s\n", div_str);
		}

		list->next = new;
		new->prev = list; */
		printf("nuevo div anadido\n");
		// Add the input to history
		add_history(input);
		
		// Process the input (here, just echo it back)
		printf("You entered: %s\n", input);
		
		// Free the memory allocated by readline
		free(div_str);
		free(input);
	}
	return 0;
}

