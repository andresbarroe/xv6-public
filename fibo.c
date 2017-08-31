#include "types.h"
#include "stat.h"
#include "user.h"

int
fibo(int n){
    int prevs[2];
    int result = 0, i, j = 0;
    unsigned long long sleep = 0, sleep2;
    sleep2 = sleep = ~sleep;
    prevs[0] = 1;
    prevs[1] = 0;
    for(i = 0; i < n; i++){
        result = prevs[0] + prevs[1];
        prevs[i % 2] = result;

        // correct is wait()
        while(sleep--)
            while(sleep2--)
                j += result * sleep;
        sleep = 0;
        sleep2 = sleep = ~sleep;
    }
    return result;
}

int
main(int argc, char *argv[])
{
    int priority;
    priority = atoi(argv[2]);
    set_priority(priority);
    int n, fib;
    n = atoi(argv[1]);
    fib = fibo(n);
    printf(1, "fibo[%d] = %d\n", n, fib);
    exit();
}
