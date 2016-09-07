/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:42:39 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/07 15:55:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "osconfig.h"

int			getkeybit(const int keycode)
{
	const t_kbcmp	cmp[] = {
		{KC_W, ZOOMIN},
		{KC_S, ZOOMOUT},
		{KC_ESCAPE, QUIT},
		{KC_SPACE, UP}, {KC_E, ROLL_RIGHT}, {KC_Q, ROLL_LEFT},
		{KC_LCTRL, DOWN},
		{KC_C, DOWN}, {KC_A, RIGHT}, {KC_D, LEFT}, {KC_UP, ROTATE_UP},
		{KC_DOWN, ROTATE_DOWN}, {KC_LEFT, ROTATE_LEFT},
		{KC_RIGHT, ROTATE_RIGHT},
		{KC_P, FORCE_DISPLAY},
		{KC_LSHIFT, FAST},
		{SDLK_n, AMBIANT_MORE | FORCE_DISPLAY},
		{SDLK_j, AMBIANT_LESS | FORCE_DISPLAY}
	};
	unsigned int	p;

	p = 16;
	while (p--)
		if (cmp[p].key == keycode)
			return (cmp[p].bit);
	return (0);
}
