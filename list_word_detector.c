#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
//solo hay que quitatr los espacios de mas, no los que definen lo que es una palabra
//IMPORTANTE, usar la otra lista..
void	put_list(t_test **list, char *div_str)//a ver
{
	t_test	*tmp;
	t_test	*new;

	new = ft_calloc(1, sizeof(t_test));
	new->str = div_str;
	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

// funcion para printear la lista, esto va mas arriba
void	print_list(t_test **list)
{
	t_test *temp;

	temp = *list;
	while (temp != NULL)
    {
        printf("Que hay en la lista: -%s-\n", temp->str);
        temp = temp->next;
    }
}
