/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:32:51 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:40:22 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "keyboard.h"

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
	t_type	nb_of_type;
	t_type	new_type;

	nb_of_type = 16;
	new_type = rt_gettype(type) + 1;
	if (new_type > nb_of_type)
		new_type = 1;
	return (search_str_type(new_type));
}

static void change_one_champs(int scale, int y,
	char *interf_champs[NB_CHAMPS][LARGER_SIZE])
{
	double	tmp;
	int		index;

	index = (int)(y / 28);
	tmp = 0.0;
	if ((index < I_END && index > I_TEXT))
	{
		if (index >= I_COL_R && index <= I_ALPHA)
		{
			tmp = ft_atod(*interf_champs[index]);
			tmp += scale;
			if (tmp > 255)
				tmp = 255;
			else if (tmp < 0)
				tmp = 0;
			free (*interf_champs[index]);
			*interf_champs[index] = ft_dtoa(tmp, 2);
		}
		else
		{
			tmp = ft_atod(*interf_champs[index]);
			free (*interf_champs[index]);
			if (index >= I_DIRX && index <= I_DIRZ)
			{
				tmp += (scale * 0.01);
				*interf_champs[index] = ft_dtoa(tmp, 6);
			}
			else
			{
				tmp += scale;
				*interf_champs[index] = ft_dtoa(tmp, 2);
			}
		}
	}
}

static void change_selected_obj(t_rt *rt)
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

static void change_str_obj(t_interf *champs_obj, int index)
{
//	char	*str_in;

//	str_in =
(void)champs_obj;
(void)index;
	ft_putstr("\033[01;032mPlease enter new name for this object :\n\033[;m]");
/* en attente lecture entree standard
	free(*champs_obj[index])
	*champs_obj[index] = ft_strdup(str_in);
	free(str_in);
*/
}

int	interf_event(t_v2i *mouse_pos, t_rt *rt)
{
	int	size;
	int pas;
	int	click;

	size = 28;
	pas = 8;
	click = mouse_pos->y;
	if (click >= I_SCALE * size + pas && click <= I_VIDE1 * size + pas)
		rt->interf->scale = change_scale(mouse_pos->x);
	else if (click >= I_ID * size + pas && click< I_VIDE2 * size + pas) // CLICK SUR CHAMPS OBJ ID
		change_selected_obj(rt);
	else if (click >= I_TYPE * size + pas && click < I_NAME * size + pas) // CLICK SUR CHAMPS TYPE
		change_type(*rt->interf->champs_obj[I_TYPE]);
	else if (click >= I_NAME * size + pas && click < I_TEXT * size + pas) // CLICK SUR CHAMPS NAME
		change_str_obj(rt->interf, I_NAME);
	else if (click >= I_TEXT * size + pas && click < I_VIDE3 * size + pas) // CLICK SUR CHAMPS TEXTURE
		change_str_obj(rt->interf, I_TEXT);
	else if (click >= I_POSX * size + pas && click < I_VIDE8 * size + pas) // CLICK SUR CHAMPS
		change_one_champs(rt->interf->scale, mouse_pos->y - pas, rt->interf->champs_obj);
	else if (click >= I_ENTER * size + pas && click < I_END * size + pas) //  CLICK SUR BUTTON ENTER
		change_all_data_obj(rt, rt->interf->champs_obj);
	rt_bounds_update(rt->root);
	rt->keyboard |= FORCE_DISPLAY;
	return (1);
}
