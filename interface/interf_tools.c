/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 00:50:39 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/10 06:57:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"
#include "rt.h"

/*
** this function search the N item corresponding to mask in his flags
** for the first use N = 0
** if no occurence is found: NULL will be returned
** note: the search is done from the end of the list to the start
*/

t_interface_cfg		*interf_getflag(t_interf *me, int mask, int n)
{
	int		p;

	p = INTERF_ITEMS;
	while (p--)
	{
		if ((me->cfg[p].flags & mask) && (n-- == 0))
			return (&me->cfg[p]);
	}
	return (NULL);
}

static int			interf_setvalue_core(char **split, t_obj *obj, t_rt *rt,
	t_interface_cfg *cfg)
{
	int			ret;
	t_sda		e;

	if (split[0])
	{
		e = (t_sda){0, rt, rt->root, obj, 0, 0};
		ret = cfg->set_value(&e, obj, split);
		if ((ret > 0) && (cfg->set_value == &sda_setup_texture))
			((t_cube*)obj->content)->color = 0x000000;
	}
	else if (cfg->set_value == &sda_setup_texture)
	{
		rt_obj_set_texture(obj, NULL);
		obj->cfgbits &= ~SDB_TEXTURE;
		ret = 0;
	}
	else
		ret = -3;
	return (ret);
}

/*
** this function is used to set a value on an object
** to do so: a function pointer is used after a split of line is done on ' '
** in case of error it will return a negative
** otherwise the return code of the function pointer will be returned
** (negative = error / 0 = nothing / 1 = ok)
*/

int					interf_setvalue(t_rt *rt, t_obj *obj, const char *line)
{
	char				**split;
	t_interface_cfg		*cfg;
	int					ret;

	if ((cfg = interf_getflag(&rt->interf, INTER_SELECTED, 0)) == NULL)
		return (-1);
	if (!cfg->set_value)
		return (0);
	if (!(split = ft_strsplit(line, ' ')))
		return (-2);
	ret = interf_setvalue_core(split, obj, rt, cfg);
	ft_freesplit(split);
	if (ret > 0)
		obj->cfgbits |= (cfg->bit | SDB_INTERFACE_EDIT);
	return (ret);
}

/*
** remove the specified bits in all flags
*/

void				interf_removeflag(t_interf *me, int mask)
{
	int			p;

	p = INTERF_ITEMS;
	while (p--)
		if (me->cfg[p].flags & mask)
			me->cfg[p].flags &= ~mask;
}

void				interf_resetline(t_interf *me)
{
	me->line[0] = '\0';
	me->line_pos = 0;
}
