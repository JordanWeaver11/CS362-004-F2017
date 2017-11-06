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

//compares two ints and prints PASS if !=, FAIL if ==
void checkDiff(int i, int j) {
	if(i != j) {
		printf("PASS: ");
	}
	else {
		printf("FAIL: ");
	}
}


#define TESTCARD "simthy"

/*
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
	//printf("Number of cards in player 2's hand = %d\n", state.handCount[otherPlayer]);
	//printf("Number of cards in player 1's hand = %d\n", state.handCount[currentPlayer]);
	//make sure that player 2 has cards in his hand
	for (i = 0; i < 5; i++){
		drawCard(otherPlayer, &state);
	}
	//make a copy of the state to compare to
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	
	
	//initialize values to use in cardEffect()
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
     
	//test1: current player receives exactly 3 cards
	playCard(handpos, choice1, choice2, choice3, &state);  //the played smithy card is discarded!
	
	int currHandCards = state.handCount[currentPlayer];
	int originalHandCards = stateOriginal.handCount[currentPlayer];
	//add 1 to account for the discarded smithy card
	int newCards = currHandCards - originalHandCards + 1;
	checkEqual(newCards, 3);
	printf("Number of new cards = %d, expected %d\n", newCards, 3);
	
	//test2: cards come from current player's pile
	int currDeckCards = state.deckCount[currentPlayer];
	int originalDeckCards = stateOriginal.deckCount[currentPlayer];
	checkDiff(originalDeckCards, currDeckCards);
	printf("Did the cards come from the current player's pile (True/False) = %d, expected %d\n", (originalDeckCards != currDeckCards), 1);
	
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
    printf("Was other player's state affected (True/False) = %d, expected %d\n", flag, 0);
    
	//test4: no changes to victory cards or kingdom cards
    flag = 0;
	for( i = 0; i < great_hall + 1; i++) {
		if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
			flag = 1;
		}
	}
	checkEqual(flag, 0);
	printf("Were supply counts changed (True/False) = %d, expected %d\n", flag, 0);
	
	printf("DONE testing smithy card\n\n");
	return 0;
}
*/

int main() {
	printf("TESTING simthy card:\n");
	int i = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int otherPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	//set up random number generator
	SelectStream(1);
	PutSeed((long)randomSeed);
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state);
	//add smithy to currentPlayer's hand
	state.hand[currentPlayer][0] = smithy;
	//make a copy of the state to compare to
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	
	//test1: current player receives exactly 3 cards
	
	
	//test2: cards come from current player's pile
	//test3: state stays the same for other players
	//test4: no changes to victory cards or kingdom cards
	
	printf("DONE testing smithy card\n\n");
	return 0;
}
