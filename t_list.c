/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:41:59 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/07 17:23:35 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini.h"

void	free_list(t_list **root, t_list *node)
{
	if (node == NULL)
		return ;
	free_list(root, node->next);
    free(node->str);
	free(node);
}



int is_word(char *str)
{
    int i;

    i = -1;
    while (str[++i] != 0)
    {
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
            return (FAILDE);
    }
    return (SUCCESS);
}

int check_type(char *str, int key)
{
	if (key == 1)
		return (WORD);
    else if (key == 0 && is_word(str) == SUCCESS)
        return (WORD);
    else if (str[0] == '|' && str[1] == 0)
        return (PIPE);
    else if (str[0] == '>' && str[1] != '>')
        return (R_OUT);
    else if (str[0] == '<' && str [1] != '<')
        return(R_INP);
    else if (str[0] == '>' && str[1] == '>')
        return (DR_OUT);
    else if (str[0] == '<' && str[1] == '<')
        return (DR_INP);
    return (FAILDE);
}

t_list *new_list(char *str, int key, int quote)
{
    t_list  *node;

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


int add_back_list(t_list **head, t_list *new_node)
{
    t_list *temp = *head;

    if (new_node == NULL)
        return (printf("error add_back_list\n"), FAILDE);
    if (temp == NULL)
        return(*head = new_node, SUCCESS) ;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return (SUCCESS);
}

char *nume_var(char* str, int *id)
{
	int i = 0;
	int	j = (*id) + 1;
	(*id)++;
	while (str[*id] != 0 && str[*id] != '$' && str[*id] != ' ' && str[*id] != DQUOTE && str[*id] != SQUOTE)
	{
		i++;
		(*id)++;
	}
	char *ret  = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[j] != 0 && str[j] != '$' && str[j] != ' ' && str[j] != DQUOTE && str[j] != SQUOTE)
		ret[i++] = str[j++];
	ret[i] = 0;
	return(ret);
}


int fct2(t_global *glb, char *s, int *i)
{
	t_envi *temp = glb->env;
	char	*exit_s;
	int		len;

	char *var_name = nume_var(s, i);
	exit_s = ft_itoa(glb->status);
	len = ft_strlen(exit_s);
	if (ft_strncmp(var_name, (char *)"?", 1) == SUCCESS)
		return (free(var_name), free(exit_s), len);
	else if (var_name[0] == 0)
		return (free(var_name), free(exit_s), 1);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name, ft_strlen(glb->env->var_name)) == SUCCESS)
			return (free(var_name), free(exit_s), ft_strlen(glb->env->var_value));
		temp = temp->next;
	}
	return (free(var_name), free(exit_s), 0);
}


int fct(t_global *glb, char *str, int *id, char c)
{
	int i = 0;
	(*id)++;

	while (str[(*id)] != 0 && str[(*id)] != c)
	{
		if (str[(*id)] == '$' && c == DQUOTE)
			i += fct2(glb, str, id);
		else
		{
			i++;
			(*id)++;
		}
	}
	// (*id) = j;
	return (i);
}


int len_str(t_global *glb, char *str)
{
	int	i = 0;
	int ret = 0;
	while (str[i] != 0)
	{
		if (str[i] == DQUOTE || str[i] == SQUOTE)
			ret += fct(glb, str, &i,  str[i]);
		else if (str[i] == '$')
			ret += fct2(glb, str, &i);
		else
			ret++;
		i++;
	}
	return (ret);
}

void	fct5(char *str, int **tab, char *s)
{
	int	i = 0;

	
	while (s[i] != 0)
		str[(*tab[1])++] = s[i++];
}

void	fct4(t_global *glb, char *str, char *ret, int **tab)
{
	t_envi *temp = glb->env;
	char	*exit_s;

	exit_s = ft_itoa(glb->status);
	char *var_name = nume_var(str, tab[0]);
	if (var_name[0] == 0)
		fct5(ret, tab, (char *)"$");
	else if (ft_strncmp(var_name, (char *)"?", 1) == SUCCESS)
		fct5(ret, tab, exit_s);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name, ft_strlen(glb->env->var_name)) == SUCCESS)
			fct5(ret, tab, temp->var_value);
		temp = temp->next;
	}
	free(var_name);
	free(exit_s);
}


void	fct3(t_global *glb, char *str, char *ret, int **tab)
{
	char c = str[(*tab[0])++];
	
	while (str[(*tab[0])] != 0 && str[*tab[0]] != c)
	{
		if (str[(*tab[0])] == '$' && c == DQUOTE)
			fct4(glb, str, ret, tab);
		else
			ret[(*tab[1])++] = str[(*tab[0])++];
	}
	(*tab[0])++;
}

char *change_str(t_global *glb, char *str)
{
	char *ret;
	int i = 0;
	int j = 0;
	int	**tab = (int **)malloc(sizeof(int *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = &i;
	tab[1] = &j;

	int key = len_str(glb, str);
	ret = (char *)malloc(sizeof(char) * (key + 1));
	if (!ret)
		return(NULL);
	while(str[i] != 0)
	{
		if(str[i] == SQUOTE || str[i] == DQUOTE)
			fct3(glb ,str, ret, tab);
		else if (str[i] == '$')
			fct4(glb, str, ret, tab);
		else
			ret[j++] = str[i++];	
	}
	ret[j] = 0;
	free(tab);
	return (ret);
}

int check_list(t_list *list)
{
	t_list *temp = list;
	while (temp != NULL)
	{
		// if (temp->type != WORD && temp->type != PIPE && temp->next == NULL)
		// return (ft_putstr_fd(2, "syntax error near unexpected token `newline'\n"), FAILDE);
		temp = temp->next;
	}
	return (SUCCESS);
}

int check_quotes(char *str)
{
	int i = 0;
	while (str[i] != 0 && str[i] != DQUOTE && str[i] != SQUOTE)
		i++;
	if (str[i] == DQUOTE || str[i] == SQUOTE)
		return (1);
	return (0);
}

t_list *init_list(t_global *glb, t_list *head, char *str, int key)
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
		
        if (add_back_list(&head, new_list(temp, key, check_quotes(cmnd[i - 1]))) != SUCCESS)
            return (ft_free(cmnd), free(temp), free_list(&head, head), ft_putstr_fd(2, "Error pipe\n"), NULL);//free
		free(temp);
    }
    ft_free(cmnd);
	if (check_list(head) != SUCCESS)
		return (free (str), free_list(&head, head), NULL);
    return (head);
}

// void print_l(t_list *head)
// {
// 	while (head != NULL)
// 	{
// 		printf("init list :type = %d %s\n", head->type, head->str);
// 		head = head->next;
// 	}
// }

// int main(int ac, char **av, char **env)
// {
// 	t_global *glb = (t_global *)malloc(sizeof(t_global));
// 	glb->env = init_envi(env);
// 	t_list *head;
// 	char *line;
// 	while (1)
// 	{
// 		line = readline("zeeeeebi =>");
// 		head = init_list(glb, head, line);
		
// 		print_l(head);
// 	}
// }
