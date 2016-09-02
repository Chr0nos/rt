/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 11:33:19 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/02 14:56:09 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "keyboard.h"

void			change_color(int scale, int y,
		char *champs[NB_CHAMPS][LARGER_SIZE])
{
	double	tmp;
	int		index;

	index = (int)(y / 28);
	tmp = 0.0;
	if ((index < I_END && index > I_TEXT))
	{
		if (index >= I_COL_R && index <= I_ALPHA)
		{
			tmp = ft_atod(*champs[index]);
			tmp += scale;
			if (tmp > 255)
				tmp = 255;
			else if (tmp < 0)
				tmp = 0;
			free(*champs[index]);
			*champs[index] = ft_dtoa(tmp, 2);
		}
	}
}

void			change_one(int scale, int y,
		char *champs[NB_CHAMPS][LARGER_SIZE])
{
	double	tmp;
	int		index;

	index = (int)(y / 28);
	tmp = 0.0;
	if ((index <= I_SIZE && index >= I_POSX))
	{
		tmp = ft_atod(*champs[index]);
		free(*champs[index]);
		if (index >= I_DIRX && index <= I_DIRZ)
		{
			tmp += (scale * 0.01);
			*champs[index] = ft_dtoa(tmp, 6);
		}
		else
		{
			tmp += scale;
			*champs[index] = ft_dtoa(tmp, 2);
		}
	}
}

static t_obj	*protect_change(t_rt *rt, t_obj *obj, t_uint *root_id)
{
	if (!obj || (obj &&
				!(obj->next) && !(obj->childs) && !(obj->parent->childs)))
	{
		*root_id = 0;
		while (!(obj = rt_obj_byid(rt->root, (*root_id)++))
				&& *root_id < 9000000)
			;
		if (*root_id == 9000000)
		{
			ft_putstr("\n/033[01;33mError, root scene\
					not contain valid ID\n\n");
			exit(1);
		}
	}
	return (obj);
}

void			change_selected_obj(t_rt *rt)
{
	static t_uint	root_id = 0;
	t_obj			*obj;

	obj = rt->interf->obj_selected;
	if (obj)
	{
		if (!rt->interf->scale)
			rt->interf->scale = 1;
		root_id = (t_uint)(rt->interf->scale + (int)obj->id);
		obj = rt_obj_byid(rt->root, root_id);
	}
	if (!(obj))
	{
		while (!(obj = rt_obj_byid(rt->root, root_id++))
				&& root_id < 9000000)
			;
	}
	rt->interf->obj_selected = protect_change(rt, obj, &root_id);
	fill_champs_obj(rt->interf->obj_selected, rt->interf->champs_obj);
}
