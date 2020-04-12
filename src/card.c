#include <stdlib.h>
#include <stdio.h>
#include <card.h>

card* create_card(int value, int suit)
{
    if(value < 1 || value > 13)
    {
        return NULL;
    }

    if(suit < 1 || suit > 4)
    {
        return NULL;
    }

    card* c = malloc(sizeof(card));
    c->value = value;
    c->suit = suit;    
    return c;
}

void print_card(card* c)
{
    switch(c->value)
    {
        case 1:
            printf("value: A\n");
            break;
        case 13:
            printf("value: K\n");
            break;
        case 12:
            printf("value: Q\n");
            break;
        case 11:
            printf("value: J\n");
            break;
        default:
            printf("value: %d\n", c->value);
            
    }       
    printf("suit: %d\n\n", c->suit);
}
