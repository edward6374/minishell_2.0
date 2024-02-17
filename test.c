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
/*Sigue sin ir pero esta mas encaminado, lo del malloc esta solucionado pero habria que mirarlo bien con printf y cosas*/
		input = readline("Enter a command: ");
		if (input == NULL)
		{
		    printf("\nExiting...\n");
		    break;
		}
		j = 0;
		while(input[i] != '|')
			count_for_malloc++;
		div_str = malloc((count_for_malloc + 1) * (sizeof(char)));
		while(input[i] != '|')//to safe every comand on string
		{
			div_str[j] = input[i];
			i++;
		}
		new = ft_calloc(1, sizeof(t_test));
		new->pos = 0; // no es 0 pero un contador
		new->str = div_str;

		list->next = new;
		new->prev = list;

		new = ft_calloc(1, sizeof(t_test));
		new->pos = new->pos++; //no se si es asi o +1
		if(new->pos > list->pos)
		{
			j = 0;
			free(div_str);
			if(input[i] == '|')//solo servira si solo hay un | por cada
				i++;
			while(input[i] != '|')
			{
				div_str[j] = input[i];
				i++;
			}
			new->str = div_str;
		}

		list->next->next = new;
		new->prev = list->next;
		// Add the input to history
		add_history(input);
		
		// Check if the user wants to exit
		if (strcmp(list->str, "exit") == 0)
		{
		    printf("Exiting...\n");
		    free(input);// Free the memory allocated by readline
		    break;
		}
		
		// Process the input (here, just echo it back)
		printf("You entered: %s\n", input);
		
		// Free the memory allocated by readline
		free(input);
	}
	return 0;

}

