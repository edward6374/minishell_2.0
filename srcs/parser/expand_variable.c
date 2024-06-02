/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:14:33 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	send_variable(t_min *tk, char *var, char *value)
{
	int	i;
	t_env	*tmp;

	i = -1;
	tmp = tk->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
		{
			while (tmp->value[++i])
				value[i] = tmp->value[i];
			value[i] = '\0';
//			printf("value: %s\n", value);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	dollar_found(char *str, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
//	printf("UN DOLLAR🤑\n");
	while (str[i] != '\0' && ((str[i] > 64 && str[i] < 91)
			|| (str[i] > 96 && str[i] < 123)
		|| (str[i] > 47 && str[i] < 58) || str[i] == '_'))
	{
//		printf("added✅: -%c-\n", str[i]);
		var[j++] = str[i++];
	}
	var[j++] = '=';
	var[j] = '\0';
//	printf("variable: %s\n", var);
}

static void	find_dollar(t_min *tk, t_word *tmp, char *var)
{
	int		i;
	int		sin;
	char	value[2000];

	i = -1;
	sin = 0;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '\'' && sin == 0)
			sin++;
		else if (tmp->str[i] == '\'' && sin == 1)
			sin--;
		if (tmp->str[i] == '$' && sin == 0)
		{
			dollar_found(&tmp->str[++i], var);
			send_variable(tk, var, value);
			i += change_word(tmp, i, ft_strlen(var) - 1, value);
		}
	}
}

void	check_dollar(t_min *tk, t_pipe *list)
{
	char	var[2000];
	t_word	*tmp;

	while (list != NULL)
	{
		tmp = list->words;
		while (tmp != NULL)
		{
			find_dollar(tk, tmp, var);
			tmp = tmp->next;
		}
		list = list->next;
	}
}
