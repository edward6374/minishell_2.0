/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2024/03/08 20:56:18 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//# include "minishell.h"
typedef struct s_test
{
    int pos;
    char *str;
    struct s_test *prev;
    struct s_test *next;
} t_test;
void	*put_list(char *div_str);
void	pos_num(char *input);

#endif
