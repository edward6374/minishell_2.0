/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/09/02 12:08:24 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_words(t_parser *all_words)
{
	t_parser	*p;

	p = all_words;
	while (p)
	{
		printf("Temp:-->%p\n", p);
		printf("Word:--%s--\n", p->word);
		printf("Next:-->%p\n", p->next);
		printf("Before:-->%p\n\n", p->before);
		p = p->next;
	}
	printf("Temp: %p\n", p);
	return (0);
}

int	multiple_words(t_parser **word_lst, t_env **env, t_vars *v, int end)
{
	int	i;

	i = v->stp - 1;
	while (++i < end)
	{
		if (v->s[i] == '<' || v->s[i] == '>' || v->s[i] == '|')
		{
			if (i - v->stp > 0 && create_word(word_lst, v, &i, 1))
				return (MALLOC);
			if (create_word(word_lst, v, &i, 0))
				return (MALLOC);
		}
		else if (v->s[i] == '$' && check_env_word(word_lst, env, v, &i))
			return (MALLOC);
	}
	if (i - v->stp > 0 && create_word(word_lst, v, &i, 1))
		return (MALLOC);
	return (0);
}

static int	find_words(t_env *env_vars, t_parser **tmp, t_vars *v)
{
	int		i;
	t_env	*env_list;

	i = v->stp - 1;
	env_list = find_env_vars(env_vars, v);
	while (++i < v->i)
	{
		check_quotes(v, &v->s[i]);
		if (v->oq && ((v->s[i + 1] == '\'' || v->s[i + 1] == '\"') || (v->s[i
						+ 1] == '\0' && v->s[i] != ' ') || v->s[i + 1] == ' ')
			&& multiple_words(tmp, &env_list, v, i + 1))
			return (free_env(env_list));
		else if (v->sq && words_sin_qts(tmp, v, &env_list, &i))
			return (free_env(env_list));
		else if (v->dq && words_dbl_qts(tmp, v, &env_list, &i))
			return (free_env(env_list));
	}
	if ((v->s[v->i] == ' ' && v->s[v->i - 1] != ' ') || (v->s[v->i] == '\0'
			&& v->s[v->i - 1] != ' '))
		if (i - v->stp > 0 && create_word(tmp, v, &i, 1))
			return (free_env(env_list));
	return (0);
}

static int	parse_line(t_min *tk, t_parser *all_words, char *s)
{
	t_vars		v;
	t_parser	*tmp;

	set_vars(&v, s);
	tmp = all_words;
	while (s[v.i])
	{
		if ((s[v.i] == ' ' && v.i == 0) || (s[v.i] == ' ' && v.oq))
			while (s[v.i] == ' ' && s[v.i] != '\0')
				v.i++;
		if ((s[v.i - 1] == ' ' || v.i == 0) && s[v.i] != ' ' && v.oq)
			v.stp = v.i;
		while ((s[v.i] != ' ' || !v.oq) && s[v.i] != '\0')
			check_quotes(&v, &s[v.i++]);
		if (find_words(tk->env, &tmp, &v))
			return (free_parser(all_words, MALLOC));
	}
	return (0);
}

int	parser(t_min *tk, char *line)
{
	t_parser	*all_words;

	if (count_quotes(line))
		return (SYNTAX);
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_all(tk, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_line(tk, all_words, line))
		return (free_all(tk, MALLOC));
	return (load_commands(tk, all_words));
}
