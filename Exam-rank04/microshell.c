/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon <amanjon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:39:18 by amanjon           #+#    #+#             */
/*   Updated: 2024/09/13 13:45:53 by amanjon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 0 				FALSE
// 1, 2, 3, 4, .... TRUE

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1

static void	ft_print(char *str)
{
	while (*str)
		write(2, str++, 1);
}

static int	ft_cd(char **argv, int count)
{
	if (count != 2)
		return (ft_print("error: cd: bad arguments\n"), 1);
	else if (chdir(argv[1]) == -1)
		return (ft_print("error: cd: cannot change directory to "), ft_print(argv[1]), ft_print("\n"), 1);
	return (0);
}

static int	ft_exec(char **argv, char **env, int count)
{
	int	status;
	int	fds[2];
	int	pid;
	int	pipes;

	pipes = (argv[count] && strcmp(argv[count], "|") == 0);
	if (pipes && pipe(fds) == -1)
		return (ft_print("error: fatal\n"), 1);
	pid = fork();
	if (pid == 0)
	{
		argv[count] = 0;
		if (pipes && (dup2(fds[STDOUT], STDOUT) == -1 || close(fds[STDIN]) == -1 || close(fds[STDOUT]) == -1))
			return (ft_print("error: fatal\n"), 1);
		execve(*argv, argv, env);
		return (ft_print("error: cannot execute "), ft_print(*argv), ft_print("\n"), 1);
	}
	waitpid(pid, &status, 0);
	if (pipes && (dup2(fds[STDIN], STDIN) == -1 || close(fds[STDIN]) == -1 || close(fds[STDOUT]) == -1))
		return (ft_print("error: fatal\n"), 1);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	int	status;
	int	count;
	
	status = 0;
	while (*argv && *(argv + 1))
	{
		argv++;
		count = 0;
		while (argv[count] && strcmp(argv[count], "|") && strcmp(argv[count], ";"))
			count++;
		if (strcmp(*argv, "cd") == 0)
			status = ft_cd(argv, count);
		else if (count)
			status = ft_exec(argv, env, count);
		argv += count;
	}
	return (status);
}
//68 line

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void ft_print(char *str)
{
	while (*str)
		write(2, str++, 1);
}

// if
void set_pipe(int pipes, int *fd, int end)
{
	if (pipes && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
	{
		ft_print("error: fatal\n");
		exit(1);
	}
}

// if
// if
int ft_cd(char **argv, int i)
{
	if (i != 2)
		return (ft_print("error: cd: bad arguments\n"), 1);
	if (chdir(argv[1]) == -1)
		return (ft_print("error: cd: cannot change directory to "), ft_print(argv[1]), ft_print("\n"), 1);
	return (0);
}

// if --> 4
int	ft_exec(char **argv, int i, char **env)
{
	int pipes, pid, fd[2], status;

	pipes = argv[i] && !strcmp(argv[i], "|");	// posición i, distinto de null y que sea "|", pipes = 1 (TRUE)
												
	if (!pipes && !strcmp(*argv, "cd"))			// encuentra un cd
		return (ft_cd(argv, i));

	if (pipes && pipe(fd) == -1)				// error al crear el pipe
		ft_print("error: fatal\n"), exit(1);

	if ((pid = fork()) == -1)					// crear proceso hijo
		ft_print("error: fatal\n"), exit(1);
	if (!pid)
	{
		argv[i] = 0;
		set_pipe(pipes, fd, 1);
		if (!strcmp(*argv, "cd"))
			exit(ft_cd(argv, i));
		execve(*argv, argv, env);				// execve(name ejecutable, argv, env); --> si falla, se ejecuta lo de abajo
		ft_print("error: cannot execute "), ft_print(*argv), ft_print("\n"), exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(pipes, fd, 0);
	return WIFEXITED(status) && WEXITSTATUS(status);
}

// while
//       while
//		 if	
int main(int, char **argv, char **env)
{
	int i;
	int status;
	
	i = 0;
	status = 0;
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
// 72 lines
// i != 0 --> se encontró argumento/s validos hasta una |, ; or NULL