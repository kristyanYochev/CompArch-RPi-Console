#include <rand.h>
#include <delay.h>

#define MULTIPLIER 1664525
#define INCREMENT 1013904223

static int seed = 0;

void rand_init()
{
    seed = get_system_timer();
}

int rand(int min, int max)
{
    seed = MULTIPLIER*seed + INCREMENT;
    return seed % (max - min) + min;
}
