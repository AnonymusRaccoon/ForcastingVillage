/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** movable_system
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "components/movable_component.h"
#include "components/controllable_component.h"
#include "components/controllers/keyboard_controller.h"
#include "components/renderer.h"
#include <stddef.h>

void keyboard_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct controllable_component *con = GETCMP(entity, controllable_component);
    struct keyboard_controller *key = GETCMP(entity, keyboard_controller);

    con->movement_x = 0;
    con->movement_x -= engine->is_keypressed(key->left_key);
    con->movement_x += engine->is_keypressed(key->right_key);
    con->movement_y = 0;
    con->movement_y -= engine->is_keypressed(key->down_key);
    con->movement_y += engine->is_keypressed(key->up_key);
    (void)system;
    (void)dtime;
}


static void ctr(void *system, va_list args)
{
}

const gc_system keyboard_controller_system = {
    name: "keyboard_controller_system",
    component_name: "keyboard_controller",
    size: sizeof(gc_system),
    ctr: &ctr,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &keyboard_update_entity,
    destroy: &system_destroy
};