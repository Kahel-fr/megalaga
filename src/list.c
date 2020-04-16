#include "game.h"

t_container		*add_container_to_game()
{
  t_container	*container;

  if ((container = MEM_alloc(sizeof(t_container))) == NULL)
    {
      KLog_U1("Cannot allocate memory for element container ", 1);
      return 0;
    }
  memset(container, 0, sizeof(t_container));
  container->first = NULL;
  container->last = NULL;
  return container;
}

void	add_element_to_container(t_container *container, t_element *element)
{
  t_element	*tmp;
  u8 counter = 1;
  tmp = container->first;
  if (tmp == NULL)
  {
    //KLog//KLog_U1("element added as first in the container ", 1);
    container->first = element;
  }
  else
    {
      //KLog//KLog_U1("element added pos in container = ", counter);
      while (tmp->next != NULL)
    	{
        counter++;
    	  tmp = tmp->next;
    	}
      tmp->next = element;
      element->prev = tmp;
    }
  container->last = element;
}

void   del_element_from_container(t_container *container, t_element *element)
{
  t_element	*elem;
  if (container->first == element)
  {
    container->first = element->next;
    if (element->data)
    {
      //if (((t_entity*)elem->data)->sprite != NULL)
        //SPR_releaseSprite(((t_entity*)elem->data)->sprite);
      MEM_free(element->data);
      element->data = NULL;
    }
    MEM_free(element);
    element = NULL;
    return;
  }
  elem = container->first;

  while (elem != NULL && elem != element)
    elem = elem->next;
  if (elem->next != NULL && elem->prev != NULL)
    {
      elem->next->prev = elem->prev;
      elem->prev->next = elem->next;
    }
  else if (elem->next == NULL)
    {
      elem->prev->next = NULL;
      container->last = elem->prev;
    }
  else if (elem == container->first)
    {
      elem->next->prev = NULL;
      container->first = elem->next;
    }
  if (elem->data)
  {
    // WORKING ON THIS
    /*if (((t_entity*)elem->data)->sprite != NULL)
      SPR_releaseSprite(((t_entity*)elem->data)->sprite);*/
    MEM_free(elem->data);
    elem->data = NULL;
  }
  MEM_free(elem);
  elem = NULL;
}

t_container		*reset_container(t_container *container)
{
  t_element	*elem;
  if (container == NULL)
    return NULL;
  elem = container->first;

  while (elem != NULL)
    {
      t_element *tmp = elem;
      elem = elem->next;
      if (tmp->data)
        MEM_free(tmp->data);
      MEM_free(tmp);
    }
  container->first = NULL;
  container->last = NULL;
  return container;
}

void delete_enemies()
{
  /*for (t_element *tmp = entities->first; tmp != NULL; tmp = tmp->next)
  {
    if (!((t_entity*)tmp->data)->is_player)
      del_element_from_container(entities, tmp);
  }*/
}

t_element	*create_element(void *data)
{
  t_element	*element;
  element = MEM_alloc(sizeof(t_element));
  if (element == NULL)
  {
   //KLog_U1("Cannot allocate memory for element", 1);
    return NULL;
  }
  memset(element, 0, sizeof(t_element));
  element->next = NULL;
  element->prev = NULL;
  element->data = data;
  return element;
}

void display_entities()
{
  /*int i = 0;
  for (t_element *tmp = entities->first; tmp != NULL; tmp = tmp->next)
  {
    t_entity *entity = (t_entity*)tmp->data;
    KLog_U2("Entity no ", i, " = ", entity->id);
    if (tmp->next == NULL)
      KLog_U1("Next pointer is NULL ",  0);
    else
      KLog_U1("Next pointer is OK ",  1);
    if (tmp->prev == NULL)
      KLog_U1("Prev pointer is NULL ",  0);
    else
      KLog_U1("Prev pointer is OK ",  1);
    i++;
  }*/
}

u8 find_max_element_in_container()
{
  /*u8 i = 0;
  u8 res;
  for (t_element *tmp = entities->first; tmp != NULL; tmp = tmp->next)
    i++;
  res = i;
  i = 0;
  for (t_element *tmp = objects->first; tmp != NULL; tmp = tmp->next)
    i++;
  if (i > res)
    res = i;
  i = 0;
  for (t_element *tmp = projectiles->first; tmp != NULL; tmp = tmp->next)
    i++;
  if (i > res)
    res = i;
  return res;*/
  return 0;
}
