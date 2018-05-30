/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:06:48 by ksonu             #+#    #+#             */
/*   Updated: 2018/04/09 21:47:44 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		print_line(const int fd, char **str, char **line)
{
	char	*ptr;
	char	*tmp;

	if ((ptr = ft_strchr(str[fd], '\n')))
	{
		*ptr = '\0';
		*line = ft_strdup(str[fd]);
		tmp = ft_strdup(ptr + 1);
		ft_strdel(&str[fd]);
		str[fd] = tmp;
		return (1);
	}
	else if (*str[fd])
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static char		*str[1023];
	char			*tmp;
	int				r;

	if (fd < 0 || BUFF_SIZE < 1 || line == NULL)
		return (-1);
	while ((r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		tmp = ft_strjoin(str[fd], buf);
		ft_strdel(&str[fd]);
		str[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (r < 0)
		return (-1);
	else if (r == 0 && str[fd] == NULL)
		return (0);
	return (print_line(fd, str, line));
}
