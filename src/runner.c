/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <stdio.h>

#include "init.h"
#include "runner.h"

int run_action(InitSystem init, PowerAction action) {
    if (init == INIT_SYSTEMD) {
        switch (action) {
        case ACTION_SUSPEND:
            puts("using systemctl suspend..");
            run_action(init, action);
            break;

        case ACTION_POWEROFF:
            puts("using systemctl poweroff..");
            run_action(init, action);
            break;

        case ACTION_REBOOT:
            puts("using systemctl reboot..");
            run_action(init, action);
            break;

        default:
            return 1;
        }
    } else if (init == INIT_RUNIT) {
        switch (action) {
        case ACTION_SUSPEND:
            puts("would use zzz");
            run_action(init, action);
            break;

        case ACTION_POWEROFF:
            puts("would use runit init 0");
            run_action(init, action);
            break;

        case ACTION_REBOOT:
            puts("would use runit init 6");
            run_action(init, action);
            break;

        default:
            return 1;
        }
    }

    return 0;
}
