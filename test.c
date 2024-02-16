#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.a"
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
	char	*div_str;

	list = NULL;
	i = 0;

	new = ft_calloc(1, sizeof(t_test));
	new->pos = 0; // no es 0 pero un contador
	new->str = ft_strdup("Primero");

	if (list == NULL);
		list = new; list = 0x3

	new = ft_calloc(1, sizeof(t_test));
	new->pos = 1;
	new->str = ft_strdup("Segundo");

	list->next = new;
	new->prev = list;

	new = ft_calloc(1, sizeof(t_test));
	new->pos = 2;
	new->str = ft_strdup("Tercero");

	list->next->next = new;
	new->prev = list->next;

	// Loop to continuously read input until "exit" is entered
	while(1)
	{
/*A ver, lo que quiero hacer es que cada vez que se encuentre con | que pare y haya almacenado lo
 necesario en div_str. Esa variable guarta la string dividida por pos. Es decir cada ves que haya
 un comando distito lo guarda ahi para mandarlo a la estructura. El problema es que new debe tener
 el de despues y list el actual. A parte que hay que vaciar div_str para que no se haga un lio.
 Por no hablar que estoy haciendo tropocientas variables y es un poco cahotico. Espero que manana
 te ubiques.*/
		input = readline("Enter a command: ");
		while(input[i] != '|')
		{
			div_str[i] = input[i]
			i++;
		}
		new = ft_calloc(1, sizeof(t_test));
		new->pos = 0; // no es 0 pero un contador
		new->str = div_str[i];

		list->next = new;
		new->prev = list;

		new = ft_calloc(1, sizeof(t_test));
		new->pos = 1;
		new->str = div_str[i];

		list->next->next = new;
		new->prev = list->next;
		// Read a line of input using readline
		input = readline("Enter a command: ");
		// Check if input is NULL (usually happens on EOF or Ctrl+D)
		if (input == NULL)
		{
		    printf("\nExiting...\n");
		    break;
		}
		
		// Add the input to history
		add_history(input);
		
		// Check if the user wants to exit
		if (strcmp(input, "exit") == 0)
		{
		    printf("Exiting...\n");
		    free(input); // Free the memory allocated by readline
		    break;
		}
		
		// Process the input (here, just echo it back)
		printf("You entered: %s\n", input);
		
		// Free the memory allocated by readline
		free(input);
	}
	return 0;

}

