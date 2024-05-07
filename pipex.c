/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:12:58 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/07 10:03:06 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*altpath(char **env, char *cmd, int i)
{
	char	**realpath;
	char	*string;

	realpath = ft_split(env[i], ':');
	realpath[0] = ft_substr(realpath[0], 5, ft_strlen(realpath[0]) - 4);
	i = -1;
	while (realpath[++i])
	{
		string = ft_strjoinslesh(realpath[i], cmd);
		if (access(string, X_OK) == 0)
			break ;
		free(string);
	}
	ft_free(realpath);
	return (string);
}

char	*get_path(char **env, char *cmd)
{
	int		i;
	char	*string;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	if (i == '\0')
	{
		string = cmd;
		if (access(string, X_OK) != 0)
		{
			free(string);
			exit(1);
		}
	}
	else
		string = altpath(env, cmd, i);
	return (string);
}

void	child(char **argv, int *pipefd, char **env, t_var var)
{
	int		fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		write(1, "no such file or directory;", 27);
		ft_putstr_fd(argv[1], 1);
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	execute(env, var.cmd_one[0], var);
	exit(1);
}

void	parent(char **argv, int *pipefd, char **env, t_var var)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		write(1, "error", 6);
		exit(1);
	}
	dup2(fd, 1);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	executepar(env, var.cmd_two[0], var);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	t_var	var;

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
	// atexit(leaks);
//  valgrind --leak-check=full --show-leak-kinds=all 
// ./pipex input "grep Hallo" "wc -l" output
// void  leaks(void)
// {
//   system("leaks pipex");
// }