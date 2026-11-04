/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <stdbool.h>
#include <stdio.h>

#include "detect.h"
#include "init.h"
#include "process.h"
#include "runner.h"

typedef struct {
    const char *program;
    const char *argument;
} Command;

static Command select_command(InitSystem init, PowerAction action) {
    if (init == INIT_SYSTEMD) {
        switch (action) {
        case ACTION_SUSPEND:
            return (Command){"systemctl", "suspend"};
        case ACTION_POWEROFF:
            return (Command){"systemctl", "poweroff"};
        case ACTION_REBOOT:
            return (Command){"systemctl", "reboot"};
        }
    }

    if (init == INIT_RUNIT) {
        switch (action) {
        case ACTION_SUSPEND:
            return (Command){"zzz", NULL};
        case ACTION_POWEROFF:
            return (Command){"init", "0"};
        case ACTION_REBOOT:
            return (Command){"init", "6"};
        }
    }

    return (Command){NULL, NULL};
}

int run_action(InitSystem init, PowerAction action, bool dry_run) {
    Command cmd = select_command(init, action);

    if (cmd.program == NULL) {
        fprintf(stderr, "snore: unsupported init system or action\n");
        return 1;
    }

    if (dry_run) {
        printf("Would execute: %s", cmd.program);

        if (cmd.argument != NULL)
            printf(" %s", cmd.argument);

        putchar('\n');
        return 0;
    }

    const char *path = resolve_program(cmd.program);

    if (path == NULL) {
        fprintf(stderr, "snore: executable not found\n");
        return 1;
    }

    char *args[] = {(char *)cmd.program, (char *)cmd.argument, NULL};

    return run_command(path, args);
}
