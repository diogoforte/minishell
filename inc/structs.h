/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:01:14 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/28 23:04:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redirect	t_redirect;
typedef struct s_pipe		t_pipe;
typedef struct s_head		t_head;

struct						s_redirect
{
	char					**cmd;
	int						cmd_count;
	int						in_redir;
	int						out_redir;
	int						heredoc;
	char					*in_file;
	char					*out_file;
	int						in_fd;
	int						out_fd;
	int						lock;
	t_redirect				*next;
};

struct						s_pipe
{
	int						pipe[2];
	int						infile;
	int						outfile;
	t_pipe					*next;
};

struct						s_head
{
	t_redirect				redirects;
	t_pipe					pipes;
};

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
	char					*delimiter;
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

#endif