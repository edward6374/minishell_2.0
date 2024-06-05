/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/02 18:29:42 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_ERROR_H
# define G_ERROR_H

static const char		*g_error_array[] = {
	"Malloc error",
	"Syntax error",
	"syntax error near unexpected token `|\'",
	"syntax error near unexpected token `newline\'",
	"open error",
	"command not found",
	"permission denied",
	"no such file or directory",
	"file not readable",
	"file not writeable",
};

#endif