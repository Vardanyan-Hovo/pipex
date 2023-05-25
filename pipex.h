/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvardany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:37:26 by hvardany          #+#    #+#             */
/*   Updated: 2022/08/30 20:40:01 by hvardany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct t_pip
{
	pid_t	forks;
	pid_t	forks1;
	int		i;
	int		x;
	char	**envir;
	int		end[2];
	int		fd[2];
	int		input_file;
	int		output_file;
	int		in;
	int		out;
	char	*pwd;
	char	*path;
	char	**path_split;
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
}			t_pipext;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		access_if_cmd2(t_pipext *pipex_all, char **envp);
void	featch1_execv(t_pipext *pipex_all, char **envp);
void	featch1(t_pipext *pipex_all, char **envp, char *argv2, int fd);
int		file_open_close(t_pipext *pipex_all, char **argv);
int		access_if_cmd1(t_pipext *pipex_all, char **envp);
char	*pat_if_evm(char **envp, char *s, int x);

#endif
