#ifndef DECK_H
#define DECK_H

#include <card.h>

typedef struct deck
{
    int current_index;
    card* cards[52];
} deck;

// function prototypes

deck* create_deck(void);

void shuffle_deck(deck*);

card* deal(deck*);

void print_deck(deck*);

void swap(card* A[], int i, int j);

#endif
