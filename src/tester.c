#include <stdio.h>
#include <stdlib.h>
#include <card.h>
#include <deck.h>
#include <hand.h>
#include <heads_up_holdem.h>

int main()
{

    simulate(20000, 20000);

    return 0;

    deck* d = create_deck();
    shuffle_deck(d);
    //print_deck(d);

    hand* h = malloc(sizeof(hand));
    h->cards[0] = deal(d);
    h->cards[1] = deal(d);
    h->cards[2] = deal(d);
    h->cards[3] = deal(d);
    h->cards[4] = deal(d);

    hand* h1 = malloc(sizeof(hand));
    h1->cards[0] = deal(d);
    h1->cards[1] = deal(d);
    h1->cards[2] = deal(d);
    h1->cards[3] = deal(d);
    h1->cards[4] = deal(d);

    print_hand(h);
    printf("------\n");
    print_hand(h1);
    printf("------\n");
    printf("compare hands: %d\n", compare_hands(h, h1));
    printf("------\n");


    shuffle_deck(d);

    card* cards[7];
    int i;
    for(i = 0; i < 7; i++)
    {
        cards[i] = deal(d);
        print_card(cards[i]);
    }
    printf("------\n");
    printf("find best hand: \n");
    hand* h3 = find_best_hand(cards);
    print_hand(h3);

    return 0;  


    printf("is straight flush %d \n", is_straight_flush(h));
    printf("is four of a kind %d \n", is_four_of_a_kind(h));
    printf("is full house %d \n", is_full_house(h));
    printf("is flush %d \n", is_flush(h));
    printf("is straight %d \n", is_straight(h));
    printf("is three of a kind %d \n", is_three_of_a_kind(h));
    printf("is two pair %d \n", is_two_pair(h));
    printf("is pair %d \n", is_pair(h));

    free(h);
}

