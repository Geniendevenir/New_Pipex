/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:03:38 by adebert           #+#    #+#             */
/*   Updated: 2024/05/24 13:46:01 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_opening(t_struct *file, char **argv)
{
	file->infile = open(argv[1], O_RDONLY);
	if (file->infile == -1)
		msg(ERR_INFILE);
	file->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (file->outfile == -1)
		msg(ERR_OUTFILE);
}

void	close_pipe(t_struct *file, int i)
{
	if (i == 0)
	{
		close(file->fd[0]);
		close(file->fd[1]);
	}
	else if (i == 1)
	{
		close(file->infile);
		close(file->outfile);
	}
}

void	free_tab(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	msg(char *err)
{
	perror(err);
	exit(1);
}
