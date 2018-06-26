/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:50:08 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/08 11:50:10 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_lst	*create_node(char *line, int *type)
{
	t_room_lst	*node;
	int			i;

	i = 0;
	node = (t_room_lst *)malloc(sizeof(t_room_lst));
	if (!node)
		return (NULL);
	while (line[i] && line[i] != ' ')
		i++;
	node->name = ft_strsub(line, 0, i);
	node->pt.i = ft_atoi(ft_strchr(line, ' '));
	node->pt.j = ft_atoi(ft_strrchr(line, ' '));
	node->type = *type;
	node->next = NULL;
	*type = ROOM;
	return (node);
}

int			pt_cmp(t_coord a, t_coord b)
{
	if (a.i == b.i && a.j == b.j)
		return (1);
	return (0);
}

int			add_node_lst(t_room_lst **head, t_room_lst *node, t_lem_in *game)
{
	t_room_lst	*tmp;
	int			check;

	tmp = NULL;
	check = 0;
	if (head && node)
	{
		tmp = *head;
		while (tmp->next)
		{
			if (ft_strequ(tmp->name, node->name) || pt_cmp(tmp->pt, node->pt))
			{
				game->error = 11;
				return (0);
			}
			tmp = tmp->next;
		}
		if (ft_strequ(tmp->name, node->name) || pt_cmp(tmp->pt, node->pt))
		{
			game->error = 11;
			return (0);
		}
		tmp->next = node;
	}
	return (1);
}

void		create_room_array(t_lem_in *game)
{
	int			i;
	t_room_lst	*head;
	t_room_lst	*tmp;

	i = 0;
	game->room = (t_room_ar *)malloc(sizeof(t_room_ar) * game->room_num);
	head = game->node;
	tmp = NULL;
	while (head)
	{
		game->room[i].name = head->name;
		game->room[i].pt = head->pt;
		game->room[i].links = NULL;
		game->room[i].ways = NULL;
		if (head->type == START)
			game->start = i;
		if (head->type == END)
			game->end = i;
		i++;
		tmp = head;
		head = head->next;
		free(tmp);
	}
	game->node = NULL;
}
