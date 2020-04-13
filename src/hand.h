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
int is_straight_flush(hand*);
int is_four_of_a_kind(hand*);
int is_full_house(hand*);
int is_flush(hand*);
int is_straight(hand*);
int is_three_of_a_kind(hand*);
int is_two_pair(hand*);
int is_pair(hand*);
void print_hand(hand*);

#endif
