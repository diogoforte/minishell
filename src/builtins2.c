/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:28:39 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/29 19:41:25 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	char	pwd[PATH_MAX];

	ft_freematrix(*envp);
	getcwd(pwd, PATH_MAX);
	if (!*pwd)
	{
		ft_dprintf(2, "Error: %s\n", strerror(errno));
		reset(cmds_head, pipes_head, NULL);
		exit(1);
	}
	else
	{
		printf("%s\n", pwd);
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
	int		status;
	char	**tmp;
	char	**sorted_envp;
	int		i;
	int		j;

	status = 0;
	i = -1;
	if (!*cmd)
	{
		sorted_envp = env_sort(*envp);
		while (sorted_envp[++i])
		{
			j = 1;
			tmp = ft_split(sorted_envp[i], '=');
			if (tmp[1])
			{
				if (tmp[2])
				{
					printf("declare -x %s=\"", tmp[0]);
					while(tmp[j] && tmp[j + 1])
					{
						if (j == 1)
							printf("%s", tmp[j++]);
						else	
							printf("=%s", tmp[j++]);
					}
					printf("=%s\"", tmp[j]);
				}
				else
					printf("declare -x %s=\"%s\"", tmp[0], tmp[1]);
				printf("\n");
			}
			else
				printf("declare -x %s\n", sorted_envp[i]);
			ft_freematrix(tmp);
		}
		ft_freematrix(sorted_envp);
		exit_status(&status);
	}
	else
		export_value(cmd, envp);
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

int	check_unset(char *var)
{
	int	status;

	status = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		ft_dprintf(2, "unset: `%s': not a valid identifier\n", var);
		status = 1;
		exit_status(&status);
		return (0);
	}
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			ft_dprintf(2, "unset: `%s': not a valid identifier\n", var);
			status = 1;
			exit_status(&status);
			return (0);
		}
		var++;
	}
	if (*var++ == '=' && var && !*var)
	{
		ft_dprintf(2, "unset: `%s': not a valid identifier\n", var);
		status = 1;
		exit_status(&status);
		return (0);
	}
	return (1);
}

void	unset(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (!*cmd)
	{
		exit_status(&status);
		return ;
	}
	while (cmd[++i])
	{
		if (!check_unset(cmd[i]))
			continue ;
		*envp = env_remove(envp, cmd[i]);
	}
	exit_status(&status);
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

void	exit_builtin_main(t_redirect *cmds_head,
						t_pipe *pipes_head,
						char ***envp,
						int status)
{
	if (pipes_head->next)
	{
		ft_freematrix(*envp);
		reset(cmds_head, pipes_head, NULL);
		exit(status);
	}
}
