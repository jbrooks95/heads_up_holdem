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
    int net_money = 0; 
    int session_count = 10000;
    int hands_per_session = 300;
    int session_starting_money = 400;
    
    int i;
    for(i = 0; i < session_count; i++)
    {
        int session_change = simulate(session_starting_money, hands_per_session, 0) - session_starting_money;
        printf("session change: %d\n", session_change);
        net_money += session_change;
    }
    printf("net money: %d\n", net_money);
    printf("average change per session: %d\n", net_money / session_count);
    return 0;
}
