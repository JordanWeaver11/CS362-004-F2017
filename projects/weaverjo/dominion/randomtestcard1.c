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

#define TESTCARD "simthy"

int main() {
	printf("TESTING simthy card:\n");
	//p = current player
	int i = 0, p = 0;
	int numPlayers = 2;
	int deckCount, discardCount, handCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	/*
	//set up random number generator
	SelectStream(1);
	PutSeed((long)randomSeed);
	*/
	int randseed = 100;
	//tracks if all tests successful for a given test number (index into array)
	int testFlags[4] = {0, 0, 0, 0};

	
	//initialize values to use in cardEffect()
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	for(p = 0; p < 2; p++) {
		int otherPlayer = !p;
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
			//add smithy to currentPlayer's hand
			state.hand[p][0] = smithy;
			//make a copy of the game state
			memcpy(&stateOriginal, &state, sizeof(struct gameState));
			
			//get ready to play the smithy card
			state.whoseTurn = p;
			state.phase = 0; //action phase
			playCard(handpos, choice1, choice2, choice3, &state);  //the played smithy card is discarded!
			
			//TEST1: current player receives exactly 3 cards
			int oldHandCount = stateOriginal.handCount[p];
			int newHandCount = state.handCount[p];
			//not enough cards to draw
			if((discardCount + deckCount) < 3) {
				if(!myAssert(newHandCount, oldHandCount + discardCount + deckCount - 1)) { //-1 for the discarded smithy card
					printf("\ttest1: deckCount = %d, handCount = %d, discardCount = %d\n",
							stateOriginal.deckCount[p], stateOriginal.handCount[p], stateOriginal.discardCount[p]);
							testFlags[0] = 1;
				}
			}
			//enough cards to draw
			else {
				if(!myAssert(newHandCount, oldHandCount + 2)) { //-1 for the discarded smithy card
				printf("\ttest1: deckCount = %d, handCount = %d, discardCount = %d\n",
						stateOriginal.deckCount[p], stateOriginal.handCount[p], stateOriginal.discardCount[p]);
						testFlags[0] = 1;
				}
			}
			
			//TEST2: cards come from current player's pile
			int newDeckCards = state.deckCount[p];
			int oldDeckCards = stateOriginal.deckCount[p];
			if(!myAssertDiff(newDeckCards, oldDeckCards)) {
				printf("\ttest2: deckCount = %d, handCount = %d, discardCount = %d\n",
						stateOriginal.deckCount[p], stateOriginal.handCount[p], stateOriginal.discardCount[p]);
						testFlags[1] = 1;
				}

			//TEST3: state stays the same for other players
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
			if(!myAssert(flag, 0)) {
				printf("\ttest3: deckCount = %d, handCount = %d, discardCount = %d\n",
						stateOriginal.deckCount[p], stateOriginal.handCount[p], stateOriginal.discardCount[p]);
						testFlags[2] = 1;
				}
			
			//TEST4: no changes to victory cards or kingdom cards
			flag = 0;
			for( i = 0; i < great_hall + 1; i++) {
				if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
					flag = 1;
				}
			}
			if(!myAssert(flag, 0)) {
				printf("\ttest4: deckCount = %d, handCount = %d, discardCount = %d\n",
						stateOriginal.deckCount[p], stateOriginal.handCount[p], stateOriginal.discardCount[p]);
						testFlags[3] = 1;
				}
			
		} //end handCount loop
		} //end discardCount loop
		} //end deckCount loop
	} //end player loop
	
	//print overall results
	printf("Summary:\n");
	for(i = 0; i < 4; i++) {
		int failed = testFlags[i];
		if(failed) {
			printf("test #%d FAILED in at least 1 random iteration!\n", i + 1);
		}
		else {
			printf("test #%d PASSED in all random iterations!\n", i + 1);
		}
	}
	
	printf("DONE testing smithy card\n\n");
	return 0;
}
