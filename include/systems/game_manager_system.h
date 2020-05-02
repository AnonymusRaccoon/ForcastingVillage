/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** runner
*/

#ifndef _MAP_MOVEMENT_SYSTEM_H_
#define _MAP_MOVEMENT_SYSTEM_H_

#include "system.h"

struct game_manager_system {
	gc_system base;
	bool is_inventory;
	bool has_message;
};

extern const struct game_manager_system game_manager_system;

#endif //_MAP_MOVEMENT_SYSTEM_H__
