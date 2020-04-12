#include <stdio.h>
#include <stdlib.h>
#include <hand.h>
#include <deck.h>

//function prototypes
void sort_ascending(hand* hand);
int is_sorted_ascending(hand* hand);
int compare_hand_values(int hand1_value, int hand2_value);

hand* find_best_hand(card* cards[])
{
    return 0;
}

//returns 1 if hand1 > hand2
//returns -1 if hand2 > hand1
//returns 0 if hand1 = hand2
//this function does things twice for simplicity and readability
int compare_hands(hand* hand1, hand* hand2)
{
    //check for straight flush
    int value1 = is_straight_flush(hand1);
    int value2 = is_straight_flush(hand2);
    if(value1 || value2) return compare_hand_values(value1, value2);

    //check for 4 of a kind
    //check for full house
    //check for flush
    //check for straight    
    //check for 3 of a kind
    //check for 2 pair
    //check for pair
    //check for high card
}

//return 1 if hand1 > hand2
//return -1 if hand2 > hand1
//return 0 if hand1 = hand2
int compare_hand_values(int hand1_value, int hand2_value)
{
    if(hand1_value > hand2_value) return 1;
    else if(hand1_value < hand2_value) return -1;
    else return 0;
}

int is_four_of_a_kind(hand* hand)
{
    int first = hand->cards[0]->value;
    int second = hand->cards[1]->value;
    int i;
    int count = 1;
    for(i = 1; i < 5; i++)
    {
        if(hand->cards[i]->value == first) count++;
    }

    if(count == 4) return first;

    count = 1;
    for(i = 2; i < 5; i++)
    {
        if(hand->cards[i]->value == second) count++;
    }

    if(count == 4) return second;

    return 0;
}

//returns value of highest card in straight
int is_straight_flush(hand* hand)
{
    int flush_value = is_flush(hand);
    int straight_value = is_straight(hand);
    if(flush_value && straight_value) return straight_value;
    else return 0;
}

//returns value of highest card in flush
int is_flush(hand* hand)
{
    sort_ascending(hand);
    int i;
    int first_suit = hand->cards[0]->suit;
    for(i = 1; i < 5; i++)
    {
        if(hand->cards[i]->suit != first_suit) return 0;
    }
    return hand->cards[4]->value;
}

//returns value of highest card in straight
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
            if(hand->cards[4]->value == 13 && hand->cards[0]->value == 2) return 5;
        }
        if(current + 1 != hand->cards[i]->value)
        {
            return 0;
        }
        current = hand->cards[i]->value;
    }
    return hand->cards[4]->value;
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

