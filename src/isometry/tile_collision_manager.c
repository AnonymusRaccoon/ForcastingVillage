/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** tile collision_managment
*/

#include "tile_collision_manager.h"
#include "map_utils.h"
#include <math.h>

#define INF 10000

bool is_on_segment(gc_vector2 p, gc_vector2 q, gc_vector2 r)
{
    if (q.x <= fmaxf(p.x, r.x) && q.x >= fminf(p.x, r.x) && \
q.y <= fmaxf(p.y, r.y) && q.y >= fminf(p.y, r.y))
        return (true);
    return (false);
}

int orientation(gc_vector2 p, gc_vector2 q, gc_vector2 r)
{
    int tmp = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (tmp == 0)
        return (0);
    return ((tmp > 0) ? 1 : 2);
}

bool gc_vector2_do_intersect(gc_vector2 p1, gc_vector2 q1, \
gc_vector2 p2, gc_vector2 q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return (true);
    if (o1 == 0 && is_on_segment(p1, p2, q1))
        return (true);
    if (o2 == 0 && is_on_segment(p1, q2, q1))
        return (true);
    if (o3 == 0 && is_on_segment(p2, p1, q2))
        return (true);
    if (o4 == 0 && is_on_segment(p2, q1, q2))
        return (true);
    return (false);
}

bool is_point_in_polygon(gc_vector2 *polygon, int n, gc_vector2 p)
{
    gc_vector2 segment = {-INF, p.y};
    int count = 0;
    int next = 0;
    int i = 0;

    if (n < 3)
        return (false);
    do {
        next = (i + 1) % n;
        if (gc_vector2_do_intersect(polygon[i], polygon[next], p, segment)) {
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return (is_on_segment(polygon[i], p, polygon[next]));
            count++;
        }
        i = next;
    } while (i != 0);
    return (count & 1);
}

bool is_pos_in_tile(gc_vector2 pos, struct tile *tile)
{
    struct vertex **c = tile->corners;
    gc_vector2 corners[4];

    pos.y *= -1;
    for (int i = 0; i < 4; i++)
        corners[i] = gc_vector2_from_coords(c[i]->x, c[i]->y, c[i]->z);
    return (is_point_in_polygon(corners, 4, pos));
}