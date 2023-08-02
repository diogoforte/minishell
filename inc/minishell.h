/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/02 04:21:29 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_redirect
{
	int		in_redir;
	int		out_redir;
	int		heredoc;
	char	*in_file;
	char	*out_file;
}			t_redirect;

int			parsing(char *line, char ***envp);
int			execute(char **cmd, char ***envp);
char		*pathfinder(char *cmd, char ***envp);
void		free_list(char **list);
char		*triple_strjoin(char *s1, char *s2, char *s3);
int			builtins(char **cmd, char ***envp);
void		echo(char **cmd);
void		cd(char **cmd);
void		pwd(void);
void		env(char ***envp);
char		**splitonce(char *str, char delim);
void		handle_sigint(int sig);
char		*find_end(char *start);
char		**resize_cmd(char **cmd, int count);
void		strip_quotes(char *arg);
char		**parse_cmd(char *line);
char		*get_env(char ***envp, char *cmd);
char		*assign_variable(char *cmd);
void		export(char **cmd, char ***envp);
char		**dup_envp(char **envp);
char		**env_add(char ***envp, char *cmd);
char		**env_remove(char ***envp, char *cmd);
t_redirect	*get_redirections(void);
int			create_heredoc_file(char *str);
int			find_delimiter(char *line);

#endif