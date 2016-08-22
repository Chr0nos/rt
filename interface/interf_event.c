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

static int	change_interf_scale(int x)
{
	ft_putstr("\tchange_scale\n");
	if (x < 50)
		return (-1);
	else if (x < 50)
		return (-10);
	else if (x < 50)
		return (-100);
	else if (x < 50)
		return (1);
	else if (x < 50)
		return (10);
	else if (x < 50)
		return (100);
	else
		return (0);
}

static void change_one_champs_obj(int scale, int x,
	char *interf_champs[NB_CHAMPS][LARGER_SIZE])
{
	double	tmp;
	int		index;

	index = (int)(x / 25);
	if (index < 23 && (index != 1 && index != 5 && index != 9 && index != 13))
	{
		tmp = ft_atod(*interf_champs[index]);
		tmp += scale;
		free (*interf_champs[index]);
		*interf_champs[index] = ft_dtoa(tmp, 2);
	}
	ft_putstr("\tchange_one_champs\n");
}

static void change_selected_obj(t_rt *rt)
{
	int i;
	t_obj	*obj;

	i = rt->interf->scale;
	obj = rt->interf->obj_selected;
	if (obj)
	{
		if (i > 0)
		{
			while (i-- && obj)
				obj = obj->next;
		}
		else
			obj = rt_obj_byid(rt->root, (t_uint)((int)obj->id + i));
		rt->interf->obj_selected = obj;
	}
	else
		rt->interf->obj_selected = rt->root;
	ft_putstr("\tchange_selected_obj\n");
}

static void change_str_obj(t_interf *champs_obj, int index)
{
//	char	*str_in;

//	str_in =
(void)champs_obj;
(void)index;
	ft_putstr("\033[01;032mPlease enter new name for this object :\n\033[;m]");
	ft_putstr("\033[01;032mLecture entree standard a implementer\033[;m]"); //tmp
/* en attente lecture entree standard
	free(*champs_obj[index])
	*champs_obj[index] = ft_strdup(str_in);
	free(str_in);
*/
}
/*
*champs_txt[0] = ft_strdup("Id ................... :"); pixel_y = 50 a 75
*champs_txt[1] = ft_strdup("");

*champs_txt[2] = ft_strdup("Type .............. :");pixel_y = 100 a 125
*champs_txt[3] = ft_strdup("Name ........... :");pixel_y = 125 a 150
*champs_txt[4] = ft_strdup("texture ............ :");pixel_y = 150 a 175
*champs_txt[5] = ft_strdup("");
*champs_txt[6] = ft_strdup("pos.X ............. :");pixel_y = 200 a 225
*champs_txt[7] = ft_strdup("pos.Y .............. :");pixel_y = 225 a 250
*champs_txt[8] = ft_strdup("pos.Z ............. :");pixel_y = 250 a 275
*champs_txt[9] = ft_strdup("");
*champs_txt[10] = ft_strdup("dir.X ............... :");pixel_y = 300 a 325
*champs_txt[11] = ft_strdup("dir.Y ................ :");pixel_y = 325 a 350
*champs_txt[12] = ft_strdup("dir.Z ............... :");pixel_y = 375 a 400
*champs_txt[13] = ft_strdup("");
*champs_txt[14] = ft_strdup("color.R ............ :");pixel_y = 425a 450
*champs_txt[15] = ft_strdup("color.G ........... :");pixel_y = 450 a 475
*champs_txt[16] = ft_strdup("color.B ........... :");pixel_y = 475 a 500
*champs_txt[17] = ft_strdup("");
*champs_txt[18] = ft_strdup("transparence :");pixel_y = 525 a 550
*champs_txt[19] = ft_strdup("reflection (%) :");pixel_y = 550 a 575
*champs_txt[20] = ft_strdup("refraction (%) :");pixel_y = 600 a 625
*champs_txt[21] = ft_strdup("");
*champs_txt[22] = ft_strdup("size ................ :");pixel_y = 650 a 675
*champs_txt[23] = NULL;
*/
int	interf_event(t_v2i *mouse_pos, t_rt *rt)
{
	if (mouse_pos->y > 5 && mouse_pos->y < 30)
		rt->interf->scale = change_interf_scale(mouse_pos->x);
	else if (mouse_pos->y >= 50 && mouse_pos->y < 75) // CLICK SUR CHAMPS OBJ ID
		change_selected_obj(rt);
//	else if (mouse_pos->y >= 100 && mouse_pos->y < 125) // CLICK SUR CHAMPS TYPE
//		change_type_obj(rt->interf, 1);
	else if (mouse_pos->y >= 125 && mouse_pos->y < 150) // CLICK SUR CHAMPS NAME
		change_str_obj(rt->interf, 3);
	else if (mouse_pos->y >= 150 && mouse_pos->y < 175) // CLICK SUR CHAMPS TEXTURE
		change_str_obj(rt->interf, 4);
	else if (mouse_pos->y >= 200 && mouse_pos->y < 675) // CLICK SUR CHAMPS
		change_one_champs_obj(rt->interf->scale, mouse_pos->x - 50, rt->interf->champs_obj);
	else if (mouse_pos->y >= 700 && mouse_pos->y < 750) //  CLICK SUR BUTTON ENTER
		change_all_data_obj(rt->interf->obj_selected, rt->interf->champs_obj);
	ft_putstr("\tinterf_event\n");
	return (1);
}
