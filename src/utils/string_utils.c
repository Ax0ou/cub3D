/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/09 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** is_space — 1 for ' ' and '\t' (decide as a team if '\t' is accepted
** between an identifier and its value; write the choice in ARCHITECTURE.md).
*/
int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/*
** skip_spaces — returns a pointer to the first non-space char of str.
*/
char	*skip_spaces(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (&str[i]);
}

/*
** is_blank_line — 1 if the line is empty or only contains spaces.
** A NULL line counts as blank.
*/
int	is_blank_line(char *line)
{
	char	*rest;

	if (!line)
		return (1);
	rest = skip_spaces(line);
	if (rest[0] == '\0')
		return (1);
	return (0);
}
