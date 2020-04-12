#ifndef CARD_H
#define CARD_H

typedef struct card
{
    int value;
    int suit;
} card;

// function prototypes

card* create_card(int, int);

void print_card(card*);

#endif
