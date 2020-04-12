#include <stdio.h>
#include <stdlib.h>
#include <deck.h>

// function prototypes
void shuffle(card* A[], int n);

deck* create_deck()
{
    deck* d = malloc(sizeof(deck));
    int i, j;
    int suit = 1;
    for(i = 0; i < 52; i++)
    {
        if(i > 13 * suit) suit++;
        d->cards[i] = create_card((i%13)+2, suit);
    }
    return d;
}

void print_deck(deck* d)
{
    int i;
    for(i = 0; i < 52; i++)
    {
        print_card(d->cards[i]);
    }
}

void shuffle_deck(deck* d)
{
	//srand(time(NULL));
    shuffle(d->cards, 52);
}

// Utility function to swap two elements A[i] and A[j] in the array
void swap(card* A[], int i, int j) {
	card* temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// Function to shuffle an array A[] of n elements
void shuffle(card* A[], int n)
{
	// read array from highest index to lowest
	for (int i = n - 1; i >= 1; i--)
	{
		// generate a random number j such that 0 <= j <= i
		int j = rand() % (i + 1);

		// swap current element with randomly generated index
		swap(A, i, j);
	}
}
