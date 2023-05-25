/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   featch1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvardany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:30:10 by hvardany          #+#    #+#             */
/*   Updated: 2022/08/30 20:33:46 by hvardany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	featch1_execv(t_pipext *pipex_all, char **envp)
{
	if (execve(pipex_all->cmd1_path, pipex_all->cmd1, envp) == -1)
	{
		exit(1);
	}
}

void	featch1(t_pipext *pipex_all, char **envp, char *argv2, int fd)
{
	pipex_all->cmd1 = ft_split(argv2, ' ');
	if (!pipex_all->path_split || !pipex_all->cmd1)
		return ;
	if (dup2(fd, 0) < 0)
	{
		write(2, "ERROR:dup2\n", 11);
		exit(1);
	}
	if (dup2(pipex_all->end[1], 1) < 0)
	{
		write(2, "ERROR:dup2\n", 12);
		exit(1);
	}
	close(pipex_all->end[1]);
	close(pipex_all->end[0]);
	close(fd);
	if (access_if_cmd1(pipex_all, envp) < 0)
	{
		write(2, "ERROR:\n", 7);
		exit(1);
	}
	featch1_execv(pipex_all, envp);
	exit(1);
}

int	file_open_close(t_pipext *pipex_all, char **argv)
{
	pipex_all->input_file = open(argv[1], O_RDONLY);
	pipex_all->output_file = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex_all->input_file < 0 || pipex_all->output_file < 0)
	{
		write(2, "ERROR:File does not opened\n", 28);
		return (0);
	}
	return (1);
}
