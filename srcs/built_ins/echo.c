/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/17 15:27:59 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include <stdbool.h>

static void	check_flag(char **args, int *i, int *no_newline)
{
	int	j;
	int	l;

	j = 1;
	*no_newline = false;
	while (42)
	{
		l = 0;
		while (args[j][l])
		{
			if ((l == 0 && args[j][l] != '-')
			|| (l != 0 && args[j][l] != 'n'))
				return ;
			l++;
		}
		*i = *i + 1;
		*no_newline = true;
		j++;
	}
}

static void	print_echo(char *str)
{
	if (!ft_strncmp(str, "> ", 3) || !ft_strncmp(str, ">> ", 4)
		|| !ft_strncmp(str, "< ", 3) || !ft_strncmp(str, "<< ", 4)
		|| !ft_strncmp(str, "| ", 3))
		str[ft_strlen(str) - 1] = '\0';
	printf("%s", str);
}

int	ft_echo(char **args, int i)
{
	int	no_newline;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	check_flag(args, &i, &no_newline);
	while (args[i] != NULL)
	{
		print_echo(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
