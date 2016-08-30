/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:32:51 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/30 21:06:40 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "keyboard.h"
#include "sda.h"

static void	change_scale(int x, t_interf *in)
{
	int		i_scale;

	i_scale = -1;
	if (x < 46 && !(i_scale = 0))
		in->scale = -100;
	else if (x < 92 && (i_scale = 1))
		in->scale = -10;
	else if (x < 138 && (i_scale = 2)) 
		in->scale = -1;
	else if (x < 184 && (i_scale = 3))
		in->scale = 1;
	else if (x < 230 && (i_scale = 4))
		in->scale = 10;
	else if (x < 270 && (i_scale = 5))
		in->scale = 100;
	else
		in->scale = 0;
	free_surfaces(in->surface_scale);
	fill_surface_scale(in, i_scale);
}

static char	*change_type(char *type)
{
	int		nb_of_type;
	t_type	new_type;

	nb_of_type = 16;
	new_type = rt_gettype(type) + 1;
	if (new_type > (t_type)nb_of_type)
		new_type = 1;
	return (search_str_type(new_type));
}

static void	change_str_obj(t_interf *interf, int i)
{
	char	*str_in;

	ft_putstr("\033[01;032mPlease enter the new name of this object :\n");
	ft_get_next_line(1, &str_in);
	ft_putstr("\n\033[;m]\n");
	if (i == I_NAME)
		interf->obj_selected->cfgbits |= SDB_NAME;
	else
		interf->obj_selected->cfgbits |= SDB_TEXTURE;
	free(*(interf->champs_obj[i]));
	*(interf->champs_obj[i]) = ft_strdup(str_in);
	free(str_in);
}

void		interf_event(t_v2i *mouse_pos, t_rt *rt)
{
	int			size;
	int			click;
	t_interf	*in;

	size = 28;
	click = mouse_pos->y;
	in = rt->interf;
	if (click >= 0 && click <= size + 8)
		change_scale(mouse_pos->x, rt->interf);
	else if (click >= I_ID * size + 64 && click < I_VIDE2 * size + 64)
		change_selected_obj(rt);
	else if (!(rt->interf->obj_selected))
		return ;
	else if (click >= I_TYPE * size + 64 && click < I_NAME * size + 64)
		change_type(*in->champs_obj[I_TYPE]);
	else if (click >= I_NAME * size + 64 && click < I_TEXT * size + 64)
		change_str_obj(in, I_NAME);
	else if (click >= I_TEXT * size + 64 && click < I_VIDE3 * size + 64)
		change_str_obj(in, I_TEXT);
	else if ((click >= I_POSX * size + 64 && click < I_VIDE5 * size + 64)
		|| (click >= I_REFL * size + 64 && click < I_VIDE8 * size + 64))
		change_one(in->scale, click - 64, in->champs_obj);
	else if (click >= I_COL_R * size + 64 && click < I_REFL * size + 64)
		change_color(in->scale, click - 64, in->champs_obj);
	else if (click >= I_ENTER * size + 64 && click < I_END * size + 64)
		change_all_data_obj(rt, in->champs_obj);
	rt_bounds_update(rt->root);
	rt->keyboard |= FORCE_DISPLAY;
}
