#pragma once

#include <unistd.h>
#include <time.h>

extern long long int cycle;

#define CYCLES_SU_COMMON 5
#define SECONDS_PER_CYCLE .0223f

#define SLEEP_FOR_CYCLES(cycles)                         \
{                                                        \
    if (CFG_DBG_EMU_SLOWDOWN == 1)                       \
        usleep(cycles * SECONDS_PER_CYCLE * .125f);        \
}
