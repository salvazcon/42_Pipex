/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:35 by saazcon-          #+#    #+#             */
/*   Updated: 2023/05/23 18:29:35 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd(struct s_var *v, char *cmd, char **envp)
{
	int		i;

	v->exec = ft_split(cmd, ' ');
	if (execve(v->exec[0], v->exec, envp) == -1)
	{
		v->path = ft_split(ft_path(envp), ':');
		if (!v->path)
			ft_error(v, "Error: Path not found:", 1);
		i = -1;
		while (v->path[++i])
		{
			v->bin = ft_strjoin(ft_strjoin(v->path[i], "/"), v->exec[0]);
			if (!access(v->bin, F_OK))
				break ;
			free(v->bin);
		}
		if (!v->bin)
			ft_error(v, "Error: Command not found:", 1);
		if (execve(v->bin, v->exec, envp) == -1)
			ft_error(v, v->bin, 127);
	}
}

void	ft_first_son(struct s_var *v, char *cmd, char **envp)
{
	close(v->fd[1]);
	close(v->pipex[0]);
	dup2(v->fd[0], STDIN_FILENO);
	dup2(v->pipex[1], STDOUT_FILENO);
	close(v->pipex[1]);
	close(v->fd[0]);
	ft_cmd(v, cmd, envp);
}

void	ft_last_son(struct s_var *v, char *cmd, char **envp)
{
	close(v->fd[0]);
	close(v->pipex[1]);
	dup2(v->pipex[0], STDIN_FILENO);
	dup2(v->fd[1], STDOUT_FILENO);
	close(v->pipex[0]);
	close(v->fd[1]);
	ft_cmd(v, cmd, envp);
}

void	ft_pipex(struct s_var *v, char **cmd, char **envp)
{
	int		status;

	if (pipe(v->pipex) == -1)
		ft_error(v, "Error: Pipe Error:", 1);
	v->ps1_id = fork();
	if (v->ps1_id == -1)
		ft_error(v, "Error: Fork Error:", 1);
	else if (v->ps1_id == 0)
		ft_first_son(v, cmd[2], envp);
	else
	{
		v->ps2_id = fork();
		if (v->ps2_id == -1)
			ft_error(v, "Error: Fork Error:", 1);
		else if (v->ps2_id == 0)
			ft_last_son(v, cmd[3], envp);
		else
		{
			close(v->pipex[0]);
			close(v->pipex[1]);
			waitpid(v->ps1_id, &status, 0);
			waitpid(v->ps2_id, &status, 0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct s_var	*v;

	if (argc != 5)
		return (perror("Error: Invalid arguments."), 1);
	v = ft_calloc(sizeof(struct s_var), 1);
	if (!v)
		return (0);
	v->fd[0] = ft_open_file(v, argv[1], O_RDONLY);
	v->fd[1] = ft_open_file(v, argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC);
	ft_pipex(v, argv, envp);
	ft_free_all(v);
	return (0);
}
