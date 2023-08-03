/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 14:16:39 by dinunes-         ###   ########.fr       */
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

void		execute(char **cmd, char ***envp);
char		*pathfinder(char *cmd, char ***envp);
void		echo(char **cmd);
void		cd(char **cmd);
void		pwd(void);
void		env(char ***envp);
void		handle_sigint(int sig);
char		*find_end(char *start);
char		**resize_cmd(char **cmd, int count);
void		strip_quotes(char *arg);
char		**parse_cmd(char *line, char ***envp);
char		*get_env(char ***envp, char *cmd);
void		export(char **cmd, char ***envp);
char		**env_add(char ***envp, char *cmd);
char		**env_remove(char ***envp, char *cmd);
t_redirect	*get_redirections(void);
int			create_heredoc_file(char *str, char ***envp);
int			find_delimiter(char *line);
int			*exit_status(int *value);
char		*assign_variable(char *cmd, char ***envp);
int			check_quotes(char *cmd);
int			check_apostrophe(char *cmd);
char		*find_var_end(char *var_start);
char		*create_new_cmd(char *cmd, char *var_start, char *var_end, char *var_name, char *var_value);
int			write_to_file(int fd, char *str, int start, int end, char ***envp);
char		*skip_spaces(char *start);
char		*process_cmd(char *start, char **end, char ***cmd, int *i, char ***envp);
char		*process_redirection_out(char *start, char **end);
char		*process_redirection_in_heredoc(char *start, char **end, char ***envp);
char		*process_redirection_in(char *start, char **end);
char		*process_regular_cmd(char *start, char **end, char ***cmd, int *i, char ***envp);
void		handle_input_redirection(void);
void		handle_output_redirection(void);
char		*execute_command(char **cmd, char ***envp);
void		handle_exit_status(int *status, char ***envp);
void		execute_builtin(char **cmd, char ***envp);
int			execute_builtin_main(char **cmd, char ***envp);
void		reset_redirections(void);

#endif