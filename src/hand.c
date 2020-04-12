#include <stdio.h>
#include <stdlib.h>
#include <hand.h>
#include <deck.h>

//function prototypes
void sort_ascending(hand* hand);
int is_sorted_ascending(hand* hand);

hand* find_best_hand(card* cards[])
{
    return 0;
}

int compare_hands(hand* hand1, hand* hand2)
{
    //check for flush
    //check for straight    
    //check for 4 of a kind
    //check for 3 of a kind
    //check for pair
    //check for high card
}

int is_flush(hand* hand)
{
    int i;
    fprintf(stderr, "%d", i);
    int first_suit = hand->cards[0]->suit;
    for(i = 1; i < 5; i++)
    {
        if(hand->cards[i]->suit != first_suit) return 0;
    }
    return 1;
}

int is_straight(hand* hand)
{
    sort_ascending(hand);
    int i;
    int current = hand->cards[0]->value;
    for(i = 1; i < 5; i++)
    {
        if(i == 4)
        {
            //check for ace if cards start with 2
            if(hand->cards[4]->value == 13 && hand->cards[0]->value == 2) return 1;
        }
        if(current + 1 != hand->cards[i]->value)
        {
            return 0;
        }
        current = hand->cards[i]->value;
    }
    return 1;
}

void sort_ascending(hand* hand)
{
    if(is_sorted_ascending(hand)) return;
    int i;
    for(i = 0; i < 4; i++)
    {
        if(hand->cards[i]->value > hand->cards[i+1]->value)
        {
            swap(hand->cards, i, i+1);
        }
    }
}

int is_sorted_ascending(hand* hand)
{
    int i;
    for(i = 0; i < 4; i++)
    {
        if(hand->cards[i]->value > hand->cards[i+1]->value) return 0;
    }
    return 1;
}

