/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:54:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 01:34:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "menu.h"
#include "keyboard.h"

int				menu_init(t_rt *rt, const char *path)
{
	t_list		*files;
	int			ret;
	const char	*masks[2] = {"*.yolo", "*.sda"};

	if (!path)
		path = "./scenes/";
	if (!(files = ls_dir(path, (const char **)(unsigned long)masks, 2)))
	{
		ft_putendl_fd("nothing to do: empty directory", 2);
		return (-2);
	}
	rt->rts_size = ft_lstsize(files);
	if ((rt->rts = malloc(
		(sizeof(t_rt) * rt->rts_size) +
		(sizeof(SDL_Rect) * rt->rts_size))) != NULL)
	{
		rt_create_window(rt);
		ret = menu_configure_rts(rt, rt->rts, files);
		rt->keyboard |= MENU;
		rt_start(rt);
	}
	else
		ret = -1;
	ft_lstdel(&files, &ft_lstpulverisator);
	return (ret);
}
