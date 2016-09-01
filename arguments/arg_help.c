/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 10:45:29 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/01 17:40:43 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include <fcntl.h>
#include <unistd.h>

static void		read_txt_help(char **str, char *src)
{
	int		ret_fd[2];
	char	*line[3];

	if ((ret_fd[1] = open(src, O_RDONLY)) == -1)
	{
		ft_putstr("Error, arg_help.txt or arg_help_key.txt not found\n");
		exit(1);
	}
	while ((ret_fd[0] = ft_get_next_line(ret_fd[1], &line[0])) == 1)
	{
		line[1] = ft_strjoin(line[0], "\n");
		free(line[0]);
		if (!(*str))
		{
			*str = ft_strdup(line[1]);
			free(line[1]);
		}
		else
		{
			line[2] = *str;
			*str = ft_strjoin(*str, line[1]);
			free(line[2]);
		}
	}
	close(ret_fd[1]);
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
	char *txt_help;
	char *txt_key;

	(void)av;
	(void)ac;
	(void)rt;
	txt_help = NULL;
	txt_key = NULL;
	read_txt_help(&txt_help, "arguments/arg_help.txt");
	read_txt_help(&txt_key, "arguments/arg_help_key.txt");
	search_and_replace(txt_help);
	search_and_replace(txt_key);
	ft_putstr(txt_help);
	ft_putstr(txt_key);
	ft_putstr("\033[;m");
	free(txt_help);
	free(txt_key);
	return (0);
}
