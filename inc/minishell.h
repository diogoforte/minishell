/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 10:23:30 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

extern char	**environ;

int		parsing(char *line, char **envp);
int		execute(char **cmd, char **envp);
char	*pathfinder(char *cmd, char **envp);
void	free_list(char **list);
char	*triple_strjoin(char *s1, char *s2, char *s3);
int		builtins(char **cmd, char **envp);
void	echo(char **cmd);
void	cd(char **cmd);
void	pwd(void);
void	export(char **cmd);
void	env(char **envp);
char	**splitonce(char *str, char delim);
void	handle_sigint(int sig);

#endif