/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 10:45:29 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/01 11:17:25 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include <fcntl.h>
#include <unistd.h>

static char		*read_txt_help(char **str, char *src)
{
	int     ret;
	int     fd;
	char    *line;
	char	*tmp;
	char	*tmp2;

	ret = 1;
	if ((fd = open(src, O_RDONLY)) == -1)
	{
		ft_putstr("Error, arg_help.txt or arg_help_key.txt not found\n");
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

static void		search_and_replace(char *texte)
{
	int	i;

	i = -1;
	while (texte[++i])
	{
		if (texte[i] == '@')
			texte[i] = '\033';
	}
}

int				arg_display_help(t_rt *rt, int ac, char **av)
{
	char *txt_help = NULL;
	char *txt_key = NULL;

	(void)av;
	(void)ac;
	(void)rt;
	txt_help = read_txt_help(&txt_help, "arguments/arg_help.txt");
	txt_key = read_txt_help(&txt_key, "arguments/arg_help_key.txt");
	search_and_replace(txt_help);
	search_and_replace(txt_key);
	ft_putstr(txt_help);
	ft_putstr(txt_key);
	ft_putstr("\033[;m");
	free(txt_help);
	free(txt_key);
	return (0);
}
