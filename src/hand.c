#include <stdio.h>
#include <stdlib.h>
#include <hand.h>
#include <deck.h>

//function prototypes
void sort_ascending(hand* hand);
void sort_descending(hand* hand);
int is_sorted_ascending(hand* hand);
int is_sorted_descending(hand* hand);
int compare_values(int hand1_value, int hand2_value);
int is_x_of_a_kind(hand* hand, int x);
int get_pair_value_from_full_house(hand* hand, int three_of_a_kind_value);
int get_lower_pair_value_from_two_pair(hand* hand, int upper_value);
int compare_for_high_card(hand* hand1, hand* hand2);

hand* find_best_hand(card* cards[])
{
    int i, j, k;
    hand* best_hand = malloc(sizeof(hand));
    //initialize best hand to be first 5 cards
    for(i = 0; i < 5; i++)
    {
        best_hand->cards[i] = cards[i];
    }
    for(i = 0; i < 7; i++)
    {
        //i is the first number to be left out
        for(j = 0; j < 7; j++)
        {
            //j is the second number to be left out
            //j cannot be i
            if(i == j) continue;
            int increment = 0; 
            hand* current_hand = malloc(sizeof(hand)); 
            for(k=0; k < 7; k++)
            {
                if(k == i || k == j)
                {
                    increment++;
                    continue;
                }
                current_hand->cards[k-increment] = cards[k];
            }
            if(compare_hands(current_hand, best_hand) == 1)
            {
                *best_hand = *current_hand;
            }
            free(current_hand);
        }
    }
    return best_hand;
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
    if(value1 || value2) return compare_values(value1, value2);

    //check for 4 of a kind
    value1 = is_four_of_a_kind(hand1);
    value2 = is_four_of_a_kind(hand2);
    if(value1 || value2)
    {
        if(value1 == value2)
        {
            //check kickers
            return compare_for_high_card(hand1, hand2);
        }
        return compare_values(value1, value2);
    }

    //check for full house
    value1 = is_full_house(hand1);
    value2 = is_full_house(hand2);
    if(value1 || value2)
    {
        if(value1 == value2)
        {
            return compare_values(get_pair_value_from_full_house(hand1, value1), get_pair_value_from_full_house(hand2, value2));
        }
        return compare_values(value1, value2);
    }

    //check for flush
    value1 = is_flush(hand1);
    value2 = is_flush(hand2);
    if(value1 || value2) return compare_values(value1, value2);

    //check for straight    
    value1 = is_straight(hand1);
    value2 = is_straight(hand2);
    if(value1 || value2) return compare_values(value1, value2);

    //check for 3 of a kind
    value1 = is_three_of_a_kind(hand1);
    value2 = is_three_of_a_kind(hand2);
    if(value1 || value2)
    {
        if(value1 == value2)
        {
            //compare kickers
            return compare_for_high_card(hand1, hand2);
        }
        return compare_values(value1, value2);
    }

    //check for 2 pair
    value1 = is_two_pair(hand1);
    value2 = is_two_pair(hand2);
    if(value1 || value2)
    {
        if(value1 == value2)
        {
            //get lower pair values
            int lower1 = get_lower_pair_value_from_two_pair(hand1, value1);
            int lower2 = get_lower_pair_value_from_two_pair(hand2, value2);
            if(lower1 == lower2)
            {
                return compare_for_high_card(hand1, hand2);
            }
            return compare_values(lower1, lower2);
        }
        return compare_values(value1, value2);
    }

    //check for pair
    value1 = is_pair(hand1);
    value2 = is_pair(hand2);
    if(value1 || value2)
    {
        if(value1 == value2)
        {
            //compare kickers
            return compare_for_high_card(hand1, hand2);
        }
        return compare_values(value1, value2);
    }

    //check for high card
    return compare_for_high_card(hand1, hand2);
}

int compare_for_high_card(hand* hand1, hand* hand2)
{
    sort_descending(hand1);
    sort_descending(hand2);
    int i, result;
    for(i = 0; i < 5; i++)
    {
        result = compare_values(hand1->cards[i]->value, hand2->cards[i]->value);
        if(result) return result; //if result is non zero
    }
    return result; //hands are the same
}

int compare_values(int value1, int value2)
{
    if(value1 > value2) return 1;
    if(value1 < value2) return -1;
    return 0;
}

int is_two_pair_or_better(hand* hand)
{
    if(is_straight_flush(hand) ||
        is_four_of_a_kind(hand) ||
        is_full_house(hand) ||
        is_flush(hand) ||
        is_straight(hand) ||
        is_three_of_a_kind(hand) ||
        is_two_pair(hand)) return 1;
     return 0;
}

int is_royal_flush(hand* hand)
{
    if(is_straight_flush(hand))
    {   
        sort_descending(hand);
        if(hand->cards[0]->value == 14) return 1;
    }
    return 0;
}

int is_pair_or_better(hand* hand)
{
    if(is_straight_flush(hand) ||
        is_four_of_a_kind(hand) ||
        is_full_house(hand) ||
        is_flush(hand) ||
        is_straight(hand) ||
        is_three_of_a_kind(hand) ||
        is_two_pair(hand) ||
        is_pair(hand)) return 1;
     return 0;
}

int is_four_to_a_flush_with_ten_or_better(hand* hand)
{
    int i, j, k;
    //only have to check first 2 cards
    for(i = 0; i < 2; i++)
    {
        int count = 1;
        for(j = i+1; j < 5; j++)
        {
            if(hand->cards[i]->suit == hand->cards[j]->suit) count++;
        }
        if(count == 4)
        {
            //4 to a flush
            //now check for 10 or better of that suit 
            int suit = hand->cards[i]->suit; 
            for(k = 0; k < 5; k++)
            {
                if(hand->cards[k]->value >= 10 && hand->cards[k]->suit == suit) return 1;
            }
        }
    }
    return 0;
}

int is_x_of_a_kind(hand* hand, int x)
{
    int i, j;
    //only have to check first (6 - x) cards
    for(i = 0; i < (6-x); i++)
    {
        int count = 1;
        for(j = i+1; j < 5; j++)
        {
            if(hand->cards[i]->value == hand->cards[j]->value) count++;
        }
        if(count == x) return hand->cards[i]->value;
    }
    return 0;
}

//expects hand to be full house
int get_pair_value_from_full_house(hand* hand, int three_of_a_kind_value)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        if(hand->cards[i]->value != three_of_a_kind_value) return hand->cards[i]->value;
    }
    return -1; //hand is not full house
}

//returns the three_of_a_kind value from full house
int is_full_house(hand* hand)
{
    int three_of_a_kind = is_three_of_a_kind(hand);
    if(!three_of_a_kind) return 0;

    sort_descending(hand);
    int pair = is_pair(hand);

    if(pair == three_of_a_kind)
    {
        sort_ascending(hand);
        pair = is_pair(hand);
    }

    if(pair == three_of_a_kind) return 0;
    
    return three_of_a_kind;
}

int is_pair(hand* hand)
{
    return is_x_of_a_kind(hand, 2);
}

//expects hand to have two pair
int get_lower_pair_value_from_two_pair(hand* hand, int upper_value)
{
    int i, j;
    for(i = 0; i < 5; i++)
    {
        if(hand->cards[i]->value != upper_value)
        {
            int not_upper_value = hand->cards[i]->value;
            for(j = i+1; j < 5; j++)
            {
                if(not_upper_value == hand->cards[j]->value) return not_upper_value;
            }
        }
    }
    return -1; //there was no second pair in hand
}

//returns higher value of two pair
int is_two_pair(hand* hand)
{
    sort_descending(hand);
    int first_pair = is_x_of_a_kind(hand, 2);
    if(first_pair == 0) return 0;

    sort_ascending(hand);
    int second_pair = is_x_of_a_kind(hand, 2);
    if(first_pair == second_pair) return 0;
    
    if(first_pair > second_pair) return first_pair;
    return second_pair;
}

//returns the value of the card that makes 3 of a kind
int is_three_of_a_kind(hand* hand)
{
    return is_x_of_a_kind(hand, 3);
}

//returns the value of the card that makes 4 of a kind
int is_four_of_a_kind(hand* hand)
{
    return is_x_of_a_kind(hand, 4);
}

//returns value of highest card in straight
int is_straight_flush(hand* hand)
{
    int flush_value = is_flush(hand);
    int straight_value = is_straight(hand);
    if(flush_value && straight_value) return straight_value;
    return 0;
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
    return sort_ascending(hand);
}

void sort_descending(hand* hand)
{
    if(is_sorted_descending(hand)) return;
    int i;
    for(i = 0; i < 4; i++)
    {
        if(hand->cards[i]->value < hand->cards[i+1]->value)
        {
            swap(hand->cards, i, i+1);
        }
    }
    return sort_descending(hand);
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

int is_sorted_descending(hand* hand)
{
    int i;
    for(i = 0; i < 4; i++)
    {
        if(hand->cards[i]->value < hand->cards[i+1]->value) return 0;
    }
    return 1;
}

void print_hand(hand* hand)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        print_card(hand->cards[i]);
    }
}
