/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:39:43 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/14 13:39:45 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst	*queue_elem(int num)
{
	t_lst	*elem;

	elem = (t_lst *)malloc(sizeof(t_lst));
	if (!elem)
		return (0);
	elem->num = num;
	elem->next = NULL;
	return (elem);
}

void	add_to_queue(t_lst *elem, int end)
{
	static t_lst	*last = NULL;
	static t_lst	*previous = NULL;

	if (elem)
	{
		if (last)
		{
			if (last->num != end)
			{
				last->next = elem;
				if (elem->num == end)
					previous = last;
				last = elem;
			}
			else
			{
				previous->next = elem;
				elem->next = last;
				previous = elem;
			}
		}
		else
			last = elem;
	}
}

void	add_to_ways(t_room_ar *room, int num)
{
	t_lst	*head;

	head = NULL;
	if (room->ways)
	{
		head = room->ways;
		while (head->next)
			head = head->next;
		head->next = queue_elem(num);
	}
	else
		room->ways = queue_elem(num);
}

void	visit_room(t_lem_in *game, t_lst *queue, char *visit)
{
	t_lst	*links;

	links = game->room[queue->num].links;
	while (links)
	{
		if (visit[links->num] == NOT_VISITED)
		{
			visit[links->num] = IN_QUEUE;
			add_to_queue(queue_elem(links->num), game->end);
			add_to_ways(&(game->room[links->num]), queue->num);
		}		
		else if (visit[links->num] == IN_QUEUE)
			add_to_ways(&(game->room[links->num]), queue->num);
		links = links->next;
	}
}

int		lem_in(t_lem_in *game)
{
	char	*visit;
	t_lst	*queue;
	t_lst	*tmp;
	int		ret;

	ret = 1;
	visit = ft_strnew(game->room_num);
	visit = ft_memset(visit, NOT_VISITED, game->room_num);
	queue = queue_elem(game->start);
	add_to_queue(queue, game->end);
	tmp = NULL;
	while (queue)
	{
		visit[queue->num] = VISITED;
		visit_room(game, queue, visit);
		tmp = queue;
		queue = queue->next;
		free (tmp);
	}
	visit = ft_memset(visit, NOT_VISITED, game->room_num);
	if (!find_ways(game, visit))
		ret = 0;
	ft_strdel(&visit);
	clean_lst(&queue);
	return (ret);
}