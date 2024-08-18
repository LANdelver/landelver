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

#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

// helper function to resize dynamic array
static void resize(vector_t *vector) {
    vector->capacity *= 2;
    char **temp = (char **)malloc(vector->capacity * sizeof(char *));
    for (int i = 0; i < vector->size; i++) {
        temp[i] = vector->items[i];
    }
    free(vector->items);
    vector->items = temp;
}

// please create new inventories this way
vector_t new_vector() {
    vector_t vector;
    vector.size = 0;
    vector.capacity = 5;
    vector.items = (char **)malloc(vector.capacity * sizeof(char *));
    return vector;
}

//
char *get_item(vector_t *vector, const int i) {
    if (i >= vector->size) {
        fprintf(stderr, "Error: index out of bounds on vector get_item");
        return NULL;
    }
    return vector->items[i];
}

void set_item(vector_t *vector, const int i, char *item) {
    if (i >= vector->size) {
        fprintf(stderr, "Error: index out of bounds on vector set_item");
        return;
    }
    vector->items[i] = item;
}

void push_back(vector_t *vector, char *item) {
    if (vector->size == vector->capacity) {
        resize(vector);
    }
    vector->items[vector->size] = item;
    vector->size++;
}

char *pop_back(vector_t *vector) {
    if (vector->size > 0) {
        // soft delete method is fine here
        vector->size--;
    }
    return vector->items[vector->size];
}