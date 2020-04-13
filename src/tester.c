#include <stdio.h>
#include <stdlib.h>
#include <card.h>
#include <deck.h>
#include <hand.h>

int main()
{
    printf("hey\n");

    card* c1 = create_card(3, 2);
    card* c2 = create_card(3, 2);
    card* c3 = create_card(4, 2);
    card* c4 = create_card(4, 2);
    card* c5 = create_card(3, 2);

    hand* h = malloc(sizeof(hand));
    h->cards[0] = c1;
    h->cards[1] = c2;
    h->cards[2] = c3;
    h->cards[3] = c4;
    h->cards[4] = c5;

    printf("is straight flush %d \n", is_straight_flush(h));
    printf("is four of a kind %d \n", is_four_of_a_kind(h));
    printf("is three of a kind %d \n", is_three_of_a_kind(h));
    printf("is two pair %d \n", is_two_pair(h));
    printf("is flush %d \n", is_flush(h));
    printf("is straight %d \n", is_straight(h));

    free(h);

    deck* d = create_deck();
    //print_deck(d);

    printf("hey\n");
    printf("hey\n");
    printf("hey\n");
    printf("hey\n");
    printf("hey\n");

    shuffle_deck(d);
   // print_deck(d);
}

