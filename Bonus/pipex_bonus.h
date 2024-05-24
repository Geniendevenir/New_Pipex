/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:07:09 by adebert           #+#    #+#             */
/*   Updated: 2024/05/24 16:30:06 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"

# define ERR_INPUT "Error: Invalid number of arguments.\n"
# define ERR_INFILE "Error: Opening Infile Failed\n"
# define ERR_OUTFILE "Error: Opening Outfile Failed\n"
# define ERR_PIPE "Error: Pipe Initialisation Failed\n"
# define ERR_FORK "Error: Fork Initialisation Failed\n"
# define ERR_CMD "Error: Command not found\n"
# define ERR_EXEC "Error: Command Execve Failed\n"

typedef struct s_struct
{
	int	fd[2];
	int	infile;
	int	outfile;
	int	nbr_cmd;
}	t_struct;

int		check_path(char *envp);
char	*try_path(char *envp, char *cmd);
char	*get_path(char *cmd, char **envp);
void	free_tab(char **cmd);
void	exec(char *argv, char **envp);
void	first_child(t_struct *file, char **argv, char **envp);
void	second_child(t_struct *file, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);
void	close_pipe(t_struct *file, int i);
void	msg(char *err);
void	file_opening(t_struct *file, char **argv);

#endif