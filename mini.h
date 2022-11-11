/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:44:38 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 23:06:47 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H

# define MINI_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SUCCESS 0
# define FAILDE -1
# define DQUOTE 34
# define SQUOTE 39
# define WORD 10
# define PIPE 11
# define R_INP 15
# define R_OUT 16
# define DR_INP 17
# define DR_OUT 18

int	g_x;

//_____________________ -Env-Fcts- _____________________//

typedef struct t_envi
{
	struct t_envi	*next;
	char			*env_x;
	char			*var_name;
	char			*var_value;
}				t_envi;

void	free_env(t_envi **env);
void	add_back(t_envi **envi, t_envi *new_node);
t_envi	*new_node(char *env_x);
t_envi	*init_envi(char **env);
void	add_place(t_envi **envi, t_envi *new_node, int i);
int		size_envi(t_envi *env);
void	delete_node_env(t_envi **env, int i);
char	*value_var(char *env);
char	*name_var(char *env);
void	add_front(t_envi **envi, t_envi *new_node);
int		change_var_value(t_envi *env, char *name, char *value);
t_envi	*find_var(t_envi *env, char *name);

//-------------------------------------------------------//

typedef struct t_global
{
	struct t_envi	*env;
	struct t_list	*cmnd_list;
	char			*cmnd;
	int				status;
	int				p_in;
	int				p_out;
	int				fd[2];
	int				lastfd;
	int				pid;

}	t_global;

typedef struct t_list
{
	struct t_list	*next;
	char			*str;
	int				type;
}			t_list;

typedef struct t_cmnd
{
	char	**cmnd;
	char	**env;
}	t_cmnd;

//				LIBFT TOOLS				//
int		ft_strlen(char *str);
int		ft_putstr_fd(int fd, char *str);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
char	*ft_strlcat(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int i);
char	*ft_itoa(int nbr);

//					PARSING				//
void	init_glb(t_global *glb, int *n_cmnd);
t_list	*init_list(t_global *glb, t_list *head, char *str, int key);
char	*change_str(t_global *glb, char *str);
char	*remove_debut(char *s, int i);
int		check_type(char *str, int key);
int		is_word(char *str);
int		check_syntax_utils(t_list **list, t_list *cmnd, int *prev);
int		check_syntax(t_list **list);
int		init_and_check(t_global *glb, char *line);
void	add_to_next_quote(t_global *glb, char *str, char *ret, int **tab);
void	add_var(t_global *glb, char *str, char *ret, int **tab);
char	*nume_var(char *str, int *id);
int		check_quotes(char *str);
int		add_back_list(t_list **head, t_list *new_node);
t_list	*new_list(char *str, int key, int quote);
void	print_error(char *cmnd, int i);
int		next_q(char *s, int i, char c);
int		is_file(char *str);
int		is_special(char c, int key);
void	free_list(t_list **root, t_list *node);

//					EXECUTION			//
char	**find_paths(t_envi **env);
int		other_fct(t_cmnd *cmnd, t_envi **env);
int		exec_cmnd(t_list *cmnd_list, t_global *glb);
int		check_pipe(char *str, int key);
int		exec_onecmnd(t_global *glb, t_list *current, char **cmnd);
int		pipe_utils(t_global *glb, t_list *current, char **cmnd, int n_cmnd);
int		builtin_fct(t_cmnd *cmnd, t_global *glb);
int		exec_builting(t_list *cmnd_list, t_global *glb);
t_envi	*find_var(t_envi *env, char *name);
void	init_fds(t_global *glb, int *i);
void	exec_child(t_global *glb, t_list *current);

//					BUILT-IN			//
int		ft_pwd(t_cmnd *cmnd, t_envi **env);
int		ft_exit(t_global *glb);
int		ft_cd(t_cmnd *cmnd, t_envi **env);
int		ft_echo(t_cmnd *cmnd, t_envi **env);
int		ft_env(t_cmnd *cmnd, t_envi **env);
int		ft_export(t_cmnd *cmnd, t_envi **env);
int		ft_unset(t_cmnd *cmnd, t_envi **env);

void	ft_free(char **str);
void	free_tcmnd(t_cmnd *cmnd);

//___________redirection_fcts______________
int		redirection_out(char *file_name, int red_type);
int		redirection_inp(char *file_name, int red_type);
char	*name_red(t_list *cmnd_list);
void	heredoc(char *file_name);
int		type_red(t_list *cmnd);
int		check_quotes(char *str);
t_cmnd	*initializ_cmnd(t_list *cmnd_list, t_envi *env);
char	**init_env_table(t_envi *envi, int size);
char	**init_cmnd_table(t_list *cmnd, int size);
void	handler_sig(t_global *glb, int i);
void	handler(int sig);
char	**split_pro_max(char *str);
int		check_red_name(char *str);
int		next_q(char *s, int i, char c);
int		nbr_mots(char *s, char c, int i);

#endif	//MINI_H
