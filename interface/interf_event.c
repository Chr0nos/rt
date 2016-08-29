/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:32:51 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/29 17:47:36 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "keyboard.h"
#include "sda.h"

static int	change_scale(int x)
{
	if (x < 46)
		return (-100);
	else if (x < 92)
		return (-10);
	else if (x < 138)
		return (-1);
	else if (x < 184)
		return (1);
	else if (x < 230)
		return (10);
	else if (x < 270)
		return (100);
	else
		return (0);
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

int			interf_event(t_v2i *mouse_pos, t_rt *rt)
{
	int		size;
	int		click;

	size = 28;
	click = mouse_pos->y;
	if (click >= I_SCALE * size + 8 && click <= I_VIDE1 * size + 8)
		rt->interf->scale = change_scale(mouse_pos->x);
	else if (click >= I_ID * size + 8 && click < I_VIDE2 * size + 8)
		change_selected_obj(rt);
	else if (click >= I_TYPE * size + 8 && click < I_NAME * size + 8)
		change_type(*rt->interf->champs_obj[I_TYPE]);
	else if (click >= I_NAME * size + 8 && click < I_TEXT * size + 8)
		change_str_obj(rt->interf, I_NAME);
	else if (click >= I_TEXT * size + 8 && click < I_VIDE3 * size + 8)
		change_str_obj(rt->interf, I_TEXT);
	else if ((click >= I_POSX * size + 8 && click < I_VIDE5 * size + 8)
		|| (click >= I_REFL * size + 8 && click < I_VIDE8 * size + 8))
		change_one(rt->interf->scale, click - 8, rt->interf->champs_obj);
	else if (click >= I_COL_R * size + 8 && click < I_REFL * size + 8)
		change_color(rt->interf->scale, click - 8, rt->interf->champs_obj);
	else if (click >= I_ENTER * size + 8 && click < I_END * size + 8)
		change_all_data_obj(rt, rt->interf->champs_obj);
	rt_bounds_update(rt->root);
	rt->keyboard |= FORCE_DISPLAY;
	return (1);
}
