/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likiffel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:43:46 by likiffel          #+#    #+#             */
/*   Updated: 2024/03/22 18:08:36 by likiffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = start;
	j = 0;
	if (s == NULL || start >= ft_strlen(s))
	{
		result = (char *)malloc(sizeof(char));
		if (result == NULL)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	if (len > ft_strlen(s))
		result = malloc((ft_strlen(s) + 1) * sizeof(char));
	else
		result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s[i] != '\0' && j < len)
		result[j++] = s[i++];
	result[j] = '\0';
	return (result);
}

char	*fill_line(int fd, char *left, char *buf)
{
	ssize_t	read_value;
	char	*temp;

	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(left);
			return (NULL);
		}
		else if (read_value == 0)
			break ;
		buf[read_value] = 0;
		if (!left)
			left = ft_strdup("");
		temp = left;
		left = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (left);
}

char	*set(char *line_buf)
{
	char	*left;
	ssize_t	i;

	i = 0;
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
		i++;
	if (line_buf[i] == 0 || line_buf[1] == 0)
		return (NULL);
	left = ft_substr(line_buf, i + 1, ft_strlen(line_buf) - i);
	if (*left == 0)
	{
		free(left);
		left = NULL;
	}
	line_buf[i + 1] = 0;
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*line;
	char		*buf;

	buf = malloc(((BUFFER_SIZE) + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buf);
		free(left);
		left = NULL;
		buf = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = fill_line(fd, left, buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	left = set(line);
	return (line);
}
