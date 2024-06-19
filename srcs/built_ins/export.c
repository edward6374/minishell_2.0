/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/19 12:48:58 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "g_error.h"

static void	print_export(char **arr)
{
	int	i;

	i = -1;
	if (arr == NULL)
		return ;
	while (arr[++i] != NULL)
		printf("declare -x %s\n", arr[i]);
}

static void	custom_qsort(char **env, size_t size)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	j_min;

	i = -1;
	while (++i < size - 1)
	{
		j_min = i;
		j = i + 1;
		while (++j < size)
		{
			if (env[j_min] && env[j] && ft_strcmp(env[j], env[j_min]) < 0)
				j_min = j;
		}
		if (j_min != i)
		{
			tmp = env[i];
			env[i] = env[j_min];
			env[j_min] = tmp;
		}
	}
}

static char	*insert_quotes(char *input)
{
	t_quotes	data;

	data.len = ft_strlen(input);
	data.tmp = malloc((data.len + 3) * sizeof(char *));
	data.i = 0;
	data.j = 0;
	while (input[data.i] != '\0')
	{
		if (input[data.i] == '=')
		{
			data.tmp[data.j] = input[data.i];
			data.j++;
			data.tmp[data.j] = '"';
		}
		else
			data.tmp[data.j] = input[data.i];
		data.i++;
		data.j++;
	}
	data.tmp[data.j] = '"';
	data.tmp[data.j + 1] = '\0';
	free(input);
	return (data.tmp);
}

int	ft_export(t_min *tk, t_cmd *tmp)
{
	char	**env;
	int		i;

	if (tmp->args[1] == NULL)
	{
		env = take_double(tk, tk->env);
		i = -1;
		while (env[++i] != NULL)
			env[i] = insert_quotes(env[i]);
		custom_qsort(env, ft_len_dptr(env));
		print_export(env);
		return (0);
	}
	else
		return (export_add(tk->env, tmp->args));
}

// this is the export_add

t_env	*new_env(char *str, char *value)
{
	t_env	*new;
	char	*name;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	name = ft_strjoin(str, "=");
	if (!name)
		exit_error(g_error_array[0], MALLOC);
	new->name = name;
	if (ft_strlen(value) == 0)
		new->value = NULL;
	else
		new->value = value;
	new->next = NULL;
	return (new);
}
