/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/27 13:48:59 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "structs.h"
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

void		echo(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
void		cd(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
int			cd_check(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
void		pwd(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp);
void		env(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp);
char		*search_env(char ***envp, char *cmd);
char		**env_add(char ***envp, char *cmd);
char		**env_remove(char ***envp, char *cmd);
void		export(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
void		export_value(char **cmd, char ***envp);
void		unset(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
void		exit_builtin_main(t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp, int status);
void		execute(t_redirect *current_cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
int			execute_builtin_main(t_redirect *current_cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
int			execute_builtin(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
void		execute_command(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
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
t_redirect	*parse_cmd(char *line, char ***envp);
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
char		*process_cmd(t_cmd_parser *parser, t_redirect **head);
char		*process_redirection_out(t_cmd_parser *parser, t_redirect **redir);
char		*process_redirection_in(t_cmd_parser *parser, t_redirect **redir);
char		*process_redirection_in_heredoc(t_cmd_parser *parser,
				t_redirect **redir);
char		*process_regular_cmd(t_cmd_parser *parser, t_redirect **redir);
int			handle_input_redirection(t_redirect *redir);
int			handle_output_redirection(t_redirect *redir);
void		reset(t_redirect *redirect, t_pipe *pipe, char *line);
void		reset_redirections(t_redirect *head);
void		reset_pipes(t_pipe *head);
t_redirect	*parse_pipeline(char *line, char ***envp);
void		execute_pipeline(t_redirect *cmds_head, t_pipe *pipes_head,
				char ***envp);
void		handle_child(t_redirect **head, t_pipe *pipes_head,
				int index, char ***envp);
void		handle_parent(t_redirect *head, t_pipe *pipes_head, int index);
char		*trim_spaces(char *str);
void		free_strings(char *s1, char *s2);
char		**split_pipes(const char *str, char c);
char		*insert_space(char *line);
char		*remove_char(char *str, char *clean, char c);
void		init_quote_state(t_in_quote *state);
void		swap_quote_state(t_in_quote *state, char q);
t_redirect	*init_redirect(void);
char		*preprocess_line(char *line);
t_redirect	*parse_redirections(char *line, char ***envp);
size_t		cmd_size(const char *str, int n, char c);
void		builtin_exit(char **cmd, t_redirect *cmds_head,
				t_pipe *pipes_head, char ***envp);
void		check_digits(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head);
t_pipe		*add_pipe(t_pipe *head);
t_pipe		*init_pipe(void);
t_pipe		*get_pipe(t_pipe *head, int n);
t_pipe		*initialize_pipeline(int n);
int			count_commands(t_redirect *cmds_head);
int			validate_pipes(char *line);
int			validate_redirections(char *line);
int			validate_red_2(char *line);
int			validate_pipes_2(char *line);
int			validate_pipes_3(char *line);
int			only_spaces(char *line);
char		*ignore_in_quotes(char *line);
char		*read_line(char **envp);
int			check_input(char *line);
char		**env_sort(char ***envp);

#endif