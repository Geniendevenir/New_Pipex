/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:07:36 by adebert           #+#    #+#             */
/*   Updated: 2024/05/23 18:10:17 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_path(char *envp)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = 0;
	while (path[i])
	{
		if (path[i] != envp[i])
			return (1);
		i++;
	}
	return (0);
}

char	*try_path(char *envp, char *cmd)
{
	char	**all_paths;
	char	*full_cmd;
	char	*curr_path;
	int		i;

	all_paths = ft_split((envp + 5), ':');
	full_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (all_paths[i])
	{
		curr_path = ft_strjoin(all_paths[i], full_cmd);
		if (access(curr_path, F_OK) == 0)
		{
			free(full_cmd);
			free_tab(all_paths);
			return (curr_path);
		}
		free(curr_path);
		i++;
	}
	free(full_cmd);
	free_tab(all_paths);
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*valid_path;

	i = 0;
	while (envp[i])
	{
		if (check_path(envp[i]) == 0)
		{
			valid_path = try_path(envp[i], cmd);
			return (valid_path);
		}
		i++;
	}
	return (NULL);
}

void	exec(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = get_path(cmd[0], envp);
	if (!path)
	{
		free(path);
		free_tab(cmd);
		msg(ERR_CMD);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_tab(cmd);
		msg(ERR_EXEC);
	}
}
