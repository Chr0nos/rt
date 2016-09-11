/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 13:30:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:54:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "stdlib.h"
#include "objects.h"

static int		sda_isobj(const char *line)
{
	if (!*line)
		return (0);
	while (*line)
	{
		if ((((*line < 'A') || (*line > 'Z'))) && (*line != '_'))
			return (0);
		line++;
	}
	return (1);
}

int				sda_spliter(const char *line, char ***av, int *ac)
{
	*av = ft_strsplitstr(line, " \t");
	*ac = (int)ft_tabcount((void **)*av);
	if (!*ac)
		free(*av);
	return ((*ac != 0));
}

static int		sda_mkobj(const char *s, int lvl, t_sda *e)
{
	const t_type	type = rt_gettype(s);
	t_obj			*parent;

	if (type == INVALID)
	{
		ft_printf("warning: INVALID object type for %s : ignoring\n", s);
		return (-1);
	}
	if ((e->last_lvl < lvl) || (e->current_obj->type == ROOT))
		parent = e->current_obj;
	else
		parent = rt_obj_nparent(e->current_obj,
			(unsigned int)(e->last_lvl - lvl + 1));
	if (!(e->current_obj = rt_factory_alloc(type, parent)))
		return (-2);
	rt_obj_set_reflect(e->current_obj, e->rt->settings.default_reflect);
	if ((e->current_obj->type & SDA_COLOR) && (e->current_obj->type != SETTING))
		((t_cube*)e->current_obj->content)->color =
			e->rt->settings.default_color;
	e->last_lvl = lvl;
	return (0);
}

int				sda_eval(const char *line, t_sda *e, const int lvl)
{
	char			**av;
	int				ac;
	int				ret;

	line += lvl;
	if (!sda_spliter(line, &av, &ac))
		return (-1);
	ret = 0;
	if ((!ac) || (!av[0]) || (av[0][0] == '#'))
		;
	else if (sda_isobj(av[0]) != 0)
	{
		if (sda_mkobj(av[0], lvl + e->lvl_offset, e) < 0)
		{
			ft_putstr_fd("error: failed to create object\n", 2);
			ret = -2;
		}
	}
	else if ((e->current_obj) && (sda_settings(e, ac, av) >= 0))
		;
	else
		ret = -1;
	ft_free_tab(av, (size_t)ac);
	free(av);
	return (ret);
}
