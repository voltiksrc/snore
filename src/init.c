/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <stdio.h>
#include <string.h>

#include "init.h"

InitSystem detect_init(void) {
    FILE *init;
    char name[64];

    // Open proc comm because it holds the name of the running init system
    init = fopen("/proc/1/comm", "r");

    if (init == NULL) {
        perror("fopen");
        return 1;
    }

    // Attempt to read the name of the init system, but close the
    // file and return if it isn't able to read it.
    if (fgets(name, sizeof(name), init) == NULL) {
        fclose(init);
        return 1;
    }

    fclose(init);
    // Remove the newline
    name[strcspn(name, "\n")] = '\0';

    if (strcmp(name, "systemd") == 0) {
        return INIT_SYSTEMD; // return our init systemd enum
    } else if (strcmp(name, "runit") == 0) {
        return INIT_RUNIT;
    } else {
        return INIT_UNKNOWN;
    }
}
