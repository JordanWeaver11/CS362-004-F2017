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

//asserts that two ints are ==
//returns 0 if assertion is false, 1 if true
int myAssert(int given, int expected) {
	if(given != expected) {
		printf("FAIL: given = %d, expected = %d\n", given, expected);
		return 0;
	}
	return 1;
}

//asserts that two ints are !=
//returns 0 if assertion is false, 1 if true
int myAssertDiff(int given, int expected) {
	if(given == expected) {
		printf("FAIL: given = %d, expected = %d\n", given, expected);
		return 0;
	}
	return 1;
}

/*
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
*/

int main() {
	printf("TESTING village card:\n");
	//p = current player
	int i = 0, p = 0;
	int numPlayers = 2;
	int deckCount, discardCount, handCount, numActions;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	/*
	//set up random number generator
	SelectStream(1);
	PutSeed((long)randomSeed);
	*/
	int randseed = 100;
	//tracks if all tests successful for a given test number (index into array)
	int testFlags[5] = {0, 0, 0, 0, 0};

	
	//initialize values to use in cardEffect()
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	/* Same as smithy test but numActions is also added
	 * Smithy and village card both depend primarily on number of cards
	 * in the player's hand, deck, etc...
	 * The only difference is that the village card also depends on actions
	 */
	for(p = 0; p < 2; p++) {
		int nextPlayer = !p;
		for (numActions = 1; numActions < 3; numActions++) {
		for (deckCount = 0; deckCount < 5; deckCount++) {
		for (discardCount = 0; discardCount < 5; discardCount++) {
		for (handCount = 1; handCount < 5; handCount++) {
			
			//clear game state
			memset(&state, 0, sizeof(struct gameState));
			initializeGame(2, k, randseed, &state);
			//fill deck, discard, and hand with copper
			state.deckCount[p] = deckCount;
			memset(state.deck[p], 4, sizeof(int) * deckCount);
			state.discardCount[p] = discardCount;
			memset(state.discard[p], 4, sizeof(int) * discardCount);
			state.handCount[p] = handCount;
			memset(state.hand[p], 4, sizeof(int) * handCount);
			//set the number of actions
			state.numActions = numActions;
			//add village to currentPlayer's hand
			state.hand[p][0] = village;
			//make a copy of the game state
			memcpy(&stateOriginal, &state, sizeof(struct gameState));
			
			printf("Testing Gamestate: deckCount = %d, handCount = %d, discardCount = %d, numActions: %d\n",
					stateOriginal.deckCount[p], stateOriginal.handCount[p], stateOriginal.discardCount[p], stateOriginal.numActions);
			
			//get ready to play the adventurer card
			state.whoseTurn = p;
			state.phase = 0; //action phase
			playCard(handpos, choice1, choice2, choice3, &state);  //the played adventurer card is discarded!
			
			//TEST1: player gets exactly 1 card
			int oldHandCount = stateOriginal.handCount[p];
			int newHandCount = state.handCount[p];
			//add 1 for the discarded village card
			int drawnCards = (newHandCount - oldHandCount) + 1;
			if(!myAssert(drawnCards, 1)) {
				printf("\tsee test1\n");
				testFlags[0] = 1;
			}
			
			//TEST2: card comes from players deck
			int oldDeckCount = stateOriginal.deckCount[p];
			int newDeckCount = state.deckCount[p];
			//the new deck should have 1 less card than the old deck
			if(!myAssert(oldDeckCount - newDeckCount, 1)) {
				printf("\tsee test2\n");
				testFlags[1] = 1;
			}
			
			//TEST3: other players are not affected
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
			if(!myAssert(flag, 0)) {
				printf("\tsee test3\n");
				testFlags[2] = 1;
			}
			
			//TEST4: no change to supply cards
			flag = 0;
			for( i = 0; i < great_hall + 1; i++) {
				if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
					flag = 1;
				}
			}
			if(!myAssert(flag, 0)) {
				printf("\tsee test4\n");
				testFlags[3] = 1;
			}
			
			//TEST5: add exactly 2 actions to this player's turn
			int oldNumActions = stateOriginal.numActions;
			int newNumActions = state.numActions;
			//after playing the village card, the player will have 2 remaining actions
			//the new number of actions should be 1 greater than the old number of actions
			if(!myAssert(newNumActions - oldNumActions, 1)) {
				printf("\tsee test5\n");
				testFlags[4] = 1;
			}
			
		} //end handCount loop
		} //end discardCount loop
		} //end deckCount loop
		} //end numActions loop
	} //end player loop
	
	//test the "number of actions" boundaries
	
	
	//print overall results
	printf("Summary:\n");
	for(i = 0; i < 5; i++) {
		int failed = testFlags[i];
		if(failed) {
			printf("test #%d FAILED in at least 1 random iteration!\n", i + 1);
		}
		else {
			printf("test #%d PASSED in all random iterations!\n", i + 1);
		}
	}
	
	//test1: player gets exactly 1 card
	//test2: card comes from players deck
	//test3: other players are not affected
	//test4: add exactly 2 actions to this player's turn
	//test5: no change to supply cards
	
	printf("DONE testing village card\n\n");
	return 0;
}
