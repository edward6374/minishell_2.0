/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2024/03/16 17:44:29 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//# include "minishell.h"
typedef struct s_test
{
    char *str;
    struct s_test *prev;
    struct s_test *next;
} t_test;

typedef struct s_word // lo usaremos para separar palabrras
{
    char *word;
    struct s_test *prev;
    struct s_test *next;
} t_word;

void	put_list(t_test **list, char *div_str);
void	print_list(t_test **list);
void	dividing_words(char *div_str);//pot ser no cal

#endif
