/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:41:59 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/08 22:19:38 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*new_list(char *str, int key, int quote)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	if (key == 0)
		node->type = check_type(str, quote);
	else
		node->type = WORD;
	if (node->type == FAILDE)
		return (NULL);
	node->next = NULL;
	return (node);
}

int	add_back_list(t_list **head, t_list *new_node)
{
	t_list	*temp;

	temp = *head;
	if (new_node == NULL)
		return (printf("error add_back_list\n"), FAILDE);
	if (temp == NULL)
		return (*head = new_node, SUCCESS);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (SUCCESS);
}

char	*change_str(t_global *glb, char *str)
{
	char	*ret;
	int		**tab;
	int		i;
	int		j;
	int		key;

	tab = (int **)malloc(sizeof(int *) * 2);
	i = 0;
	j = 0;
	if (!tab)
		return (NULL);
	tab[0] = &i;
	tab[1] = &j;
	key = len_str(glb, str);
	ret = (char *)malloc(sizeof(char) * (key + 1));
	if (!ret)
		return (NULL);
	while (str[i] != 0)
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
			fct3(glb, str, ret, tab);
		else if (str[i] == '$')
			fct4(glb, str, ret, tab);
		else
			ret[j++] = str[i++];
	}
	ret[j] = 0;
	return (free(tab), ret);
}

t_list	*init_list(t_global *glb, t_list *head, char *str, int key)
{
	char	**cmnd;
	char	*temp;
	int		i;

	cmnd = ft_split(str, ' ');
	i = 0;
	head = NULL;
	if (cmnd == NULL)
		return (ft_putstr_fd(2, (char *)"Error quotes\n"), NULL);
	while (cmnd != NULL && cmnd[i] != NULL)
	{
		temp = change_str(glb, cmnd[i++]);
		if (add_back_list(&head, new_list(temp,
					key, check_quotes(cmnd[i - 1]))) != SUCCESS)
			return (ft_free(cmnd), free(temp), free_list(&head, head),
				ft_putstr_fd(2, "Error pipe\n"), NULL);
		free(temp);
	}
	ft_free(cmnd);
	if (check_list(head) != SUCCESS)
		return (free (str), free_list(&head, head), NULL);
	return (head);
}
