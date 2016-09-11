/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:56:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 00:29:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "arguments.h"
#include "libft.h"
#define ARG_NUM 5

t_v2i		arg_getgeo(const char *s)
{
	t_v2i		geo;
	char		*sx;
	char		*sy;
	int			p;

	p = 0;
	while (ft_isdigit(s[p]))
		p++;
	sx = ft_strndup(s, (unsigned int)p);
	p++;
	sy = ft_strdup(&s[p]);
	geo.x = ft_atoi(sx);
	geo.y = ft_atoi(sy);
	ft_mfree(2, sx, sy);
	return (geo);
}

/*
** returns the index in the tab of name
*/

static int	arg_parse_option(const t_argument *args, int p, const char *name)
{
	while (p--)
	{
		if (!ft_strcmp(args[p].name, name))
			return (p);
	}
	return (-1);
}

/*
** put here the functions to add to the parser, function has to return:
** the number of parameter it used (cannot be higher than 0xffff)
** a quit code: PARSE_ARG_STOP / PARSE_ARG_ERROR
*/

static void	arg_parse_init(t_argument *arg_list)
{
	arg_list[0] = (t_argument){"-e", 1, &rt_export};
	arg_list[1] = (t_argument){"-b", 2, &rt_export_bmp};
	arg_list[2] = (t_argument){"-s", 1, &arg_geometry};
	arg_list[3] = (t_argument){"-fs", 0, &arg_fs};
	arg_list[4] = (t_argument){"-h", 0, &arg_display_help};
}

static int	arg_parse_error(const char *err, int ret)
{
	ft_putendl_fd(err, 2);
	return (ret);
}

int			arg_parse(t_rt *rt, int ac, char **av)
{
	t_argument			arg_list[ARG_NUM];
	int					index;
	int					ret;

	arg_parse_init((t_argument*)arg_list);
	while ((ac > 0) && (*av) && (*av[0] == '-'))
	{
		index = arg_parse_option(arg_list, ARG_NUM, *av);
		if (index < 0)
			return (arg_parse_error("error: unknow option", 2));
		ac--;
		av++;
		if (ac < arg_list[index].params_mins)
			return (arg_parse_error("error: missing argument", 1));
		ret = arg_list[index].f(rt, ac, av);
		ac -= (ret & 0xffff);
		av += (ret & 0xffff);
		if (ret & PARSE_ARG_STOP)
			break ;
		if (ret & (PARSE_ARG_ERROR | PARSE_ARG_STOPALL))
			return ((ret & PARSE_ARG_STOPALL) ? 0 : 1);
	}
	return (rt_normal(rt, av[0]));
}
