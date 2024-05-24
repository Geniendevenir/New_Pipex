/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:07:02 by adebert           #+#    #+#             */
/*   Updated: 2024/05/24 16:30:33 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	fork_init(t_struct *file, char **argv, char **envp)
{
	int	curr_cmd;
	int	pid;

	curr_cmd = 0;
	while (curr_cmd > file->nbr_cmd && pid[curr_cmd])
	{
		pid = fork();
		if (pid == -1)
			msg(ERR_FORK);
		if (pid == 0)
		{
			if (curr_cmd == 0)
				first_child(file, argv, envp);
			if (curr_cmd == file->nbr_cmd)
				last_child(file, argv, envp);
			else
				middle_childs(file, argv, envp);
		}
		curr_cmd++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	file;

	if (argc < 5)
		msg(ERR_INPUT);
	file_opening(&file, argv);
	if (pipe(file.fd) == -1)
		msg(ERR_PIPE);
	file.nbr_cmd = argc - 3;
	fork_init(&file, argv, envp);

	/*
	1- determiner le nombre de nbr_cmd = argc -3;
	2- int pid[nbr_cmd]; malloc ?
	while (curr_cmd > nbr_comm && pid[curr_cmd])
	{
		pid[curr_cmd] = fork();
		if (pid == -1)
			msg(ERR_FORK);
		if (pid == 0)
		{
			if (curr_cmd == 0)
				first_child();
			if (curr_cmd == nbr_comm)
				last_child();
			else
				middle_childs();
		}
		curr_cmd++;
	}
	3- First child:
		dup2(file->fd[1], STDOUT_FILENO);
		dup2(file->infile, STDIN_FILENO);
		exec;
	4- Middle childs:
		dup2(file->fd[1], STDIN_FILENO);
		dup2(file->fd[0], STDOUT_FILENO);
		exec;
	5- Last child:
		dup2(file->fd[0], STDIN_FILENO);
		dup2(file->outfile, STDOUT_FILENO);
		exec;
	6- close_pipe(&file, 0);
	7- int i = 0;
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	8- close_pipe(&file, 1);
	*/
}

	/* pid1 = fork();
	if (pid1 == -1)
		msg(ERR_FORK);
	if (pid1 == 0)
		first_child(&file, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		msg(ERR_FORK);
	if (pid2 == 0)
		second_child(&file, argv, envp); */