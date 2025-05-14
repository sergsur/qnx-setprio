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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
{
        log_info("setprio running\n");

        return EXIT_SUCCESS;
}

