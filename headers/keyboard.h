/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 22:26:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 14:36:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

enum	e_keyboard
{
	LEFT = 1,
	RIGHT = 1 << 1,
	UP = 1 << 2,
	DOWN = 1 << 3,
	ZOOMIN = 1 << 4,
	ZOOMOUT = 1 << 5,
	QUIT = 1 << 6,
	ROTATE_LEFT = 1 << 7,
	ROTATE_RIGHT = 1 << 8,
	ROTATE_UP = 1 << 9,
	ROTATE_DOWN = 1 << 10,
	FORCE_DISPLAY = 1 << 11,
	FAST = 1 << 12,
	ROLL_LEFT = 1 << 13,
	ROLL_RIGHT = 1 << 14,
	FULLSCREEN = 1 << 15,
	MENU = 1 << 16,
	FILTER_RED = 1 << 17,
	FILTER_GREEN = 1 << 18,
	FILTER_BLUE = 1 << 19,
	FILTER = FILTER_BLUE | FILTER_GREEN | FILTER_RED,
	ROLL = ROLL_LEFT | ROLL_RIGHT,
	ROTATE = ROTATE_DOWN | ROTATE_LEFT | ROTATE_RIGHT | ROTATE_UP,
	SIDE = LEFT | RIGHT | UP | DOWN | ZOOMIN | ZOOMOUT,
	MOVE = ROLL | ROTATE | SIDE
};

typedef struct	s_kb_cmp
{
	int			key;
	int			bit;
}				t_kbcmp;

#endif
