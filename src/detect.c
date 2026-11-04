/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <string.h>
#include <unistd.h>

const char *resolve_program(const char *name) {
    if (strcmp(name, "systemctl") == 0) {
        if (access("/run/current-system/sw/bin/systemctl", X_OK) == 0)
            return "/run/current-system/sw/bin/systemctl";

        if (access("/usr/bin/systemctl", X_OK) == 0)
            return "/usr/bin/systemctl";
    }

    return NULL;
}
