/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:44:38 by hameur            #+#    #+#             */
/*   Updated: 2022/10/27 19:29:53 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL

#define MINISHELL

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

# define SUCCESS 0
# define FAILDE -1

# define DQUOTE 34
# define SQUOTE 39

# define WORD 10
# define PIPE 11
# define VAR 14
# define R_INP 15
# define R_OUT 16
# define DR_INP 17
# define DR_OUT 18


//_____________________ -Env-Fcts- _____________________//

typedef struct t_envi
{
	char	*env_x;
	char	*var_name;
	char	*var_value;
	struct t_envi	*next;
}	t_envi;

void    free_env(t_envi **env);
void	add_back(t_envi **envi, t_envi *new_node);
t_envi	*new_node(char *env_x);
t_envi	*init_envi(char **env);
void	add_place(t_envi **envi, t_envi *new_node, int i);
int		size_envi(t_envi *env);
void	delete_node_env(t_envi **env, int i);
char    *value_var(char *env);
char    *name_var(char *env);
void	add_front(t_envi **envi, t_envi *new_node);
int		change_var_value(t_envi *env,char *name, char *value);



//-------------------------------------------------------//



typedef struct t_global
{
	struct t_envi	*env;  //v
	struct t_list	*cmnd_list; //v
	char			*cmnd; //v
	int				status;

}	t_global;

typedef struct t_list
{
	char	*str;
	int		type;
	struct t_list	*next;
}	t_list;

typedef struct t_cmnd
{
	char **cmnd;
	char **env;
}	t_cmnd;



int		ft_strlen(char *str);
int		ft_putstr_fd(int fd, char *str);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
char	*ft_strlcat(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int i);



char	**find_paths(t_envi **env);
char	*remove_debut(char* s, int i);
int		other_fct(t_cmnd *cmnd, t_envi **env);
int		exec_cmnd(t_list *cmnd_list, t_envi *env);

int		builtin_fct(t_cmnd *cmnd, t_envi **env);

void	ft_free(char **str);

int		ft_pwd(t_cmnd *cmnd, t_envi **env);
int		ft_exit(t_cmnd *cmnd, t_envi **env);
int		ft_cd(t_cmnd *cmnd, t_envi **env);
int		ft_echo(t_cmnd *cmnd, t_envi **env);
int		ft_env(t_cmnd *cmnd, t_envi **env);
int		ft_export(t_cmnd *cmnd, t_envi **env);
int		ft_unset(t_cmnd *cmnd, t_envi **env);


void	free_list(t_list **root, t_list *node);
int		init_list(t_global *glb, char *str);

//___________redirection_fcts______________
int		redirection_out(char *file_name, int red_type);
int		redirection_inp(char *file_name, int red_type);
char	*name_red(t_list *cmnd_list);
void	heredoc(char *file_name);
int		type_red(t_list *cmnd);




t_cmnd	*initializ_cmnd(t_list *cmnd_list, t_envi *env);
char	**init_env_table(t_envi *envi, int size);
char	**init_cmnd_table(t_list *cmnd, int size);




int	nbr_mots	(char *s, char c);

#endif	//MINISHELL
