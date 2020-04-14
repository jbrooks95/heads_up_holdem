#include <stdio.h>
#include <stdlib.h>
#include <card.h>
#include <deck.h>
#include <hand.h>

//function prototypes
int get_post_flop_bet(card* player_cards[], hand* player_hand, int raise_multiplier);
int get_trips_multiplier(hand* player_hand);

int ante = 5;
int trips = 0;
int pocket_bonus = 0;

int simulate(int starting_dollars, int number_of_hands, int print_info)
{
    int number_of_hands_complete = 0;
    int odds = ante;
    int bet3x = ante * 3;
    int current_dollars = starting_dollars;
    deck* d = create_deck();

    hand* player_hand = malloc(sizeof(hand));
    hand* dealer_hand = malloc(sizeof(hand));

    card* player_cards[7];
    card* dealer_cards[7];
    
    int i, j, bet, trips_multiplier, pocket_bonus_multiplier;
    for(int i = 0; i < number_of_hands; i++)
    {
        shuffle_deck(d);
        bet = 0;
        pocket_bonus_multiplier = 0;
        trips_multiplier = 0;

        //return if not enough money
        if(current_dollars < (ante + odds + bet3x)) 
        {
            if(print_info) printf("out of money\n");
            return current_dollars;
        }

        //deal pocket cards
        for(int j = 0; j < 2; j++)
        {
            player_cards[j] = deal(d);
            dealer_cards[j] = deal(d);
        }

        //check player cards for pre-flop raise
        int high_value, low_value, high_suit, low_suit;
        if(player_cards[0]->value > player_cards[1]->value)
        {
            high_value = player_cards[0]->value;
            high_suit = player_cards[0]->suit;
            low_value = player_cards[1]->value;
            low_suit = player_cards[1]->suit;
        }
        else
        {
            high_value = player_cards[1]->value;
            high_suit = player_cards[1]->suit;
            low_value = player_cards[0]->value;
            low_suit = player_cards[0]->suit;
        }

        if(high_value == low_value && high_value > 2) //check for pair bigger than 2s
        {
            if(high_value == 14)
            {
                pocket_bonus_multiplier = 30; //pocket aces
            }
            else
            {
                pocket_bonus_multiplier = 5; //pocket pair
            }

            if(high_value > 2)
            {
                bet = bet3x;
            }
        }
        else if(high_value == 14) //check for ace
        {
            if(low_value == 13 || low_value == 12 || low_value == 11) //ace face
            {
                if(high_suit == low_suit) //ace face suited
                {
                    pocket_bonus_multiplier = 20;
                }    
                else
                {
                    pocket_bonus_multiplier = 10;
                }
            }
            bet = bet3x;
        }
        else if(high_value == 13) //check for king
        {
            if(high_suit == low_suit && low_value >= 5)
            {
                bet = bet3x;
            }   
            else if(low_value >= 7)
            {
                bet = bet3x;
            }
        }
        else if(high_value == 12) //check for queen
        {
            if(high_suit == low_suit && low_value >= 8)
            {
                bet = bet3x;
            }   
            else if(low_value >= 10)
            {
                bet = bet3x;
            }
        }
        else if(high_value == 11 && low_value == 10 && high_suit == low_suit) //check for jack 10 suited
        {
            bet = bet3x;
        }

        //deal flop
        for(int j = 2; j < 5; j++)
        {
            card* current = deal(d);
            player_cards[j] = current;
            dealer_cards[j] = current;
        }

        for(int j = 0; j < 5; j++)
        {
            player_hand->cards[j] = player_cards[j];
        } 

        //check for post-flop raise if bet hasn't already been made
        if(bet == 0)
        {
            bet = get_post_flop_bet(player_cards, player_hand, 2);
        }
        
        //deal turn and river
        for(int j = 5; j < 7; j++)
        {
            card* current = deal(d);
            player_cards[j] = current;
            dealer_cards[j] = current;
        }

        player_hand = find_best_hand(player_cards);
        dealer_hand = find_best_hand(dealer_cards);

        if(bet == 0)
        {
            bet = get_post_flop_bet(player_cards, player_hand, 1);
        }
        
        if(bet == 0 && ante != 0) //fold hand
        {
            current_dollars -= (ante + odds + trips + pocket_bonus);
        }
        else
        {
            int ante_payout = ante;
            int odds_multiplier = 0;
            if(!is_pair_or_better(dealer_hand)) //dealer doesn't qualify
            {
                ante_payout = 0;
            }
            int result = compare_hands(player_hand, dealer_hand);
            if(result == 1) //player wins
            {
                //check for odds payout
                if(is_royal_flush(player_hand)) odds_multiplier = 500;
                else if(is_straight_flush(player_hand)) odds_multiplier = 50;
                else if(is_four_of_a_kind(player_hand)) odds_multiplier = 10;
                else if(is_full_house(player_hand)) odds_multiplier = 3;
                else if(is_flush(player_hand)) odds_multiplier = 2; //actually pays 1.5, fix later
                else if(is_straight(player_hand)) odds_multiplier = 1;

                int win = ((odds*odds_multiplier) + ante_payout + bet);
                current_dollars += win;
            }
            else if(result == -1) //dealer wins
            {
                current_dollars -= (ante_payout + bet + odds);

                //check for bad beat odds payout
                if(is_straight_flush(player_hand)) odds_multiplier = 500;
                else if(is_four_of_a_kind(player_hand)) odds_multiplier = 50;
                else if(is_full_house(player_hand)) odds_multiplier = 10;
                else if(is_flush(player_hand)) odds_multiplier = 8;
                else if(is_straight(player_hand)) odds_multiplier = 5;

                current_dollars += (odds * odds_multiplier);
            }
            //else push
            trips_multiplier = get_trips_multiplier(player_hand);
            current_dollars += (trips * trips_multiplier) + (pocket_bonus * pocket_bonus_multiplier);
            if(trips_multiplier == 0)
            {
                current_dollars -= trips;
            }
            if(pocket_bonus_multiplier == 0)
            {
                current_dollars -= pocket_bonus;
            }
        }
        number_of_hands_complete++;
        if(print_info) printf("current dollars: %d, # of hands: %d\n", current_dollars, i);
    }
    free(player_hand);
    free(dealer_hand);
    return current_dollars;
}

int get_trips_multiplier(hand* player_hand)
{
    if(is_royal_flush(player_hand)) return 100;
    if(is_straight_flush(player_hand)) return 40;
    if(is_four_of_a_kind(player_hand)) return 30;
    if(is_full_house(player_hand)) return 8;
    if(is_flush(player_hand)) return 7;
    if(is_straight(player_hand)) return 4;
    if(is_three_of_a_kind(player_hand)) return 3;
    return 0;
}

//return bet amount
int get_post_flop_bet(card* player_cards[], hand* player_hand, int raise_multiplier)
{
    int bet_amount = ante * raise_multiplier;
    //check for 2 pair or better
    if(is_two_pair_or_better(player_hand))
    {
        return bet_amount;
    }
    //check to four to a flush with 10 or better of that suit
    else if(is_four_to_a_flush_with_ten_or_better(player_hand) && raise_multiplier == 2)
    {
        return bet_amount;
    }
    else
    {
        int number_of_cards = 5; //post flop value
        if(raise_multiplier == 1) number_of_cards = 7; //post turn value
        //check for hidden pair better (better than deuces if raise multiplier is 2x)
        for(int j = 0; j < 2; j++)
        {
            int k; 
            int current_value = player_cards[j]->value; //player_cards maintains original dealing order
            if(current_value == 2 && raise_multiplier != 1) continue; //check for hidden pair better than deuces
        
            for(k = j+1; k < number_of_cards; k++)
            {
                if(current_value == player_cards[k]->value)
                {
                    return bet_amount;
                }
            }
        }
    }
    return 0;
}
