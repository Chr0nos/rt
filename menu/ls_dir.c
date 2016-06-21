/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 10:30:07 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/21 13:47:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "menu.h"
#include <dirent.h>

/*
** list a directory (path)
** using the mask as format, mask should be *.yolo
** in case of error NULL will be returned
** otherwise the chained list returned will
*/

t_list	*ls_dir(const char *path, const char *mask)
{
	DIR				*dir;
	t_list			*lst;
	struct dirent	*file;

	if (!(dir = opendir(path)))
		return (NULL);
	lst = NULL;
	while ((file = readdir(dir)))
	{
		if ((ft_strcmp(file->d_name, "..")) && (ft_strcmp(file->d_name, ".")) &&
			(ft_match(file->d_name, mask)))
		{
			ft_lstpush_sort(&lst,
				ft_lstnewstr(ft_strjoin("./scenes/", file->d_name)),
				&ft_lststrcmp);
		}
	}
	closedir(dir);
	return (lst);
}
