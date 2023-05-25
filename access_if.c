/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_if.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvardany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:19:24 by hvardany          #+#    #+#             */
/*   Updated: 2022/08/30 20:29:58 by hvardany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	j;

	j = 0;
	while (j < n)
	{
		if (s1[j] > s2[j])
			return ((unsigned char)s1[j] - (unsigned char)s2[j]);
		else if (s1[j] < s2[j])
			return ((unsigned char)s1[j] - (unsigned char)s2[j]);
		j++;
	}
	return (0);
}

char	*pat_if_evm(char **envp, char *s, int x)
{
	int	i;

	i = 0;
	if (!envp || !(*envp))
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], s, x))
			return (&envp[i][x]);
		i++;
	}
	return (NULL);
}

int	access_if_cmd1(t_pipext *pipex_all, char **envp)
{
	int		i;
	char	*pat;
	char	*x;

	i = 0;
	if (access(pipex_all->cmd1[0], F_OK & X_OK) == 0)
	{
		execve(pipex_all->cmd1[0], pipex_all->cmd1, envp);
		write(2, "ERROR:\n", 9);
		exit(1);
	}
	while (pipex_all->path_split[i])
	{
		x = ft_strjoin(pipex_all->path_split[i], "/");
		pat = ft_strjoin(x, pipex_all->cmd1[0]);
		free(x);
		if (access(pat, F_OK & X_OK) == 0)
		{
			pipex_all->cmd1_path = pat;
			return (i);
		}
		free(pat);
		i++;
	}
	return (-1);
}

int	access_if_cmd2(t_pipext *pipex_all, char **envp)
{
	int		i;
	char	*pat;
	char	*x;

	if (access(pipex_all->cmd2[0], F_OK & X_OK) == 0)
	{
		execve(pipex_all->cmd2[0], pipex_all->cmd2, envp);
		exit(1);
	}
	i = 0;
	while (pipex_all->path_split[i])
	{
		x = ft_strjoin(pipex_all->path_split[i], "/");
		pat = ft_strjoin(x, pipex_all->cmd2[0]);
		free(x);
		if (access(pat, F_OK & X_OK) == 0)
		{
			pipex_all->cmd2_path = pat;
			return (i);
		}
		free(pat);
		i++;
	}
	return (-1);
}
