/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:12:58 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/06 09:36:29 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env, char *cmd, t_var var)
{
	int		i;
	char	path[8];
	char	**realpath;
	char	*string;

	ft_strcpy(path, "PATH=");
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], path, 7) != NULL)
			break ;
		else
			i++;
	}
	realpath = ft_split(env[i], ':');
	i = -1;
	while (realpath[++i])
	{
		string = ft_strjoinslesh(realpath[i], cmd);
		if (access(string, X_OK) == 0)
			break ;
		free(string);
	}
	ft_free(realpath);
	if (i == '\0')
	{
		ft_putendl_fd("No command", 2);
		exit(0);
	}
	return (string);
}

void	child(char **argv, int *pipefd, char **env, t_var var)
{
	int		fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		exit(0);
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	execute(env, var.cmd_one[0], argv, var);
	exit(0);
}

void	parent(char **argv, int *pipefd, char **env, t_var var)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit(0);
	dup2(fd, 1);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	executepar(env, var.cmd_two[0], argv, var);
	exit(0);
}

// void	leaks(void)
// {
// 	system("leaks pipex");
// }

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	t_var	var;

	// atexit(leaks);
	get_args(argc, argv, &var);
	if (pipe(pipefd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
	{
		child(argv, pipefd, env, var);
	}
	parent(argv, pipefd, env, var);
	return (0);
}

// < test.txt grep a1 | wc -w > test2
// ./pipex test.txt "grep a1" "wc -l" test2