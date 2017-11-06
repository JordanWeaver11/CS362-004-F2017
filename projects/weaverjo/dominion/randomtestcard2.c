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
	playCard(handpos, choice1, choice2, choice3, &state);  //the played village card is discarded!
	
	//test1: player gets exactly 1 card
	int oldHandCount = stateOriginal.handCount[currentPlayer];
	int newHandCount = state.handCount[currentPlayer];
	//add 1 for the discarded village card
	int drawnCards = (newHandCount - oldHandCount) + 1;
	checkEqual(drawnCards, 1);
	printf("Player drew exactly %d card, expected %d\n", drawnCards, 1);
	
	//test2: card comes from players deck
	int oldDeckCount = stateOriginal.deckCount[currentPlayer];
	int newDeckCount = state.deckCount[currentPlayer];
	//the new deck should have 1 less card than the old deck
	checkEqual(oldDeckCount - newDeckCount, 1);
	printf("Card came from the player's deck (True/False) = %d, expected %d\n", (oldDeckCount - newDeckCount) == 1, 1);
	
	//test3: other players are not affected
	int flag = 0;
	
	for (i = 0; i < state.deckCount[nextPlayer]; i++) {
		if(state.deck[nextPlayer][i] != stateOriginal.deck[nextPlayer][i]) {
			flag = 1;
		}
    }
	for (i = 0; i < state.handCount[nextPlayer]; i++) {
		if(state.hand[nextPlayer][i] != stateOriginal.hand[nextPlayer][i]) {
			flag = 1;
		}
    }
   	for (i = 0; i < state.discardCount[nextPlayer]; i++) {
		if(state.discard[nextPlayer][i] != stateOriginal.discard[nextPlayer][i]) {
			flag = 1;
		}
    }
    checkEqual(flag, 0);
    printf("Was other player's state affected (True/False) = %d, expected %d\n", flag, 0);
    
	//test4: add exactly 2 actions to this player's turn
	int oldNumActions = stateOriginal.numActions;
	int newNumActions = state.numActions;
	//after playing the village card, the player will have 2 remaining actions
	//the new number of actions should be 1 greater than the old number of actions
	checkEqual(newNumActions - oldNumActions, 1);
	printf("Village added %d actions to current players turn, expected %d actions added\n", (newNumActions - oldNumActions) + 1, 2);
	
    //test5: no change to supply cards
    flag = 0;
	for( i = 0; i < great_hall + 1; i++) {
		if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
			flag = 1;
		}
	}
	checkEqual(flag, 0);
	printf("Were supply cards changed (True/False) = %d, expected %d\n", flag, 0);
	
	printf("DONE testing village\n\n");
	return 0;
}
