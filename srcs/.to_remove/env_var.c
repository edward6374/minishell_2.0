/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/28 16:04:30 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "parser.h"

int	change_env_list(t_parser **word_lst, t_env **env, t_vars *v, t_word data)
{
	t_env	*next;

	if (!data.check)
		data.word = check_spaces(env, ft_strdup((*env)->value));
	if (!data.word || add_or_join(word_lst, v, data.word, 0))
		return (MALLOC);
	if (data.check)
		v->stp = (*data.idx)--;
	else
	{
		v->stp = *data.idx + ft_strlen((*env)->name);
		next = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = next;
		if (*env)
			(*env)->before = NULL;
	}
	return (0);
}

void static	not_env_var(t_vars *v, t_word *data)
{
	data->check = 1;
	if (v->s[++(*data->idx)] == '?')
		(*data->idx)++;
	while (ft_isalnum(v->s[(*data->idx)]))
		(*data->idx)++;
	if (v->s[data->i + 1] == '?' || ft_isdigit(v->s[data->i + 1]))
	{
		if (ft_isdigit(v->s[data->i + 1]))
			data->i = data->i + 2;
		data->word = ft_substr(v->s, data->i, *data->idx - data->i);
	}
	else
		data->word = ft_strdup("");
}

int	check_env_word(t_parser **word_lst, t_env **env, t_vars *v, int *i)
{
	t_word	data;

	data.i = *i;
	data.idx = i;
	data.check = 0;
	if (*i - v->stp > 0 && (v->s[v->stp - 1] != ' ' || v->s[*i - 1] != ' '))
	{
		data.word = ft_substr(v->s, v->stp, *i - v->stp);
		if (!data.word || create_word(word_lst, v, i, 1))
			return (MALLOC);
	}
	if ((!(*env) || ft_strncmp(&v->s[*i + 1], (*env)->name,
				ft_strlen((*env)->name) - 1)) && ++data.check)
		not_env_var(v, &data);
	return (change_env_list(word_lst, env, v, data));
}

static t_env	*new_list_elem(t_env *found, t_env **old_tmp, t_vars *v, int *i)
{
	int		count;
	t_env	*new;

	count = *i + 1;
	while ((v->s[count] >= 'a' && v->s[count] <= 'z') || (v->s[count] >= 'A'
			&& v->s[count] <= 'Z') || (v->s[count] >= '0'
			&& v->s[count] <= '9'))
		count++;
	*i = count - 1;
	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(found->name);
	new->value = ft_strdup(found->value);
	if (old_tmp)
	{
		(*old_tmp)->next = new;
		new->before = *old_tmp;
	}
	return (new);
}

t_env	*find_env_vars(t_env *env, t_vars *v)
{
	int		i;
	t_env	*tmp;
	t_env	*found;
	t_env	*env_list;

	env_list = NULL;
	i = v->stp - 1;
	while (++i < v->i)
	{
		check_quotes(v, &v->s[i]);
		if ((v->oq || v->dq) && v->s[i] == '$')
		{
			found = search_env(env, &v->s[i + 1], find_env);
			if (found && !env_list)
			{
				env_list = new_list_elem(found, NULL, v, &i);
				tmp = env_list;
			}
			else if (found)
				tmp = new_list_elem(found, &tmp, v, &i);
		}
	}
	return (env_list);
}
