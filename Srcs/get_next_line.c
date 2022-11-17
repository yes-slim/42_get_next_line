/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:41:12 by yes-slim          #+#    #+#             */
/*   Updated: 2022/11/17 23:04:07 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE == INT_MAX)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	ret = ft_fill(str);
	str = ft_remainder(str);
	return (ret);
}

char	*ft_read(int fd, char *str)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(str, '\n') && i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free (str);
			free (buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	return (str);
}

char	*ft_fill(char *str)
{
	char	*ret;
	int		i;
	int		z;

	i = 0;
	z = 0;
	if (!ft_strlen(str))
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		ret = malloc(sizeof(char) * (i + 2));
	else
		ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	while (z <= i && str[z])
	{
		ret[z] = str[z];
		z++;
	}
	ret[z] = '\0';
	return (ret);
}

char	*ft_remainder(char *str)
{
	char	*remainder;
	int		i;
	int		z;

	i = 0;
	z = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	remainder = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!remainder)
	{
		free (str);
		return (NULL);
	}
	while (str[i])
		remainder[z++] = str[i++];
	remainder[z] = '\0';
	free (str);
	return (remainder);
}
