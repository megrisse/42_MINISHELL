/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:41:59 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/27 19:54:59 by megrisse         ###   ########.fr       */
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
	printf("num : /****%c*****/\n", str[*id]);
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

char *fct3(t_envi *env, char *str, int *i, int *j)
{
	int id = 0;
	char c = str[(*i)++];
	
	while (str[(*i)] != 0 && str[(*i)] != c)
	{
		if (str[(*i)] == '$' && c == DQUOTE)
			i =+ fct4(env, str, i, j);
		else
			;
	}
}

char *change_str(t_envi *env, char *str)
{
	char *ret;
	int i = 0;
	int j = 0;
	
	ret = (char *)malloc(sizeof(char) * (len_str(env, str) + 1));
	while(str[i] != 0)
	{
		if(str[i] == SQUOTE || str[i] == DQUOTE)
			ft_strlcat(ret, fct3(env ,str, &i, &j));
		else if (str[i] == '$')
			ft_strlcat(ret, fct4(env, str, &i, &j));
		else
			ret[j++] == str[i++];	
	}
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
		printf("len_str %d\n", len_str(glb->env, line));
	}
}
