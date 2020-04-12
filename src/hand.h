#ifndef HAND_H
#define HAND_H

#include <card.h>
#include <deck.h>

typedef struct hand
{
    card* cards[5];
    int rank;
} hand;

// function prototypes
hand* find_best_hand(card* []);

int compare_hands(hand*, hand*);
int is_flush(hand*);
int is_straight(hand*);

#endif
