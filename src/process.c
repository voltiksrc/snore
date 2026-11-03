/*
 * Copyright (c) 2026 voltik
 * SPDX-License-Identifier: ISC
 */

#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int check_permissions(void) {
    return geteuid() == 0; // 0 for regular user, 1 for root
}

int run_command(const char *program, char *const args[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        execvp(program, args);

        perror("execvp");
        _exit(127);
    }

    int status;

    // Make the parent process wait for the child process so
    // it doesn't skip ahead
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    // Check if waitpid got interrupted by a signal and rerun it if so
    if (errno == EINTR) {
        waitpid(pid, &status, 0);
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return 1;
}
