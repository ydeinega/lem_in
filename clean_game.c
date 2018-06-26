/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 20:12:22 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/13 20:12:25 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_game(t_lem_in *game)
{
	clean_node(game->node);
	clean_room(game->room, game->room_num);
	clean_info(game->info);
	game->node = NULL;
	game->room = NULL;
	game->info = NULL;
	free(game);
}

void	clean_node(t_room_lst *node)
{
	t_room_lst	*head;

	head = NULL;
	if (node)
	{
		while (node)
		{
			head = node;
			ft_strdel(&(head->name));
			node = node->next;
			free(head);
		}
	}
}

void	clean_room(t_room_ar *room, int room_num)
{
	int			i;

	i = -1;
	if (room)
	{
		while (++i < room_num)
		{
			ft_strdel(&(room[i].name));
			clean_lst(&(room[i].links));
			clean_lst(&(room[i].ways));
		}
		free(room);
	}
}

void	clean_info(t_list *info)
{
	t_list		*tmp;

	tmp = NULL;
	if (info)
	{
		while (info)
		{
			tmp = info;
			ft_strdel((char **)(&(info->content)));
			info = info->next;
			free(tmp);
		}
	}
}

void	clean_lst(t_lst **list)
{
	t_lst	*head;
	t_lst	*tmp;

	head = NULL;
	tmp = NULL;
	if (list)
	{
		head = *list;
		while (head)
		{
			tmp = head;
			head = head->next;
			free(tmp);
		}
		*list = NULL;
	}
}
