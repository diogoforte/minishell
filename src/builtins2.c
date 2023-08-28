/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:28:39 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/28 17:48:41 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	char	*pwd;

	ft_freematrix(*envp);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(2, "Error: %s\n", strerror(errno));
		reset(cmds_head, pipes_head, NULL);
		exit(1);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

void	env(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	int		i;
	char	*ptr;

	i = 0;
	while ((*envp)[i])
	{
		ptr = ft_strchr((*envp)[i], '=');
		if (ptr)
			printf("%s\n", (*envp)[i]);
		i++;
	}
	ft_freematrix(*envp);
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

void	export(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (!*cmd)
	{
		while ((*envp)[i])
			printf("declare -x %s\n", (*envp)[i++]);
		exit_status(&status);
	}
	else
		export_value(cmd, envp);
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

void	unset(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!*cmd)
	{
		exit_status(&status);
		return ;
	}
	while (cmd[i])
	{
		*envp = env_remove(envp, cmd[i]);
		i++;
	}
	exit_status(&status);
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}
