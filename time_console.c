#include <stdio.h>
#include <time.h>

int main(void) {
    time_t timer;
    time(&timer);
    printf("Local time is: %s\n", ctime(&timer));
    return 0;
}
