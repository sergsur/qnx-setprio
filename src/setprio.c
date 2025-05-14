/**
 *******************************************************************************
 *  @file           : setprio.c
 *  @brief          : Priority assignment tool
 *******************************************************************************
 *  @author     Sergey Surazhskyi
 *
 *  @description
 *      Assign specified priority for a specific thread of the process
 *
 * MIT License
 *
 * Copyright (c) 2025 sergsur
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************
 **/

#include <errno.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOK                 0
#define NO_ARGUMENT         0
#define REQUIRED_ARGUMENT   1

#define PID_OPT             'p'
#define PRIORITY_OPT        'r'
#define TID_OPT             't'

#define PID_OPT_STR         "pid"
#define PRIORITY_OPT_STR    "priority"
#define TID_OPT_STR         "tid"

#define HEX_BASE            16
#define DEC_BASE            10

#define log(fmt, type, ...)                                                     \
        do {                                                                    \
                printf("[%s:%d:%s] %s" fmt, __FILE__, __LINE__, __func__,       \
                       type, ## __VA_ARGS__);                                   \
        } while (0);

#define log_info(fmt, ...)  log(fmt, "Inf:", ## __VA_ARGS__)
#define log_err(fmt, ...)   log(fmt, "Err:", ## __VA_ARGS__)
#define log_dbg(fmt, ...)   log(fmt, "Dbg:", ## __VA_ARGS__)

typedef struct {
        int32_t   priority;
        pthread_t pid;
        pthread_t tid;
} ctx_st_t;

static
struct option cmd_options_long[] = {
        {PID_OPT_STR,       REQUIRED_ARGUMENT, NULL, PID_OPT        },
        {PRIORITY_OPT_STR,  REQUIRED_ARGUMENT, NULL, PRIORITY_OPT   },
        {TID_OPT_STR,       REQUIRED_ARGUMENT, NULL, TID_OPT        },
};

static
const char *cmd_options_short = "p:r:t:";

static
inline int str2int(const char *string)
{
        char *x_pos = NULL;
        int value = 0;

        x_pos = strchr(string, 'x');
        if (NULL != x_pos) {
                value = strtol(string, NULL, HEX_BASE);
        } else {
                value = strtol(string, NULL, DEC_BASE);
        }

        return value;
}

static
int parse_arguments(ctx_st_t *ctx, int argc, char *argv[])
{
        int opt = 0;
        int rc = EOK;
        int option_index = 0;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        while (-1 != (opt = getopt_long(argc, argv, cmd_options_short,
                                        cmd_options_long, &option_index))) {
                switch (opt) {
                case PID_OPT:
                        log_info("Process id: %s\n", optarg);

                        ctx->pid = str2int(optarg);

                        break;

                case TID_OPT:
                        log_info("Thread id: %s\n", optarg);

                        ctx->tid = str2int(optarg);

                        break;

                case PRIORITY_OPT:
                        log_info("Priority: %s\n", optarg);

                        ctx->priority = str2int(optarg);

                        break;

                default:
                        log_err("Unsupported option: %d\n", opt);

                        return EINVAL;
                }
        }

        return rc;
}

int main(int argc, char *argv[])
{
        int err = EOK;
        ctx_st_t ctx = {0};

        log_info("setprio running\n");

        err = parse_arguments(&ctx, argc, argv);
        if (EOK != err) {
                log_err("Command parsing failed. Error: %s\n", strerror(err));

                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

