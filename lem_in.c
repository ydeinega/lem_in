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
	elem.num = num;
	elem.next = NULL;
	return (elem);
}

void	add_to_queue(t_lst *elem)
{
	static t_lst	*last = NULL;

	if (elem)
	{
		if (last)
			last->next = elem;
		last = elem;
	}
}

int		lem_in(t_lem_in *game)
{
	char	*visit;
	t_lst	*queue;
	t_lst	*tmp;
	t_lst	*links;

	visit = ft_strnew(game->room_num);
	visit = ft_memset(visit, NOT_VISITED, game->room_num);
	queue = queue_elem(game->start);
	tmp = NULL;
	while (queue)
	{
		//здесь в самом начале нужно поменять статус на ВИЗИТЕД
		links = game->room[queue->num].links;
		while (links)
		{
			if (visit[links->num] == NOT_VISITED)
				//мы записываем его в очередь и записываем в вэйс, откуда мы пришли
				//при этом мы меняем состояние на В_ОЧЕРЕДИ
			if (visit[links->num] == IN_QUEUE)
				//мы записываем в вэйс откуда мы пришли

			links = links->next;
		}
		tmp = queue;
		queue = queue->next;
		free (tmp);
	}
	ft_strdel(&visit);
	//clean_queue(queue);
}