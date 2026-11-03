/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#ifndef INIT_H
#define INIT_H

typedef enum { INIT_SYSTEMD, INIT_RUNIT, INIT_UNKNOWN } InitSystem;

typedef enum { ACTION_SUSPEND, ACTION_POWEROFF, ACTION_REBOOT } PowerAction;

InitSystem detect_init(void);

#endif
