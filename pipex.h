/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:40 by saazcon-          #+#    #+#             */
/*   Updated: 2023/05/23 18:29:40 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//INCLUDES
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h> //errno
# include <sys/wait.h> //wait

struct	s_var{
	char	**exec;
	char	**path;
	char	*bin;
	pid_t	ps1_id;
	pid_t	ps2_id;
	int		pipex[2];
	int		fd[2];
};

int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_open_file(struct s_var *v, char *file, int flags);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *stash, char *buff);
char	*ft_path(char **env);
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);
void	ft_close(struct s_var *v);
void	ft_free_all(struct s_var *v);
void	ft_error(struct s_var *v, char *error, int num);

#endif