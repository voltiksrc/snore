/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "init.h"
#include <stdbool.h>

int run_action(InitSystem init, PowerAction action, bool dry_run);

#endif
