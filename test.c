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
	//printf("antes de entrar en el while\n");
	// Loop to continuously read input until "exit" is entered
	while(1)
	{
		input = readline("Enter a command: ");
	//	printf("pre if null\n");
		if (input == NULL)
		{
			printf("if de null\n");
		    printf("\nExiting...\n");
		    break;
		}
	//	printf("post if\n");
		j = 0;
	//	printf("post j\n");
		while(input[count_for_malloc] != '|' && input[count_for_malloc] != '\0')
		{
			printf("en el while\n");
			count_for_malloc++;
		}
	//	printf("cout_for_malloc: %d\n", count_for_malloc);
		div_str = malloc((count_for_malloc + 1) * (sizeof(char)));
		while(input[i] != '|'&& input[i] != '\0')//to safe every comand on string
		{
			printf("bucando pipe\n");
			div_str[j] = input[i];
			i++;
		}
		new = ft_calloc(1, sizeof(t_test));
		new->pos = 0; // no es 0 pero un contador
		new->str = div_str;
		//printf("metido en new\n");
		list = new;
		printf("metido en list\n");
		new->prev = NULL;
		printf("new->prev ahora es list\n");
		new = ft_calloc(1, sizeof(t_test));
		new->pos++; //no se si es asi o +1
		printf("pos++ que me he inventado\n");
		if(new->pos > list->pos)
		{
			printf("entro en el if para liberar la div_str y meter la nueva en newmientras list tiene la vieja\n");
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

		list->next = new;
		new->prev = list;
		printf("se ha anadido lo nuevo\n");
		// Add the input to history
		add_history(input);
/*Hay un problema con el exit que no te lo coje, ademas que quizas hay que quitar los espacios de las palabras*/
		// Check if the user wants to exit
		if (strcmp(list->str, "exit") == 0)
		{
			printf("if del exit\n");
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

