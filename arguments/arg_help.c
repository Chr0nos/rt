/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 10:45:29 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/14 18:52:23 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include <fcntl.h>
#include <unistd.h>

static void		read_txt_help(char *src)
{
	int		ret_fd;
	char	*line;

	if ((ret_fd = open(src, O_RDONLY)) == -1)
	{
		ft_putstr("Error, arg_help.txt or arg_help_key.txt not found\n");
		exit(1);
	}
	while ((ft_get_next_line(ret_fd, &line)) == 1)
	{
		ft_putendl(ft_strreplace(line, '@', '\033'));
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(ret_fd);
}

int				arg_display_help(t_rt *rt, int ac, char **av)
{
	(void)av;
	(void)ac;
	(void)rt;
	read_txt_help("arguments/arg_help.txt");
	read_txt_help("arguments/arg_help_key.txt");
	return (0);
}
