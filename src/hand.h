#ifndef HAND_H
#define HAND_H

#include <card.h>

typedef struct hand
{
    card* cards[5];
    int rank;
} hand;

// function prototypes
hand* find_best_hand(cards* []);

int compare_hands(hand*, hand*);

#endif
