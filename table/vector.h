/*
Copyright (C) 2024 Lance Borden, Sariah Echols

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3.0
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.

*/

typedef struct {
    char **items;
    int size;
    int capacity;
} vector_t;

vector_t vector_new();

char *vector_get_item(vector_t *vector, const int i);

void vector_set_item(vector_t *vector, const int i, char *item);

void vector_push_back(vector_t *vector, char *item);

char *vector_pop_back(vector_t *vector);

void vector_delete(vector_t *vector);