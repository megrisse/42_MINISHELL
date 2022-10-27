/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:41:59 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/27 21:13:04 by megrisse         ###   ########.fr       */
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

int check_type(char *str)
{
    int i = 0;
    if (is_word(str) == SUCCESS)
        return (WORD);
    else if (str[0] == '|' && str[1] == 0)
        return (PIPE);
    else if (str[0] == '>' && str[1] == 0)
        return (R_OUT);
    else if (str[0] == '<' && str [1] == 0)
        return(R_INP);
    else if (str[0] == '>' && str[1] == '>' && str[2] == 0)
        return (DR_OUT);
    else if (str[0] == '<' && str[1] == '<' && str[2] == 0)
        return (DR_INP);
    return (FAILDE);
}

t_list *new_list(char *str)
{
    t_list  *node;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->str = ft_strdup(str);
    node->type = check_type(str);
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
	while (str[*id] != 0 && str[*id] != '$' && str[*id] != ' ' && str[*id] != DQUOTE)
	{
		i++;
		(*id)++;
	}
	char *ret  = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[j] != 0 && str[j] != '$' && str[j] != ' ' && str[j] != DQUOTE)
		ret[i++] = str[j++];
	ret[i] = 0;
	return(ret);
}


int fct2(t_envi *env, char *s, int *i)
{
	t_envi *temp = env;

	char *var_name = nume_var(s, i);
	printf("ini i = %d && var_name = %s\n", *i, var_name);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name, ft_strlen(env->var_name)) == SUCCESS)
			return (free(var_name), ft_strlen(env->var_value));
		temp = temp->next;
	}
	return (free(var_name), 0);
}


int fct(t_envi *env, char *str, int *id, char c)
{
	int i = 0;
	int j = (*id) + 1;

	while (str[j] != 0 && str[j] != c)
	{
		if (str[j] == '$' && c == DQUOTE)
			i += fct2(env, str, &j);
		else
		{
			i++;
			j++;
		}
		printf("len_str : /** %c **/ ret = %d\n", str[j], i);
	}
	(*id) = j;
	return (i);
}


int len_str(t_envi *env, char *str)
{
	int	i = 0;
	int ret = 0;
	while (str[i] != 0)
	{
		if (str[i] == DQUOTE || str[i] == SQUOTE)
			ret += fct(env, str, &i,  str[i]);
		else if (str[i] == '$')
			ret += fct2(env, str, &i);
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
		str[(*tab[1]++)] = s[i++];
}

void	fct4(t_envi *env, char *str, char *ret, int **tab)
{
	t_envi *temp = env;

	char *var_name = nume_var(str, tab[0]);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name, ft_strlen(env->var_name)) == SUCCESS)
		{
			fct5(ret, tab, temp->var_value);
			free(var_name);
		}
		temp = temp->next;
	}
	free(var_name);
}


void	fct3(t_envi *env, char *str, char *ret, int **tab)
{
	int id = 0;
	char c = str[(*tab[0])++];
	
	while (str[(*tab[0])] != 0 && str[*tab[0]] != c)
	{
		if (str[(*tab[0])] == '$' && c == DQUOTE)
			fct4(env, str, ret, tab);
		else
			ret[(*tab[1]++)] = str[(*tab[0]++)];
	}
	(*tab[0])++;
}

char *change_str(t_envi *env, char *str)
{
	char *ret;
	int i = 0;
	int j = 0;
	int	**tab = (int **)malloc(sizeof(int *) * 2);
	tab[0] = &i;
	tab[1] = &j;

	ret = (char *)malloc(sizeof(char) * (len_str(env, str) + 1));
	while(str[i] != 0)
	{
		if(str[i] == SQUOTE || str[i] == DQUOTE)
			fct3(env ,str, ret, tab);
		else if (str[i] == '$')
			fct4(env, str, ret, tab);
		else
			ret[j++] = str[i++];	
	}
	free(tab);
	return (ret);
}

int init_list(t_global *glb, char *str)
{
	t_list *head = glb->cmnd_list;
    char	**cmnd;
    char	*temp;
	int		i;

    cmnd = ft_split(str, ' ');
    i = 0;
    head = NULL;
    //cmnd = NULL : kayna a quote whda
    while (cmnd != NULL && cmnd[i] != NULL)
    {
        temp = change_str(glb->env, cmnd[i++]);
        if (add_back_list(&head, new_list(temp)) != SUCCESS)
            return (FAILDE);//free
    }
    ft_free(cmnd);
    return (SUCCESS);
}




int main(int ac, char **av, char **env)
{
	t_global *glb = (t_global *)malloc(sizeof(t_global));
	glb->env = init_envi(env);
	char *line;
	while (1)
	{
		line = readline("zeeeeebi =>");
		printf("change_str  %s\n", change_str(glb->env, line));
	}
}
