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

static int	change_interf_scale(int x)
{
	if (x < 42)
		return (-100);
	else if (x < 84)
		return (-10);
	else if (x < 126)
		return (-1);
	else if (x < 168)
		return (1);
	else if (x < 210)
		return (10);
	else if (x < 252)
		return (100);
	else
		return (0);
}

static void change_one_champs_obj(int scale, int y,
	char *interf_champs[NB_CHAMPS][LARGER_SIZE])
{
	double	tmp;
	int		index;

	index = (int)(y / 25);
	ft_putstr("index = ");
	ft_putnbr(index);
	ft_putchar('\n');
	tmp = 0.0;
	if ((index < NB_CHAMPS - 1 && index > I_TEXT) || index > I_TYPE)
	{
		ft_putstr("le champs vallait = ");
		ft_putstr(*interf_champs[index]);
		ft_putchar('\n');
		if (index >= I_COL_R && index <= I_ALPHA)
		{
			tmp = ft_basetoul(*interf_champs[index], "0123456789ABCDEF");
			tmp += scale; //a additionner en hexa
			free (*interf_champs[index]);
			*interf_champs[index] = ft_dtoa(tmp, 2); // remettre en hexa
		}
		else
		{
			tmp = ft_atod(*interf_champs[index]);
			tmp += scale;
			free (*interf_champs[index]);
			*interf_champs[index] = ft_dtoa(tmp, 2);
		}
		ft_putstr("maintenant il vaut = ");
		ft_putstr(*interf_champs[index]);
		ft_putchar('\n');
	}
}

static void change_selected_obj(t_rt *rt)
{
	static t_uint	root_id = 1;

	ft_putstr("recherche obj next\n");
	if (rt->interf->obj_selected)
		rt->interf->obj_selected = rt_obj_byid(rt->root,
			(t_uint)((int)rt->interf->obj_selected->id + rt->interf->scale));
	if (!(rt->interf->obj_selected))
	{
		rt->interf->obj_selected = rt_obj_byid(rt->root, root_id++);
		if ((rt->interf->obj_selected->next) == NULL)
			root_id = 1;
	}
	init_selected_obj(rt->interf->obj_selected, rt->interf->champs_obj);
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

int	interf_event(t_v2i *mouse_pos, t_rt *rt)
{
	if (mouse_pos->y > 0 && mouse_pos->y < 40)
	{
		rt->interf->scale = change_interf_scale(mouse_pos->x);
		ft_putstr("nouveau scale = ");
		ft_putnbr(rt->interf->scale);
		ft_putchar('\n');
	}
	else if (mouse_pos->y >= 50 && mouse_pos->y < 75) // CLICK SUR CHAMPS OBJ ID
		change_selected_obj(rt);
	else if (mouse_pos->y >= 100 && mouse_pos->y < 125) // CLICK SUR CHAMPS TYPE
		change_str_obj(rt->interf, 3);
//		change_type_obj(rt->interf, 1);
	else if (mouse_pos->y >= 125 && mouse_pos->y < 150) // CLICK SUR CHAMPS NAME
		change_str_obj(rt->interf, 3);
	else if (mouse_pos->y >= 150 && mouse_pos->y < 175) // CLICK SUR CHAMPS TEXTURE
		change_str_obj(rt->interf, 4);
	else if (mouse_pos->y >= 200 && mouse_pos->y < 675) // CLICK SUR CHAMPS
		change_one_champs_obj(rt->interf->scale, mouse_pos->y - 50, rt->interf->champs_obj);
	else if (mouse_pos->y >= 700 && mouse_pos->y < 750) //  CLICK SUR BUTTON ENTER
		change_all_data_obj(rt, rt->interf->champs_obj);
	return (1);
}
