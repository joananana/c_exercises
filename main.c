#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_COUNT 8

int pin1 = 0x1; // red
int pin2 = 0x2; // green

bool red = false;
bool green = false;

void *scan_keyboard(void *state)
{
    int read_state = 1;
    while (1)
    {
        scanf("%i", &read_state);
        if (read_state == 0) read_state = 1;
        *((int *)state) = read_state;
    }
}

void set_red()
{
    printf("Set, %08x\n", pin1);
    red = true;
}

void reset_red()
{
    printf("Reset, %08x\n", pin1);
    red = false;
}

void set_green()
{
    printf("Set, %08x\n", pin2);
    green = true;
}

void reset_green()
{
    printf("Reset, %08x\n", pin2);
    green = false;
}

int main(void)
{
    // Declare variable for thread's ID:
    // this is to give controls to threads using pthreads functions
    pthread_t id;

    int state = 1;
    int count = 0;

    pthread_create(&id, NULL, scan_keyboard, &state);

    while (1)
    {
        printf("State: ");
        printf("%i\n", state);

        if (count == 0)
        {
            if (red)
            {
                reset_red();
            }
            else
            {
                set_red();
            }
            if (green)
            {
                reset_green();
            }
            else
            {
                set_green();
            }
        }

        count = (count + 1) % (MAX_COUNT / state);
        fflush(stdout);
        usleep(1000000);
    }
}
