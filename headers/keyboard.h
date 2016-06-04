/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 22:26:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/04 22:53:45 by snicolet         ###   ########.fr       */
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
	QUIT = 1 << 6
};

typedef struct	s_kb_cmp
{
	int			key;
	int			bit;
}				t_kbcmp;

#endif
