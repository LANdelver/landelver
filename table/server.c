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

#include <Python.h>
#include <pthread.h>
#include <stdio.h>
#include "server.h"

static void* run_python_script(void* arg) {
    const char* filename = (const char*)arg;

    // Initialize the Python interpreter
    Py_Initialize();

    if (!Py_IsInitialized()) {
        fprintf(stderr, "Failed to initialize Python interpreter\n");
        pthread_exit(NULL);
    }

    // Add the current directory to the Python path (if your script is in the current directory)
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");

    // Open and execute the Python script file
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        Py_Finalize();
        pthread_exit(NULL);
    }

    PyRun_SimpleFile(fp, filename);
    fclose(fp);

    // Finalize the Python interpreter
    Py_Finalize();

    pthread_exit(NULL);
}

void start_websocket_server() {
    const char* filename = "server/server.py";

    // Create a thread to run the Python script
    pthread_t python_thread;
    if (pthread_create(&python_thread, NULL, run_python_script, (void*)filename)) {
        fprintf(stderr, "Error creating thread\n");
        return;
    }
}
