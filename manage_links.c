/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:12:58 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/12 19:13:01 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			manage_links(t_lem_in *game, char *line)
{
	char	*name1;
	char	*name2;
	int		i;

	i = 0;
	while (line[i] != '-')
		i++;
	name1 = ft_strsub(line, 0, i);
	name2 = ft_strdup(&line[i + 1]);
	//ft_printf("name1 = |%s|, name2 = |%s|\n", name1, name2);
	if (!check_links(game, name1, name2))
		return (0);
	return (1);
}

int			check_links(t_lem_in *game, char *name1, char *name2)
{
	int n1;
	int n2;
	int i;

	i = -1;
	n1 = -1;
	n2 = -1;
	while (++i < game->room_num)
	{
		n1 = ft_strequ(game->room[i].name, name1) ? i : n1;
		n2 = ft_strequ(game->room[i].name, name2) ? i : n2;
	}
	//ft_printf("n1 = %i n2 = %i\n", n1, n2);
	free (name1);
	free (name2);
	if (n1 >= 0 && n2 >= 0)
	{
		if (n1 != n2 && (!add_links(game->room, n1, n2)
			|| !add_links(game->room, n2, n1)))
			return (0);
	}
	else
		return (0);
	return (1);
}

int			add_links(t_room_ar *room, int n1, int n2)
{
	t_lst	*link;

	link = (t_lst *)malloc(sizeof(t_lst));
	if (!link)
		return (0);
	link->num = n2;
	link->next = NULL;
	if (!room[n1].links)
		room[n1].links = link;
	else
	{
		link->next = room[n1].links;
		room[n1].links = link;
	}
	return (1);
}
