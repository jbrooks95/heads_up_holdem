#include <stdio.h>
#include <stdlib.h>
#include <card.h>
#include <deck.h>
#include <hand.h>
#include <time.h>
#include <heads_up_holdem.h>

int main()
{
    srand(time(NULL));
    simulate(200, 100);
    return 0;
}
