#ifndef HAND_H
#define HAND_H

#include <card.h>
#include <deck.h>

typedef struct hand
{
    card* cards[5];
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
int is_four_to_a_flush_with_ten_or_better(hand*);
int is_two_pair_or_better(hand*);
int is_pair_or_better(hand*);
int is_royal_flush(hand*);
void print_hand(hand*);

#endif
