/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:42:01 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 18:49:06 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	nbr_mots(char *s, char c, int nbr_mots)
{
	int	i;

	i = 0;
	if (s[0] != c && s[0])
		nbr_mots++;
	while (s[i] != 0)
	{
		if (s[i] == DQUOTE || s[i] == SQUOTE)
		{
			i = next_q(s, i, s[i]);
			if (i == FAILDE)
				return (FAILDE);
		}
		else if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != 0 && i++ > 0)
				nbr_mots++;
			else
				i++;
		}
		else
			i++;
	}
	return (nbr_mots);
}

char	*ft_copy(char *str, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = start;
	ret = (char *)malloc((end - start + 1) * sizeof(char));
	if (!ret)
		return (ret);
	while (j < end)
		ret[i++] = str[j++];
	ret[i] = 0;
	return (ret);
}

int	find_char(char *str, int pos, char c, int id)
{
	while (str[pos] == c)
		pos++;
	while (str[pos] != 0 && str[pos] != c)
	{
		if (str[pos] == DQUOTE || str[pos] == SQUOTE)
			pos = next_q(str, pos, str[pos]);
		else
			pos++;
	}
	if (id == 2)
	{
		while (str[pos + 1] == c)
			pos++;
	}
	if (str[pos] == 0 && id == 0)
		return (0);
	return (pos);
}

static char	**ft_remplissage(char *s, char **copy, char c)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	end = 0;
	end = find_char(s, end, c, 0);
	while (end != 0)
	{
		copy[i++] = ft_copy(s, start, end);
		start = find_char(s, start, c, 2) + 1;
		end = find_char(s, end + 1, c, 0);
	}
	end = find_char(s, start, c, 2);
	if ((size_t)start != strlen(s))
		copy[i++] = ft_copy(s, start, end);
	copy[i] = NULL;
	i = 0;
	return (copy);
}

char	**ft_split(char *s, char c)
{
	char	**copy;
	int		size;

	size = 0;
	if (!s)
		return (NULL);
	if (!*s)
	{
		copy = (char **)malloc (sizeof (char *) * 1);
		if (!copy)
			return (NULL);
		return (copy[0] = NULL, copy);
	}
	size = nbr_mots(s, c, size);
	if (size == FAILDE)
		return (printf("error quots\n"), NULL);
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	return (ft_remplissage(s, copy, c));
}
