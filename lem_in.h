/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:38 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/07 11:52:41 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "./libft/libft.h"
# define START 1
# define END 2
# define ANTS 0
# define ROOM 3
# define LINK 4
# define VISITED 5
# define NOT_VISITED 6
# define IN_QUEUE 7
# define NOT_FINISHED 8
# define FINISHED 9

typedef struct			s_coord
{
	int					i;
	int					j;
}						t_coord;

typedef struct			s_lst
{
	int					num;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_room_lst
{
	char				*name;
	t_coord				pt;
	int					type;
	struct s_room_lst	*next;
}						t_room_lst;

typedef struct			s_room_ar
{
	char				*name;
	t_coord				pt;
	t_lst				*links;
	t_lst				*ways;
}						t_room_ar;

typedef struct			s_way
{
	int					num;
	int					ant;
	struct s_way		*next;
}						t_way;

typedef struct			s_route
{
	int					steps;
	t_way				*room;
	struct s_route		*next;
}						t_route;

typedef struct			s_bug
{
	int					room;
	int					num;
	t_way				*turn;
}						t_bug;

typedef struct			s_lem_in
{
	int					ants;
	int					room_num;
	int					start;
	int					end;
	int					first;
	t_room_lst			*node;
	t_room_ar			*room;
	t_list				*info;
}						t_lem_in;

void					reading_lem_in(char *line, t_lem_in *game, int *type);
void					error(char *line, char *ptr, t_lem_in *game);
t_lem_in				*create_game(void);
void					add_info(t_lem_in *game, char *ptr);
int						room_valid(char *line, t_lem_in *game, int *type);
int						check_room_str(char *line);
int						check_if_int(char *str);
int						link_valid(char *line, t_lem_in *game, int *type);
int						check_link_str(char *line);
int						ants_valid(char *line, t_lem_in *game, int *type);
int						command_valid(char *line, t_lem_in *game, int *type);
t_room_lst				*create_node(char *line, int *type);
int						add_node_lst(t_room_lst **head, t_room_lst *node);
void					create_room_array(t_lem_in *game);
int						manage_links(t_lem_in *game, char *line);
int						check_links(t_lem_in *game, char *name1, char *name2);
int						add_link(t_room_ar *room, int n1, int n2);
int						check_doubles(t_lem_in *game, int n1, int n2);
void					clean_game(t_lem_in *game);
void					clean_node(t_room_lst *node);
void					clean_room(t_room_ar *room, int room_num);
void					clean_info(t_list *info);
void					clean_lst(t_lst **list);
t_lst					*queue_elem(int num);
void					add_to_queue(t_lst *elem, int end);
void					add_to_ways(t_room_ar *room, int num);
int						lem_in(t_lem_in *game);
void					visit_room(t_lem_in *game, t_lst *queue, char *visit);
int						find_ways(t_lem_in *game, char *visit);
void					add_to_way(t_route **way, t_way *room, int steps);
t_way					*extract_way(t_lem_in *game, int num, char *visit,
						int *steps);
t_way					*create_room(t_lem_in *game, int num, char *visit);
void					clean_room_inway(t_way *head);
int						check_rooms(t_bug *ant, int n, int end);
void					choose_way(t_route *way, t_bug *ant, int *ants,
						int end);
void					move_futher(t_bug *ant);
void					print_moves(t_lem_in *game, t_bug *ant, int ants,
						char *finish);
t_bug					*create_ants(t_lem_in *game);
void					move_ants(t_lem_in *game, t_route *way);
void					clean_way(t_route *way);
#endif
