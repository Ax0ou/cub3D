/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:59:06 by aalvarad          #+#    #+#             */
/*   Updated: 2025/11/07 09:08:19 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_word(char const *s, char c);
static void		copy(char const *s, size_t start, size_t len, char *dst);
static void		free_all(char **tab, size_t upto);
static char		**fill_tab(char **tab, char const *s, char c, size_t nb);

char	**ft_split(char const *s, char c)
{
	size_t	nb_mots;
	char	**tab;

	if (!s)
		return (NULL);
	nb_mots = cnt_word(s, c);
	tab = (char **) ft_calloc (nb_mots + 1, sizeof * tab);
	if (tab == NULL)
		return (NULL);
	return (fill_tab(tab, s, c, nb_mots));
}

static char	**fill_tab(char **tab, char const *s, char c, size_t nb)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	i = 0;
	while (i < nb)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		tab[i] = (char *)malloc((end - start) + 1);
		if (tab[i] == NULL)
			return (free_all(tab, i), NULL);
		copy(s, start, end - start, tab[i]);
		i++;
		start = end;
	}
	tab[i] = NULL;
	return (tab);
}

static size_t	cnt_word(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static void	copy(char const *s, size_t start, size_t len, char *dst)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		dst[j] = s[start + j];
		j++;
	}
	dst[len] = '\0';
}

static void	free_all(char **tab, size_t upto)
{
	while (upto > 0)
	{
		upto--;
		free(tab[upto]);
	}
	free(tab);
}
