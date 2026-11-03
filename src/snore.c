/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "init.h"
#include "runner.h"

void help(void) {
    puts("Snore - A useful power controlling utility.\n");

    puts("usage: snore [option] [--dry-run]\n");
    puts("snore -s       Suspend your system");
    puts("snore -p       Poweroff your system");
    puts("snore -r       Reboot your system");
    puts("-h, --help     Show this message");
}

bool parse_action(const char *arg, PowerAction *action) {
    if (strcmp(arg, "-s") == 0)
        *action = ACTION_SUSPEND;
    else if (strcmp(arg, "-p") == 0)
        *action = ACTION_POWEROFF;
    else if (strcmp(arg, "-r") == 0)
        *action = ACTION_REBOOT;
    else
        return false;

    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "snore: missing argument\n");
        return 1;
    }

    bool dry_run = false;
    PowerAction action;
    bool has_action = false;

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
    }

    // Take subcommand arguments rather than multiple executables.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--dry-run") == 0) {
            dry_run = true;
            continue;
        }

        PowerAction parsed;

        if (!parse_action(argv[i], &parsed)) {
            fprintf(stderr, "snore: unknown option '%s'\n", argv[i]);
            return 1;
        }

        if (has_action) {
            fprintf(stderr, "snore: multiple power actions specified\n");
            return 1;
        }

        action = parsed;
        has_action = true;
    }
    InitSystem init = detect_init();

    return run_action(init, action, dry_run);
}
