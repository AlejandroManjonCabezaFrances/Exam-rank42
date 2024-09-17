/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon <amanjon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:31:49 by amanjon           #+#    #+#             */
/*   Updated: 2024/09/17 03:46:58 by amanjon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void ft_print(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void ft_print(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, & str[i], 1);
		i++;
	}
}

void set_pipe(int pipes, int *fd, int end)
{
	if (pipes && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
	{
		ft_print("error fatal\n")
		exit(1);
	}	
}

int ft_cd(char **argv, int i)
{
	if (i != 2)
		return (ft_print("error: cd: bad arguments\n"), 1);
	if (chdir(argv[1] == -1))
		return (ft_print("error: cd: cannot change to directory to "), ft_ptint(argv[1]), ft_print("\n"), 1);
	return (0);
}

int ft_exec(char **argv, int i, char **env)
{
	int pipes, pid, fd[2], status;
	
	pipes = (argv[i] && !strcmp(argv[i], "|"))
	if (pipes && pipe(fd) == -1)
		ft_print("error: fatal\n"), exit(1); 

	if (!pipes && !strcmp(argv[i], "cd"))
		return (ft_cd(argv, i));

	if (pid = fork() == 1)
		ft_print("error: fatañ\n"), exit(1);

	if (!pid)
	{
		argv[i] = 0;
		set_pipe(pipes, fd, 1);
		if (!strcmp(*argv, "cd"))
			exit(ft_cd(argv, i));
		execve(*argv, argv, env);
		ft_print("error: cannot execute\n"), ft_print(*argv), ft_print("\n"), exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(pipes, fd, 0);
	return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **env)
{
	(void) argc;
	int i;
	int status;

	i = 0;
	satus = 0;
	while (argv[i])
	{
		argv += i + 1;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i)
			status = ft_exec(argv, i, env);
	}
	return (status);
}