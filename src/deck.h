#ifndef DECK_H
#define DECK_H

#include <card.h>

typedef struct deck
{
    card* cards[52];
} deck;

// function prototypes

deck* create_deck(void);

void shuffle_deck(deck*);

void print_deck(deck*);

#endif
