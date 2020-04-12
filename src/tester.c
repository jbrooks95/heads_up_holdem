#include <stdio.h>
#include <stdlib.h>
#include <card.h>
#include <deck.h>
#include <hand.h>

int main()
{
    printf("hey\n");

    card* c1 = create_card(2, 2);
    card* c2 = create_card(13, 2);
    card* c3 = create_card(3, 2);
    card* c4 = create_card(4, 2);
    card* c5 = create_card(2, 2);

    hand* h = malloc(sizeof(hand));
    printf("hey3\n");
    h->cards[0] = c1;
    h->cards[1] = c2;
    h->cards[2] = c3;
    h->cards[3] = c4;
    h->cards[4] = c5;

    int isflush = is_flush(h);
    printf("is flush %d\n", isflush);

    int isstraight = is_straight(h);
    printf("is straight %d\n", isstraight);

    free(h);

    deck* d = create_deck();
    print_deck(d);

    printf("hey\n");
    printf("hey\n");
    printf("hey\n");
    printf("hey\n");
    printf("hey\n");

    shuffle_deck(d);
   // print_deck(d);
}

