/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 21:07:21 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_redirect	t_redirect;

struct						s_redirect
{
	char					**cmd;
	int						cmd_count;
	int						in_redir;
	int						out_redir;
	int						heredoc;
	char					*in_file;
	char					*out_file;
	t_redirect				*next;
};

typedef struct s_pipe
{
	int						pipe[2];
	int						infile;
	int						outfile;
}							t_pipe;

typedef struct s_cmd_parser
{
	char					**cmd;
	char					*start;
	char					*end;
	int						i;
	char					***envp;
}							t_cmd_parser;

typedef struct s_heredoc
{
	int						fd;
	char					*str;
	int						start;
	int						end;
	char					***envp;
}							t_heredoc;

typedef struct s_variables
{
	char					*start;
	char					*end;
	char					*name;
	char					*value;
}							t_variables;

typedef struct s_in_quote
{
	int						doub;
	int						sing;
	int						inside;
}							t_in_quote;

void						echo(char **cmd);
void						cd(char **cmd, char ***envp);
void						pwd(void);
void						env(char ***envp);
char						*search_env(char ***envp, char *cmd);
char						**env_add(char ***envp, char *cmd);
char						**env_remove(char ***envp, char *cmd);
void						export(char **cmd, char ***envp);
void						execute(t_redirect *current_cmd, char ***envp);
int							execute_builtin_main(char **cmd, char ***envp);
void						execute_builtin(char **cmd, char ***envp);
void						execute_command(char **cmd, char ***envp);
int							*exit_status(int *value);
void						handle_exit_status(int *status);
char						*pathfinder(char *cmd, char ***envp);
void						signals(int n);
void						handle_sigint(int sig);
void						handle_sigint2(int sig);
void						handle_sigquit2(int sig);
void						handle_sigquit(int sig);
char						*find_end(char *start);
char						**resize_cmd(char **cmd, int count);
char						*strip_quotes(char *arg);
t_redirect					*parse_cmd(char *line, char ***envp);
int							create_heredoc_file(char *str, char ***envp);
int							find_delimiter(char *line);
char						*assign_variable(char *cmd, char ***envp, int flag);
int							check_quotes(char *cmd);
int							check_apostrophe(char *cmd);
char						*find_var_end(char *var_start);
char						*create_new_cmd(t_variables *var, char *cmd);
void						write_all_to_file(t_heredoc *params);
void						write_to_file(t_heredoc *params);
char						*skip_spaces(char *start);
char						*process_cmd(t_cmd_parser *parser,
								t_redirect **head);
char						*process_redirection_out(t_cmd_parser *parser,
								t_redirect **redir);
char						*process_redirection_in(t_cmd_parser *parser,
								t_redirect **redir);
char						*process_redirection_in_heredoc(
								t_cmd_parser *parser, t_redirect **redir);
char						*process_regular_cmd(t_cmd_parser *parser,
								t_redirect **redir);
void						handle_input_redirection(t_redirect *redir);
void						handle_output_redirection(t_redirect *redir);
void						reset_structs(t_redirect *head);
void						reset_redirections(t_redirect *head);
void						reset_pipe(void);
t_redirect					*parse_pipeline(char *line, char ***envp);
void						execute_pipeline(t_redirect *cmds_head,
								char ***envp);
t_pipe						*get_pipe(void);
void						handle_child(t_redirect *head, int index,
								char ***envp);
void						handle_parent(t_redirect *head, int index);
char						*trim_spaces(char *str);
void						free_strings(char *s1, char *s2);
char						**split_pipes(const char *str, char c);
char						*insert_space(char *line);
char						*remove_char(char *str, char c);
void						init_quote_state(t_in_quote *state);
void						swap_quote_state(t_in_quote *state, char q);
t_redirect					*init_redirect(void);

#endif