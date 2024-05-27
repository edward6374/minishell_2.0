/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:39 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/27 10:00:17 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
#include "struct.h" 

static t_env	*find_path_var(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH=", 6) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*take_full_path(char *pwd, char *str)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(pwd, "/");
	if (!tmp)
		exit(MALLOC);
	new = ft_strjoin(tmp, str);
	if (!new)
		exit(MALLOC);
	return (new);
}

int	get_cmd_path(t_min *tk, t_cmd *new, char *word)
{
	int		i;
	char	*path;
	char	**split;
	t_env	*tmp;

	tmp = find_path_var(tk->env);
	if (!tmp)
	{
		new->cmd = ft_strdup(word);
		return (CMD_NOT_FOUND);
	}
	split = ft_split(tmp->value, ':');
	if (!split)
		exit(MALLOC);
	i = 0;
	while (split[i])
	{
		path = take_full_path(split[i], word);
		if (access(path, X_OK) == 0)
		{
			ft_free_dptr(split);
			new->cmd = path;
			return (0);
		}
		else if (access(path, F_OK) == 0)
		{
			ft_free_dptr(split);
			free(path);
			new->cmd = ft_strdup(word);
			return (CMD_FOUND_NOT_EX);
		}
		i++;
	}
	ft_free_dptr(split);
	free(path);
	new->cmd = ft_strdup(word);
	return (CMD_NOT_FOUND);
}

static void	put_args(t_cmd *new, t_test *node)
{
	int		n;
	t_word	*tmp_words;

	n = 0;
	tmp_words = node->words;
	while(tmp_words)
	{
		if(tmp_words->str[0] != '<' && tmp_words->str[0] != '>')
			n++;
		else
			tmp_words = tmp_words->next;
		tmp_words = tmp_words->next;
	}
	new->args = ft_calloc(n + 1, sizeof(char *));
	if (!new->args) // en caso de fallo👾
		exit(MALLOC);
	n = 0;
	tmp_words = node->words;
	while(tmp_words)
	{
		if(tmp_words->str[0] == '<' || tmp_words->str[0] == '>')
			tmp_words = tmp_words->next;
		else
		{
			new->args[n++] = ft_strdup(tmp_words->str);
			if (!new->args) //👾
				exit(MALLOC);
		}
		tmp_words = tmp_words->next;
	}
}
static void	command_inside(t_min *tk, t_cmd *new, t_test *node)
{
	t_word	*tmp_words;

	tmp_words = node->words;
	while(tmp_words)
	{
		if((tmp_words->prev == NULL && tmp_words->str[0] != '<' && tmp_words->str[0] != '>')
			|| (tmp_words->prev && tmp_words->prev->str[0] != '<' && tmp_words->prev->str[0] != '>'))
		{
			new->ok = get_cmd_path(tk, new, tmp_words->str);
			break;
		}
		tmp_words = tmp_words->next;
	}
	if (!new->ok)
		put_args(new, node);
}

static void	put_command_list(t_min *tk, t_cmd **list_cmd, t_test *node)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		exit(MALLOC);
	new->out_fd = 1;
	new->hdoc = ft_calloc(1, sizeof(t_here_doc));
	if (!new->hdoc)
		exit(MALLOC);
//	new->ok = do_open(node, new);
	do_open(node, new); //he quitado el new->ok ya que ya lo hago en el do_open lo de los returns. Quizas es necesario por eso lo comento
	if(new->ok == 0)
		command_inside(tk, new, node);
	if(!(*list_cmd))
		*list_cmd = new;
	else
	{
		tmp = *list_cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->before = tmp;
		new->n = new->before->n + 1;
	}
}


t_cmd	*get_command_list(t_min *tk, t_test *list)
{
	t_test	*tmp;
	t_cmd	*list_cmd;

	list_cmd = NULL;
	tmp = list;
	while (tmp != NULL)
	{
		put_command_list(tk, &list_cmd, tmp);
		tmp = tmp->next;
	}
	return (list_cmd);
}

