/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvardany <hvardany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:55:59 by hvardany          #+#    #+#             */
/*   Updated: 2022/08/30 20:15:58 by hvardany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	featch2_execv(t_pipext *pipex_all, char **envp)
{
	if (execve(pipex_all->cmd2_path, pipex_all->cmd2, envp) == -1)
	{
		exit(1);
	}
}

void	featch2(t_pipext *pipex_all, char **envp, char *argv3)
{
	pipex_all->cmd2 = ft_split(argv3, ' ');
	if (!pipex_all->path_split || !pipex_all->cmd2)
		return ;
	if (dup2(pipex_all->end[0], 0) < 0)
	{
		write(2, "ERROR:\n", 8);
		exit(0);
	}
	close(pipex_all->end[1]);
	close(pipex_all->end[0]);
	if (dup2(pipex_all->output_file, 1) < 0)
	{
		write(2, "ERROR:\n", 8);
		exit(0);
	}
	close(pipex_all->output_file);
	if (access_if_cmd2(pipex_all, envp) < 0)
	{
		write(2, "ERROR:\n", 8);
		exit(0);
	}
	featch2_execv(pipex_all, envp);
}

void	proces_input(t_pipext *pipex_all, char **argv, char **envp)
{
	if (pipe(pipex_all->end) < 0)
	{
		write(2, "ERROR:pipe does not opened\n", 28);
		exit(0);
	}
	pipex_all->pwd = pat_if_evm(envp, "PWD=", 4);
	pipex_all->path = pat_if_evm(envp, "PATH=", 5);
	pipex_all->path_split = ft_split(pipex_all->path, ':');
	pipex_all->forks = fork();
	if (pipex_all->forks == 0)
	{
		featch1(pipex_all, envp, argv[2], pipex_all->input_file);
		exit(0);
	}
	else if (pipex_all->forks < 0)
	{
		write(2, "ERROR:\n", 7);
		return ;
	}
}

void	free_all(t_pipext *pipex_all)
{
	int	i;

	i = -1;
	if (pipex_all->cmd1_path)
		free(pipex_all->cmd1_path);
	if (pipex_all->cmd2_path)
		free(pipex_all->cmd2_path);
	if (pipex_all->path_split)
	{
		while (pipex_all->path_split[++i])
			free(pipex_all->path_split[i]);
	}
	if (pipex_all->cmd1)
	{
		i = -1;
		while (pipex_all->cmd1[++i])
			free(pipex_all->cmd1[i]);
	}
	if (pipex_all->cmd2)
	{
		i = -1;
		while (pipex_all->cmd2[++i])
			free(pipex_all->cmd2[i]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipext	pipex_all;

	if (argc == 5)
	{
		if (file_open_close(&pipex_all, argv) == -1)
			return (-1);
		proces_input(&pipex_all, argv, envp);
		if (pipex_all.forks < 0)
			return (0);
		pipex_all.forks1 = fork();
		if (pipex_all.forks1 == 0)
		{
			featch2(&pipex_all, envp, argv[3]);
			exit(1);
		}
		wait(0);
		free_all(&pipex_all);
		return (0);
	}
	write(2, "ERROR:\n", 7);
	return (0);
}
