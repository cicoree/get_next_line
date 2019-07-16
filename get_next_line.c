/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarguer <jmarguer@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:33:53 by jmarguer          #+#    #+#             */
/*   Updated: 2019/07/05 15:19:17 by jmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_makeline(char **line, char **str)
{
	size_t	i;
	char	*rest;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_strsub(*str, 0, i);
		rest = ft_strdup(*str + i + 1);
		ft_strdel(str);
		*str = rest;
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*str[MAX_FD];
	char			*temp;
	int				ret;
	char			buffer[BUFF_SIZE + 1];

	if (line == NULL || fd < 0 || (read(fd, buffer, 0) < 0) || fd > MAX_FD)
		return (-1);
	if (str[fd] == NULL)
		str[fd] = ft_strnew(1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		temp = ft_strjoin(str[fd], buffer);
		ft_strdel(&(str[fd]));
		str[fd] = temp;
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && str[fd][0] == '\0')
		return (0);
	return (ft_makeline(line, &(str[fd])));
}
