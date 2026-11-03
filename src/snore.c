/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "init.h"
#include "runner.h"

void help(void) {
    puts("Snore - A useful power controlling utility.\n");

    puts("usage: snore [option]\n");
    puts("snore -s       Suspend your system");
    puts("snore -p       Poweroff your system");
    puts("snore -r       Reboot your system");
    puts("-h, --help     Show this message");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "snore: missing argument\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "snore: too many arguments\n");
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
    }

    InitSystem init = detect_init();

    // Take subcommand arguments rather than multiple executables.
    if (strcmp(argv[1], "-s") == 0) {
        return run_action(init, ACTION_SUSPEND);
    } else if (strcmp(argv[1], "-p") == 0) {
        return run_action(init, ACTION_POWEROFF);
    } else if (strcmp(argv[1], "-r") == 0) {
        return run_action(init, ACTION_REBOOT);
    } else {
        fprintf(stderr, "Unknown subcommand '%s'\n", argv[1]);
        return 1;
    }

    return 0;
}
