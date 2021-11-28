#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

/***************************************************************************/
void edge_to_string(const edge_t *edge, char *str, unsigned size)
{
  assert(str != NULL);
  assert(size > 0);

  str[0] = '\0';
}

/***************************************************************************/
bool list_is_empty(const adjacency_list_t *list)
{
  assert(list != NULL);

  return false;
}

/***************************************************************************/
unsigned list_size(const adjacency_list_t *list)
{
  assert(list != NULL);

  return 0;
}

/***************************************************************************/
void list_prepend(adjacency_list_t *list, edge_t *edge)
{
  assert(list != NULL);
  assert(edge != NULL);
}

/***************************************************************************/
bool list_contains(const adjacency_list_t *list, unsigned tail, unsigned head)
{
  assert(list != NULL);

  return false;
}

/***************************************************************************/
bool graph_initialise(graph_t *graph, unsigned vertex_count)
{
  assert(graph != NULL);

  return false;
}

/***************************************************************************/
void graph_print(const graph_t *graph)
{
  assert(graph != NULL);
}

/***************************************************************************/
void graph_release(graph_t *graph)
{
  assert(graph != NULL);
}

/***************************************************************************/
bool
graph_connect(graph_t *graph, unsigned tail, unsigned head, unsigned weight)
{
  assert(graph != NULL);

  return false;
}

/***************************************************************************/
void graph_disconnect(graph_t *graph, unsigned tail, unsigned head)
{
  assert(graph != NULL);
}

/***************************************************************************/
unsigned graph_indegree(const graph_t *graph, unsigned id)
{
  assert(graph != NULL);

  unsigned result = 0;

  if (id < graph->vertex_count)
  {
    for (size_t i=0; i < graph->vertex_count; i++)
    {
      const adjacency_list_t *list = &graph->adjacency_lists[i];

      for (edge_t *edge = list->first; edge != NULL; edge = edge->next)
      {
        if (edge->head == id)
        {
          result++;
        }
      }
    }
  }

  return result;
}

/***************************************************************************/
unsigned graph_outdegree(const graph_t *graph, unsigned id)
{
  assert(graph != NULL);

  return 0;
}

/***************************************************************************/
void graph_build_from_file(graph_t *graph, const char *pathname)
{
  assert(graph != NULL);
  assert(pathname != NULL);

  FILE *fp = fopen(pathname, "r");
  if (fp != NULL)
  {
    unsigned vertex_count;

    if (fscanf(fp, "%u", &vertex_count) == 1)
    {
      if (graph_initialise(graph, vertex_count)) 
      {
        while (! feof(fp))
        {
          unsigned tail;
          unsigned head;
          unsigned weight;

          int n = fscanf(fp, "%u %u %u", &tail, &head, &weight);

          if (! feof(fp))
          {
            if (n == 3)
            {
              if (graph_connect(graph, tail, head, weight))
              {
                fprintf(stderr, "Failed to connect: %d->%d\n", tail, head);
              }
            }
            else
            {
              /* Bad format */
            }
          }
        }
      }
    }
    else
    {
      /* Bad format */
    }

    (void) fclose(fp);
  }
}

/***************************************************************************/
void graph_to_dot(const graph_t *graph, const char *pathname)
{
  assert(graph != NULL);
  assert(pathname != NULL);

  FILE *fp = fopen(pathname, "w");
  if (fp != NULL)
  {
    fprintf(fp, "digraph {\n");

    for (size_t i=0; i < graph->vertex_count; i++)
    {
      const adjacency_list_t *list = &graph->adjacency_lists[i];

      for (edge_t *edge = list->first; edge != NULL; edge = edge->next)
      {
        fprintf(fp, "%d -> %d\n", edge->tail, edge->head);
      }
    }

    fprintf(fp, "}\n");
  }
}
