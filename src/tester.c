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


    card* cards[7];
    cards[0] = create_card(2, 3);
    cards[1] = create_card(14, 2);
    cards[2] = create_card(2, 1);
    cards[3] = create_card(7, 4);
    cards[4] = create_card(11, 2);
    cards[5] = create_card(13, 2);
    cards[6] = create_card(13, 4);
    
    hand* hand = find_best_hand(cards);
    print_hand(hand);
}
