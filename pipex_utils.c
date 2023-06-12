/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:55:17 by saazcon-          #+#    #+#             */
/*   Updated: 2023/06/07 00:16:22 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (*s)
		write(fd, &*s, ft_strlen(s));
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (n > i && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char *stash, char *buff)
{
	char	*str;
	int		i;
	int		j;

	if (!stash || !buff)
		return (NULL);
	str = ft_calloc(sizeof(char), ft_strlen(stash) + ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		str[i] = stash[i];
		i++;
	}
	j = 0;
	while (buff[j])
	{
		str[i + j] = buff[j];
		j++;
	}
	return (str);
}
