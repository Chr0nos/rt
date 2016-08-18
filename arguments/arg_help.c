/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 10:45:29 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/18 12:30:14 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include <fcntl.h>
#include <unistd.h>

static char *read_txt_help(char **str, char *src)
{
	int     ret;
	int     fd;
	char    *line;
	char	*tmp;
	char	*tmp2;

	ret = 1;
	if ((fd = open(src, O_RDONLY)) == -1)
	{
		ft_putstr("Error, arg_help.txt, not open\n");
		exit (1);
	}
	while ((ret = ft_get_next_line(fd, &line)) == 1)
	{
		tmp = ft_strjoin(line, "\n");
		free(line);
		if (!(*str))
			*str = ft_strdup(tmp);
		else
		{
			tmp2 = *str;
			*str = ft_strjoin(*str, tmp);
			free(tmp2);
		}
	}
	close(fd);
	return (*str);
}

int					arg_display_help(t_rt *rt, int ac, char **av)
{
	static char *txt_help = NULL;
	static char *txt_key = NULL;

	(void)av;
	(void)ac;
	(void)rt;
	if (!txt_help)
		txt_help = read_txt_help(&txt_help, "arguments/arg_help.txt");
	if (!txt_key)
		txt_key = read_txt_help(&txt_key, "arguments/arg_help_key.txt");
	ft_putstr("\033[01;032m");
	ft_putstr(txt_help);
	ft_putstr("\n\033[01;033m");
	ft_putstr(txt_key);
	ft_putstr("\033[;m");
	return (0);
}
