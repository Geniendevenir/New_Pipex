/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:07:02 by adebert           #+#    #+#             */
/*   Updated: 2024/05/24 15:55:45 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_struct *file, char **argv, char **envp)
{
	dup2(file->fd[1], STDOUT_FILENO);
	dup2(file->infile, STDIN_FILENO);
	close(file->fd[0]);
	exec(argv[2], envp);
}

void	second_child(t_struct *file, char **argv, char **envp)
{
	dup2(file->fd[0], STDIN_FILENO);
	dup2(file->outfile, STDOUT_FILENO);
	close(file->fd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	file;
	int			pid1;
	int			pid2;

	if (argc != 5)
		msg(ERR_INPUT);
	file_opening(&file, argv);
	if (pipe(file.fd) == -1)
		msg(ERR_PIPE); // fermer les fd
	pid1 = fork();
	if (pid1 == -1)
		msg(ERR_FORK); // fermer les fd et files
	if (pid1 == 0)
		first_child(&file, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		msg(ERR_FORK); // fermer les fd et files
	if (pid2 == 0)
		second_child(&file, argv, envp);
	close_pipe(&file, 0);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close_pipe(&file, 1);
}
