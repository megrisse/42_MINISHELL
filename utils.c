/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:58:17 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/10 16:57:54 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strdup(char *s1)
{
	char	*p;
	int		i;

	i = ft_strlen(s1);
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		p[i] = s1[i];
	p[i] = 0;
	return (p);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
		;
	return (i);
}

char	*ft_strlcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	j = -1;
	i = ft_strlen(s1);
	i += ft_strlen(s2);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		str[i] = s1[i];
	while (s2[++j] != 0)
		str[i++] = s2[j];
	str[i] = 0;
	return (str);
}

int	ft_strncmp(char *s1, char *s2, int i)
{
	int	x;

	x = 0;
	if (s1 == NULL || s2 == NULL)
		return (FAILDE);
	while (s1[x] != 0 && s2[x] != 0 && s1[x] == s2[x] && i > x)
		x++;
	if (s1[x] == s2[x] && i == x)
		return (SUCCESS);
	return (s1[x] - s2[x]);
}

int	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
		write(fd, &str[i], 1);
	return (i);
}
