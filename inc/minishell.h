/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 22:43:47 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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
	char	*command;
}			t_redirect;

typedef struct s_pipe
{
	int		pipe[2];
	int		infile;
	int		outfile;
}			t_pipe;

typedef struct s_cmd_parser
{
	char	**cmd;
	char	*start;
	char	*end;
	int		i;
	char	***envp;
}			t_cmd_parser;

typedef struct s_heredoc
{
	int		fd;
	char	*str;
	int		start;
	int		end;
	char	***envp;
}			t_heredoc;

typedef struct s_variables
{
	char	*start;
	char	*end;
	char	*name;
	char	*value;
}			t_variables;

void		echo(char **cmd);
void		cd(char **cmd, char ***envp);
void		pwd(void);
void		env(char ***envp);
char		*search_env(char ***envp, char *cmd);
char		**env_add(char ***envp, char *cmd);
char		**env_remove(char ***envp, char *cmd);
void		export(char **cmd, char ***envp);
void		execute(char **cmd, char ***envp);
int			execute_builtin_main(char **cmd, char ***envp);
void		execute_builtin(char **cmd, char ***envp);
void		execute_command(char **cmd, char ***envp);
int			*exit_status(int *value);
void		handle_exit_status(int *status);
char		*pathfinder(char *cmd, char ***envp);
void		signals(int n);
void		handle_sigint(int sig);
void		handle_sigint2(int sig);
void		handle_sigquit2(int sig);
void		handle_sigquit(int sig);
char		*find_end(char *start);
char		**resize_cmd(char **cmd, int count);
char		*strip_quotes(char *arg);
char		**parse_cmd(char *line, char ***envp);
t_redirect	*get_redirections(void);
int			create_heredoc_file(char *str, char ***envp);
int			find_delimiter(char *line);
char		*assign_variable(char *cmd, char ***envp, int flag);
int			check_quotes(char *cmd);
int			check_apostrophe(char *cmd);
char		*find_var_end(char *var_start);
char		*create_new_cmd(t_variables *var, char *cmd);
void		write_all_to_file(t_heredoc *params);
void		write_to_file(t_heredoc *params);
char		*skip_spaces(char *start);
char		*process_cmd(t_cmd_parser *parser);
char		*process_redirection_out(t_cmd_parser *parser);
char		*process_redirection_in_heredoc(t_cmd_parser *parser);
char		*process_redirection_in(t_cmd_parser *parser);
char		*process_regular_cmd(t_cmd_parser *parser);
void		handle_input_redirection(void);
void		handle_output_redirection(void);
void		reset_structs(void);
void		reset_redirections(void);
void		reset_pipe(void);
char		***parse_pipeline(char *line, char ***envp);
void		execute_pipeline(char ***cmds, char ***envp);
t_pipe		*get_pipe(void);
void		handle_child(char ***cmds, int index, char ***envp);
void		handle_parent(int index);
char		*trim_spaces(char *str);
void		free_strings(char *s1, char *s2);
char		**split_pipes(const char *str, char c);

#endif