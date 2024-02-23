#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
/*hay que intentar simplemnte coger la estring y printearla por las palabritas separadas por pipes.
Si se puede hacer eso, solo quedara hacer una fucion como la ft_lstadd_back_bonus.c del libft
para separar las cosas. O algo rollo esto:

// Print the contents of the list
    printf("Contents of the list:\n");
    t_test *temp = list;
    while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->next;
    }
para meter las cosas en la lista*/

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
			free(div_str);
			if(input[i] != '\0')
				i++;
		}
		free(input);
	}
	return 0;
}
