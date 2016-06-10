/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:42:39 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/09 17:42:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"

int			getkeybit(const int keycode)
{
	const t_kbcmp	cmp[] = {
		{SDLK_w, ZOOMIN},
		{SDLK_s, ZOOMOUT},
		{SDLK_ESCAPE, QUIT},
		{SDLK_SPACE, UP},
		{SDLK_e, ROLL_RIGHT},
		{SDLK_q, ROLL_LEFT},
		{SDLK_LCTRL, DOWN},
		{SDLK_c, DOWN},
		{SDLK_a, RIGHT},
		{SDLK_d, LEFT},
		{SDLK_UP, ROTATE_UP},
		{SDLK_DOWN, ROTATE_DOWN},
		{SDLK_LEFT, ROTATE_LEFT},
		{SDLK_RIGHT, ROTATE_RIGHT},
		{SDLK_p, FORCE_DISPLAY},
		{SDLK_LSHIFT, FAST}
	};
	unsigned int	p;

	p = sizeof(cmp);
	while (p--)
		if (cmp[p].key == keycode)
			return (cmp[p].bit);
	return (-1);
}
