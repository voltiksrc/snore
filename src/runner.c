/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <stdbool.h>
#include <stdio.h>

#include "init.h"
#include "process.h"

int run_action(InitSystem init, PowerAction action, bool dry_run) {
    const char *program = NULL;
    const char *operation = NULL;

    if (init == INIT_SYSTEMD) {
        program = "systemctl";

        switch (action) {
        case ACTION_SUSPEND:
            operation = "suspend";
            break;

        case ACTION_POWEROFF:
            operation = "poweroff";
            break;

        case ACTION_REBOOT:
            operation = "reboot";
            break;

        default:
            return 1;
        }
    } else if (init == INIT_RUNIT) {
        switch (action) {
        case ACTION_SUSPEND:
            program = "zzz";
            break;

        case ACTION_POWEROFF:
            program = "init";
            operation = "0";
            break;

        case ACTION_REBOOT:
            program = "init";
            operation = "6";
            break;

        default:
            return 1;
        }
    } else {
        fprintf(stderr, "snore: unsupported init system\n");
        return 1;
    }

    // Display the selected command without executing it.
    if (dry_run) {
        printf("Would execute: %s %s\n", program, operation ? operation : "");
        return 0;
    }

    return run_command(program, args);
}
