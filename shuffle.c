#include "shuffle.h"

// You can add more functions to this file.  Helper functions must start with '_'.
#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "utility.c"
// You may add more functions in this file.

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
	//int n=0;
	for (int i = 0; i < orig_deck.size-1; i++){
		upper_deck[i].size = i+1;
		lower_deck[i].size = orig_deck.size - 1 - i;
		for (int x = 0; x < i+1; x++){
			upper_deck[i].cards[x] = orig_deck.cards[x];
		}
		for (int y=0; y < orig_deck.size- 1 - i; y++){
			lower_deck[i].cards[y] = orig_deck.cards[y+i+1];
		}
	}

}
void _recursive(CardDeck u_deck, CardDeck l_deck, CardDeck new_deck, int i_low, int i_up, int k){
	if (i_up == u_deck.size && i_low == l_deck.size){
		//print_deck(new_deck);
		//printf("\n");
		repeat_shuffle(new_deck, (k-1));
	}
	else if(u_deck.size == i_up){
		new_deck.cards[i_up + i_low] = l_deck.cards[i_low];
		_recursive(u_deck, l_deck, new_deck, (i_low+1), i_up, k);
	}
	else if(l_deck.size == i_low){
		new_deck.cards[i_up + i_low] = u_deck.cards[i_up];
		_recursive(u_deck, l_deck, new_deck, i_low, (i_up+1),k);
	}
	else {
		new_deck.cards[i_up + i_low] = u_deck.cards[i_up];
		_recursive(u_deck, l_deck, new_deck, i_low, (i_up+1), k);

		new_deck.cards[i_up + i_low] = l_deck.cards[i_low];
		_recursive(u_deck, l_deck, new_deck, (i_low+1), i_up, k);
	}

}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	//int *arr = malloc(sizeof(int) * lower_deck.size);
	//int tot_size = upper_deck.size + lower_deck.size;
	//
	
/**	CardDeck new_deck = {
		.size = upper_deck.size + lower_deck.size,
		.cards = {0}
	};

	//getIndex(tot_size-1, lower_deck.size-1,arr, upper_deck, lower_deck);
	int i_low = 0;
	int i_up = 0;

	//_recursive(upper_deck, lower_deck, new_deck, i_low, i_up);

	//free(arr);
**/
	return;
}


void shuffle(CardDeck orig_deck) {
	int numpairs = orig_deck.size -1;


	CardDeck * upper_deck = malloc(numpairs * sizeof(CardDeck));
	CardDeck * lower_deck = malloc(numpairs * sizeof(CardDeck));

	// allocate memory
	if (upper_deck == NULL || lower_deck == NULL) {
		free(upper_deck);
		free(lower_deck);
	}



	// call divideDeck to fill upper_deck and lower_deck 
	divide(orig_deck, upper_deck, lower_deck);

	int n = 0;
	while (n < numpairs) {
		// for each pairs call interleave
		interleave(upper_deck[n], lower_deck[n]);
		n++;
	}
	
	free(upper_deck);
	free(lower_deck);

} 
/**
void buildArr(int * arr, CardDeck u_deck, CardDeck l_deck){
	int totSize = u_deck.size + l_deck.size;
	int indexU = 0;
	int indexL = 0;
	char h;
	int c=0;
	CardDeck* finalArr = malloc(sizeof(CardDeck));

	for (int i=0; i<totSize; i++){
		if (i== arr[indexL]){
			finalArr[0].cards[i] = l_deck.cards[indexL];
			indexL++;
		}
		else{
			finalArr[0].cards[i] = u_deck.cards[indexU];
			indexU++;
		}
	}
	for (int x=0; x<totSize; x++){
		h = finalArr[0].cards[x];
		if (h == '\0'){
			c=1;
		}
	}
	if (c!=1){
		print_deck(*finalArr);
	}

void divide(CardDeck orig_deck, CardDeck* upper_deck, CardDeck* lower_deck) {
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
}

void shuffle(CardDeck orig_deck) {
}
**/


void repeat_shuffle(CardDeck orig_deck, int k) {

	if (k<=0){
		printDeck(orig_deck);
		return;
	}

	int i_low = 0;
	int i_up = 0;
	int numpairs = orig_deck.size -1;

	CardDeck new_deck = {
		.size = orig_deck.size,
		.cards = {0}
	};
	
	CardDeck * upper_deck = malloc(numpairs * sizeof(CardDeck));
	CardDeck * lower_deck = malloc(numpairs * sizeof(CardDeck));

	// allocate memory
	if (upper_deck == NULL || lower_deck == NULL) {
		free(upper_deck);
		free(lower_deck);
	}



	// call divideDeck to fill upper_deck and lower_deck 
	divide(orig_deck, upper_deck, lower_deck);
/**
	int n = 0;
	while (n < numpairs) {
		// for each pairs call interleave
		interleave(upper_deck[n], lower_deck[n], k);
		n++;
	}
**/	

	int n =0;
	while (n<numpairs){
		
		_recursive(upper_deck[n], lower_deck[n], new_deck, i_low, i_up, k);
		++n;
	}

	free(upper_deck);
	free(lower_deck);
	
/**	CardDeck new_deck = {
		.size = upper_deck.size + lower_deck.size,
		.cards = {0}
	};
**/
	//getIndex(tot_size-1, lower_deck.size-1,arr, upper_deck, lower_deck);
	//int i_low = 0;
	//int i_up = 0;

//	_recursive(upper_deck, lower_deck, new_deck, i_low, i_up, k);



}
