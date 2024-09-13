/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon <amanjon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:31:49 by amanjon           #+#    #+#             */
/*   Updated: 2024/09/13 13:48:08 by amanjon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// 0 				FALSE
// 1, 2, 3, 4, .... TRUE
/* int main()
{
	int i;

	i = 0;
	if(i)
		printf("entra en if: condición verdadera");
	else
		printf("entra en el else: condición falsa");
	return (0);
} */

void ft_print(char *str)
{
	while(*str)
		write(2, str++, 1);   // 2: stderr (salida de error estándar)
}

void set_pipe(int pipes, int *fd, int end)
{
	if (pipes, && (dup2(fd[end], end) == -1 || close(fd[0]) == 1 || close(fd[1]) == -1))
	{
		ft_print("error: fatal\n");
		exit(1);
	}
}

int ft_cd(char **argv, int i)
{
	if (i != 2)
		return (ft_print("error: bad arguments\n"), 1);
	if (chdir(argv[1] == -1))
		return (ft_print("error: cd: cannot change directory to "), ft_print(argv[1]), ft_print("\n"), 1);
}	return (0);

int ft_exec(char **argv, int i, char **env)
{
	int pipes, pid, fd[2], status;

	pipes = argv[i] && !strcmp(argv[i], "|");
	
	if (!pipes && !strcmp(*argv, "cd"))
		return (ft_cd(argv, i));

	if (pipes && pipe(fd) == -1)
		ft_print("error: fatal\n"), exit (1);

	if ((pid = fork()) == -1)
		ft_print("error: fatal\n"), exit (1);

	if (!pid)
	{
		argv[0] = 0;		// se pone NULL al final del argumento
		set_pipe(pipes, fd, 1);
		if (!strcmp(*argv, "cd"))
			exit(ft_cd(argv, i));
		execve(*argv, argv, env);
		ft_print("error: cannot execute ");, ft_print(*argv), ft_print("\n"), exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(pipes, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status)); 		// 1 Verifica si el proceso hijo terminó normalmente. // 2 Obtiene el código de salida del proceso hijo, pero solo si											
}

int main()
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