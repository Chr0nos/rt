/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 10:45:29 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/16 10:46:26 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"

int					arg_display_help(t_rt *rt, int ac, char **av)
{
	(void)av;
	(void)ac;
	(void)rt;
	ft_putstr(
		"\033[01;032m\n\
		..______________________________________________________________..\n\
		||                                                              ||\n\
		||\033[01;035m                    WELCOME IN OUR RT MENU\
		\033[01;032m        ||\n\
		\\\\______________________________________________________________//\n\
		|                                                                |\n\
		|\
		\033[04;036mNext time, add map and try option :\
		\033[;032m |\n\
		|  -e  : output scene to sda format.                             |\n\
		|  -b  : export scene to image bmp & choose a destination path   |\n\
		|        -> ./rt -e scenes/test.sda ~Desktop/my_image.bmp        |\n\
		|  -s  : define your map size.                                   |\n\
		|        -> ./rt -s 800x800 scenes/test.sda                      |\n\
		|  -fs : full screen mode.                                       |\n\
		|  -x  : disable refresh mode.                                   |\n\
		|________________________________________________________________|\n\
		|____________________________  ENJOY ____________________________|\
		\n\n\033[;m");
	return (1);
}
