/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:41:59 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/11 14:10:32 by hameur           ###   ########.fr       */
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

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != DQUOTE && str[i] != SQUOTE)
		i++;
	if (str[i] == DQUOTE || str[i] == SQUOTE)
		return (1);
	return (0);
}

t_list	*init_list(t_global *glb, t_list *head, char *str, int key)
{
	char	**cmnd;
	char	*temp;
	int		i;

	cmnd = split_pro_max(str);
	i = 0;
	head = NULL;
	if (cmnd == NULL)
		return (ft_putstr_fd(2, (char *)"Error quotes\n"), NULL);
	while (cmnd[i] != NULL)
	{
		temp = change_str(glb, cmnd[i++]);
		if (add_back_list(&head, new_list(temp, key,
					check_quotes(cmnd[i - 1]))) != SUCCESS)
			return (ft_free(cmnd), free(temp), free_list(&head, head), NULL);
		free(temp);
	}
	ft_free(cmnd);
	return (head);
}
