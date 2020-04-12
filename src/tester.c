#include <stdio.h>
#include <card.h>
#include <deck.h>

int main()
{
    printf("hey\n");
    card* c = create_card(11, 1);
    print_card(c);

    deck* d = create_deck();
    print_deck(d);

    printf("hey\n");
    printf("hey\n");
    printf("hey\n");
    printf("hey\n");
    printf("hey\n");

    shuffle_deck(d);
    print_deck(d);
}

