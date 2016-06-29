/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 13:30:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 22:44:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "stdlib.h"

static int	sda_isobj(const char *line)
{
	if (!*line)
		return (0);
	while (*line)
	{
		if ((*line < 'A') || (*line > 'Z'))
			return (0);
		line++;
	}
	return (1);
}

static int	sda_spliter(const char *line, char ***av, int *ac)
{
	*av = ft_strsplitstr(line, " \t");
	*ac = (int)ft_tabcount((void **)*av);
	if (!*ac)
		free(*av);
	return ((*ac != 0));
}

static void		sda_mkobj(const char *s, int lvl, int *last_lvl,
	t_obj **current_obj)
{
	const t_type	type = rt_gettype(s);
	t_obj			*parent;

	if (type == INVALID)
	{
		ft_printf("warning: INVALID object type for %s : ignoring\n", s);
		return ;
	}
	if ((*last_lvl < lvl) || ((*current_obj)->type == ROOT))
		parent = *current_obj;
	else
		parent = rt_obj_nparent(*current_obj,
			(unsigned int)(*last_lvl - lvl + 1));
	*current_obj = rt_factory_alloc(type, parent);
	*last_lvl = lvl;
}

int			sda_eval(const char *line, t_rt *rt, t_obj *root, const int lvl)
{
	static t_obj	*current_obj = NULL;
	static int		last_lvl = 0;
	char			**av;
	int				ac;
	int				ret;

	if (!current_obj)
		current_obj = root;
	line += lvl;
	if (!sda_spliter(line, &av, &ac))
		return (-1);
	ret = 0;
	if ((!ac) || (!av[0]) || (av[0][0] == '#') ||
		(av[0][0] == '}') || (av[0][0] == '{'))
		;
	else if (sda_isobj(av[0]) > 0)
		sda_mkobj(av[0], lvl, &last_lvl, &current_obj);
	else if ((current_obj) && (sda_settings(current_obj, rt, ac, av)) >= 0)
		;
	else
		ret = -1;
	ft_free_tab(av, (size_t)ac);
	free(av);
	return (ret);
}
