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

typedef struct s_test
{
    int pos;
    char *str;
    struct s_test *prev;
    struct s_test *next;
} t_test;
/*
int	count_pipe(char *input)
{
	int count;
	int pipe;

	count = 0;
	pipe = 0;
	while(input[count])
	{
		if(input[count] == '|')
			pipe++;
		count++;
	}
	return(pipe);
}*/
int main()
{
	char	*input;
	//t_test	*list;
	//t_test	*new;
	int		i;
	int 	j;
	int		count_for_malloc;
	char	*div_str;
//	int 	controll_readline;

//	list = NULL;
	i = 0;
	div_str = NULL;
	count_for_malloc = 0;
//	controll_readline = 0;
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
			printf("if del exit\n");
			printf("Exiting...\n");
			free(input);// Free the memory allocated by readline
			break;
		}
		add_history(input);
		while (input[i])
		{
			count_for_malloc = i;
			while(input[count_for_malloc] != '|' && input[count_for_malloc] != '\0')//to reservate memory with malloc
				count_for_malloc++;
			//free(div_str);
			div_str = malloc((count_for_malloc - i + 1) * (sizeof(char)));
			j = 0;
			while(input[i] != '|' && input[i] != '\0')//to safe every comand on strinig (not necessery to controlle space
			{
				printf("bucando pipe\n");
				div_str[j] = input[i];
				i++;
				j++;
			}
			printf("%s\n", div_str);
			free(div_str);
			i++;
		/*	
			if(list == NULL)
			{
				new = ft_calloc(1, sizeof(t_test));
			//	new->pos = 0;
				new->str = div_str;
				printf("metido en new: %s\n", div_str);
				list = new;
				new->prev = NULL;
				i++;
				continue;
			}
			if(list != NULL && (input[i] == '|' || input[i] == '\0'))
			{
				new = ft_calloc(1, sizeof(t_test));
				new->pos++;
				new->str = div_str;
				printf("segundo metido en new: %s\n", div_str);
				list->next = new;
				new->prev = list;
				i++;
				continue;
			}
			printf("cuanto es pos: %d\n", new->pos);
			printf("\n");

			if(input[i] == '|')//pass the pipe
			{
				printf("pos era: %d\n", new->pos);
				new->pos++;
				i++;
				printf("pos es: %d\n", new->pos);
				continue;
			}
		//	if(input[i] == '\0')
		//	{
		//		add_history(input);
		//		free(div);
		//		free(input);
		//		break;
		//	}*/
		free(input);
		}
	}
	return 0;
}
