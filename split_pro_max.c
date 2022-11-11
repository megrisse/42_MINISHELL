/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pro_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:36:22 by hameur            #+#    #+#             */
/*   Updated: 2022/11/11 13:11:57 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*add_special(char *str, char c, int *i)
{
	int	sp;

	sp = is_special(c, 0);
	if (sp == PIPE)
		return ((*i)++, ft_strdup((char *)"|"));
	else if (sp == R_INP && str[(*i) + 1] == c)
		return ((*i) += 2, ft_strdup((char *)"<<"));
	else if (sp == R_INP && str[(*i) + 1] != c)
		return ((*i)++, ft_strdup((char *)"<"));
	else if (sp == R_OUT && str[(*i) + 1] == c)
		return ((*i) += 2, ft_strdup((char *)">>"));
	else if (sp == R_OUT && str[(*i) + 1] != c)
		return ((*i)++, ft_strdup((char *)">"));
	return (NULL);
}

int	add_value_utils(char *s, char *str, int *i, int *j)
{
	char	c;
	int		key;

	c = 0;
	key = 0;
	while (str[(*i)] != 0 && str[(*i)] != ' '
		&& is_special(str[(*i)], key) == FAILDE && key == 0)
	{
		if ((str[(*i)] == SQUOTE || str[(*i)] == DQUOTE) && c == 0)
		{
			c = str[(*i)];
			s[(*j)++] = str[(*i)++];
			while (str[(*i)] != 0 && str[(*i)] != c)
				s[(*j)++] = str[(*i)++];
			if (str[(*i)] == 0)
				return (printf("Error Quotes\n"), FAILDE);
			c = 0;
			s[(*j)++] = str[(*i)++];
			continue ;
		}
		s[(*j)++] = str[(*i)++];
	}
	s[(*j)] = 0;
	return (SUCCESS);
}

char	*add_value(char *str, int *i)
{
	char	s[1024];
	int		j;
	int		key;
	char	c;

	j = *i;
	key = 0;
	c = 0;
	while (str[(*i)] != 0 && str[(*i)] == ' ')
		(*i)++;
	if (is_special(str[j], 0) != FAILDE)
		return (add_special(str, str[(*i)], i));
	j = 0;
	while (str[(*i)] != 0 && str[(*i)] == ' ')
		(*i)++;
	if (add_value_utils(s, str, i, &j) != SUCCESS)
		return (NULL);
	while (str[(*i)] == ' ')
		(*i)++;
	return (ft_strdup(s));
}

char	**ft_realloc(char **ret, char *str)
{
	char	**cmnds;
	int		i;

	i = 0;
	cmnds = NULL;
	if (str == NULL)
		return (ret);
	if (ret == NULL)
	{
		cmnds = (char **)malloc(sizeof(char *) * 2);
		cmnds[0] = ft_strdup(str);
		cmnds[1] = NULL;
		return (cmnds);
	}
	while (ret != NULL && ret[i++] != NULL)
		;
	cmnds = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (ret[++i] != NULL)
		cmnds[i] = ft_strdup(ret[i]);
	cmnds[i++] = ft_strdup(str);
	cmnds[i] = NULL;
	return (ft_free(ret), cmnds);
}

char	**split_pro_max(char *str)
{
	int		i;
	char	**ret;
	char	*string;

	i = 0;
	ret = NULL;
	while (str[i] != 0)
	{
		string = add_value(str, &i);
		if (string == NULL)
			return (ft_free(ret), NULL);
		else if (string[0] == 0)
			return (free(string), ret);
		ret = ft_realloc(ret, string);
		free(string);
	}
	return (ret);
}

// int main(int ac, char **av)
// {
// 	char **str;
// 	int i = -1;
// 	while (1)
// 	{
// 		i = 0;
// 		char *line = readline("zebi=>");
// 		str = split_pro_max (line);
// 		while (str[i])
// 			printf("split pro max : %s\n", str[i++]);
// 		// str = ft_split(line, '|');
// 		// i = -1;
// 		// while (str != NULL && str[++i])
// 		// 	printf("%s\n", str[i]);
// 		ft_free(str);
// 		printf("\n");
// 	}
// }