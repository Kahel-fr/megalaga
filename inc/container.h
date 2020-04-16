#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#include "game.h"

typedef struct s_element
{
  void *data;
  struct s_element *next;
  struct s_element *prev;
} t_element;

typedef struct s_container
{
  int		nb_elems;
  t_element	*first;
  t_element	*last;
} t_container;

t_container		*add_container_to_game();
void	         add_element_to_container(t_container *container, t_element *element);
void           del_element_from_container(t_container *container, t_element *element);
t_container		 *reset_container(t_container *container);
t_element	     *create_element(void *data);
u8 find_max_element_in_container();

#endif /*CONTAINER_H__*/
