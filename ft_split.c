/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:42:01 by hameur            #+#    #+#             */
/*   Updated: 2022/10/28 21:18:20 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	next_q(char *s, int i, char c, int key)
{
	i++;
	while (s[i] != 0 && s[i] != c)
		i++;
	if (s[i] == 0 && key == 0)
		return(FAILDE);
	if (key == 1 && s[i] == 0)
		return (i);
	return (i + 1);
}

int	nbr_mots	(char *s, char c)
{
	int	i;
	int	nbr_mots;

	i = 0;
	nbr_mots = 0;
	if (s[0] != c && s[0])
		nbr_mots++;
	while (s[i] != 0)
	{
		if (s[i] == DQUOTE || s[i] == SQUOTE)
		{
			i = next_q(s, i, s[i], 0);
			if (i == FAILDE)
				return (FAILDE);
		}
		else if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != 0)
			{
				nbr_mots++;
				i++;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (nbr_mots);
}

char *ft_copy(char *str, int start, int end)
{
	char *ret;
	int	i = 0;
	int j = start;
	ret = (char *)malloc((end - start + 1) * sizeof(char));
	while (j < end)
		ret[i++] = str[j++];
	ret[i] = 0;
	return (ret);
}

int find_char(char *str, int pos, char c, int id)
{
	while(str[pos] == c)
		pos++;
	while (str[pos] != 0 && str[pos] != c)
	{
		if (str[pos] == DQUOTE || str[pos] == SQUOTE)
			pos = next_q(str, pos, str[pos], 0);
		else
			pos++;
	}
	if (id == 2)
	{
		while (str[pos + 1] == c)
			pos++;
	}
	if (str[pos] == 0 && id == 0)
		return(0);
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
	end =  find_char(s, start, c, 2);
	if ((size_t)start != strlen(s))
		copy[i++] = ft_copy(s, start, end);
	copy[i] = NULL;
	i = 0;
	// while (copy[i] != 0)
	// 	printf("copy = %s\n", copy[i++]);
	return (copy);
}

char	**ft_split(char *s, char c)
{
	char	**copy;
	int		size;
	if (!s)
		return (NULL);
	if (!*s)
	{
		copy = (char **)malloc (sizeof (char *) * 1);
		if (!copy)
			return (NULL);
		return (copy[0] = NULL, copy);
	}
	size = nbr_mots(s, c);
	if (size == FAILDE)
		return (printf("error quots\n"), NULL);
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	return (ft_remplissage(s, copy, c));
}

/*
int main(int ac, char **av)
{
	char **str;
	int i;
	while (1)
	{
		char *line = readline("zebi=>");
		str = ft_split(line, '|');
		i = -1;
		while (str != NULL && str[++i])
			printf("%s\n", str[i]);
		printf("\n");
	}
}

*/
