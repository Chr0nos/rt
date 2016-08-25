/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 11:33:19 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/25 13:16:19 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "keyboard.h"

void	change_color(int scale, int y, char *champs[NB_CHAMPS][LARGER_SIZE])
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

void	change_one(int scale, int y, char *champs[NB_CHAMPS][LARGER_SIZE])
{
	double	tmp;
	int		index;

	index = (int)(y / 28);
	tmp = 0.0;
	if ((index < I_END && index > I_TEXT))
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

void	change_selected_obj(t_rt *rt)
{
	static t_uint	root_id = 1;

	if (rt->interf->obj_selected)
		rt->interf->obj_selected = rt_obj_byid(rt->root,
			(t_uint)((int)rt->interf->obj_selected->id + rt->interf->scale));
	if (!(rt->interf->obj_selected))
	{
		rt->interf->obj_selected = rt_obj_byid(rt->root, root_id++);
		if ((rt->interf->obj_selected->next) == NULL)
			root_id = 1;
	}
	init_champs_obj(rt->interf->champs_obj);
	fill_champs_obj(rt->interf->obj_selected, rt->interf->champs_obj);
}
