#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

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

int main() {
	printf("TESTING village card:\n");
	int i = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int nextPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state); //deck starts with 7 copper and 3 estates
	//add village card to currentPlayer's hand
	state.hand[currentPlayer][0] = village;
	//make sure that player 2 has cards in his hand
	for (i = 0; i < 5; i++){
		drawCard(nextPlayer, &state);
	}
	//make a copy of the state to compare to
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	
	//initialize values to use in cardEffect()
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	cardEffect(village, choice1, choice2, choice3, &state, handpos, &bonus);  //the played village card is discarded!
	
	//test1: player gets exactly 1 card
	int oldHandCount = stateOriginal.handCount[currentPlayer];
	int newHandCount = state.handCount[currentPlayer];
	//card comes from players deck
	//other players are not affected
	//add exactly 2 actions to this player's turn
	printf("TESTING village\n");
	return 0;
}
