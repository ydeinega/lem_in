/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:27:50 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/15 15:27:52 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*create_room(t_lem_in *game, int num, char *visit)
{
	t_way	*room;

	room = NULL;
	if (visit[num] == VISITED)
		return (NULL);
	room = (t_way *)malloc(sizeof(t_way));
	room->num = num;
	room->ant = 0;
	room->next = NULL;
	if (num != game->start && num != game->end)
		visit[num] = VISITED;
	return (room);
}

void	clean_room_inway(t_way *head)
{
	t_way	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

t_way	*extract_way(t_lem_in *game, int num, char *visit, int *steps)
{
	t_way	*head;
	t_way	*room;
	t_lst	*tmp;

	tmp = NULL;
	room = NULL;
	head = create_room(game, game->end, visit);
	while (num >= 0)
	{
		room = create_room(game, num, visit);
		if (room)
		{
			room->next = head;
			head = room;
			*steps = *steps + 1;
		}
		else
		{
			clean_room_inway(head);
			return (NULL);
		}
		tmp = game->room[num].ways;
		num = tmp ? tmp->num : -1;
	}
	return (head);
}

void	add_to_way(t_route **way, t_way *room, int steps)
{
	static t_route	*last = NULL;
	t_route			*turn;

	turn = (t_route *)malloc(sizeof(t_route));
	turn->steps = steps;
	turn->room = room;
	turn->next = NULL;
	if (*way == NULL)
		*way = turn;
	if (last)
		last->next = turn;
	last = turn;
}

int		find_ways(t_lem_in *game, char *visit)
{
	int		steps;
	t_lst	*tmp;
	t_route	*way;
	t_way	*room;

	steps = 0;
	tmp = game->room[game->end].ways;
	way = NULL;
	room = NULL;
	while (tmp)
	{
		room = extract_way(game, tmp->num, visit, &steps);
		if (room)
			add_to_way(&way, room, steps);
		tmp = tmp->next;
		steps = 0;
	}
	if (way)
	{
		ft_lstprint(&(game->info));
		ft_printf("\n");
		move_ants(game, way);
	}
	return (way ? 1 : 0);
}
