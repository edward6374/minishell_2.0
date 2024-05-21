/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:39 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/21 17:31:22 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
#include "struct.h" //⚠️  possible error ⚠️\

void	put_args(t_cmd *new, t_text *node)
{
	int n;
	t_words	*tmp_words;

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
	while(tmp_words)
	{
		if(tmp_words->before->str[0] == '<' || tmp_words->before->str[0] == '>')
			tmp_words = tmp_words->next;
		else
		{
			new->args[n++] = ft_strdup(tmp_words->str);
			if (!new->args) //👾
				exit(MALLOC);
		}
		tmp_word = tmp_words->next;
	}
}
void	command_inside(t_cmd *new, t_test *node)
{
	t_word *tmp_words;
	char *path;

	tmp_words = node->words;
	while(tmp->words != NULL)
	{
		if(tmp_words->before->str[0] == '<' || tmp_words->before->str[0] == '>')
		}
			tmp_words = node->words;
			path = get_path(tmp_words->str)
			if(access(path, X_OK) != 0)
			{
				new->cmd = ft_strdup(tmp_words->str);
				if (!new->cmd) //👾
					exit(MALLOC);
				if (access(path, F_OK) == 0)
					new->ok = CMD_FOUND_NOT_EX;
				else
					new->ok = CMD_NOT_FOUND;
			}
			else
			{
				new->cmd = ft_strdup(path);
				if (!new->cmd)
					exit(MALLOC);
			}
			break;
		}
		tmp->words = tmp_words->next;
	}
	put_args(new, tmp_words);
}
void	put_command_list(t_cmd **list_cmd, t_test *node)
{
	t_cmd *new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		exit(MALLOC);
	new->out_fd = 1;
//	new->ok = do_open(node, new);
	do_open(node, new); //he quitado el new->ok ya que ya lo hago en el do_open lo de los returns. Quizas es necesario por eso lo comento
	if(new->ok == 0)
		command_inside(new, node);
	if(!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->before = tmp;
		new->n = new->before->n + 1;
	}
}


void	get_command_list(t_test *list)
{
	t_test	*tmp;
	t_cmd	*list_cmd;

	*list_cmd = NULL;
	tmp = list;
	while (tmp != NULL)
	{
		put_command_list(&list_cmd, tmp);
		tmp = tmp->next;
	}
}

