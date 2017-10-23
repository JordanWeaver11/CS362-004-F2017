#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//compares two ints and prints PASS if equal, FAIL otherwise
void checkEqual(int i, int j) {
	if(i == j) {
		printf("PASS: ");
	}
	else {
		printf("FAIL: ");
	}
}

#define TESTCARD "simthy"

int main() {
	printf("TESTING simthy card:\n");
	int i = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int otherPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state);
	//add smithy to currentPlayer's hand
	state.hand[currentPlayer][0] = smithy;
	//make a copy of the state to compare to
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	
	
	//initialize values to use in cardEffect()
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
     
	//test1: current player receives exactly 3 cards
	cardEffect(smithy, choice1, choice2, choice3, &state, handpos, &bonus);  //the played smithy card is discarded!
	
	int currHandCards = state.handCount[currentPlayer];
	int originalHandCards = stateOriginal.handCount[currentPlayer];
	//add 1 to account for the discarded smithy card
	int newCards = currHandCards - originalHandCards + 1;
	checkEqual(newCards, 3);
	printf("Number of new cards = %d, expected %d\n", newCards, 3);
	
	//test2: 3 cards come from current player's pile
	int currDeckCards = state.deckCount[currentPlayer];
	int originalDeckCards = stateOriginal.deckCount[currentPlayer];
	checkEqual(originalDeckCards - currDeckCards, 3);
	printf("Number of cards drawn from current player's deck = %d, expected %d\n", originalDeckCards - currDeckCards, 3);
	//test3: state stays the same for other players
	int flag = 0;
	
	for (i = 0; i < state.deckCount[otherPlayer]; i++) {
		if(state.deck[otherPlayer][i] != stateOriginal.deck[otherPlayer][i]) {
			flag = 1;
		}
    }
	for (i = 0; i < state.handCount[otherPlayer]; i++) {
		if(state.hand[otherPlayer][i] != stateOriginal.hand[otherPlayer][i]) {
			flag = 1;
		}
    }
   	for (i = 0; i < state.discardCount[otherPlayer]; i++) {
		if(state.discard[otherPlayer][i] != stateOriginal.discard[otherPlayer][i]) {
			flag = 1;
		}
    }
    checkEqual(flag, 0);
    printf("Was other player's state affected = %d, expected %d\n", flag, 0);
    
    flag = 0;
    
	//test4: no changes to victory cards or kingdom cards
	for( i = 0; i < great_hall + 1; i++) {
		if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
			flag = 1;
		}
	}
	checkEqual(flag, 0);
	printf("Were supply counts changed = %d, expected %d\n", flag, 0);
	return 0;
}
