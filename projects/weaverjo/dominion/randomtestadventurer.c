#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"


//generates a random number between [low, high]
int genRand(int low, int high) {
	if(high == 0) {
		return 0;
	}
	return rand() % (high + 1 - low) + low;
}

//my own delay function
void delay(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while(goal > clock());
}

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

//returns the number of treasure cards in given players hand
int countTreasure(int player, struct gameState *state) {
	int i = 0;
	int numTreasures = 0;
	for(i = 0; i < state->handCount[player]; i++) {
		int currentCard = state->hand[player][i];
		//printf("player %d's card %d\n", player, currentCard);  //DEBUGGING
		if( (currentCard > province) & (currentCard < adventurer) ) {
			numTreasures++;
		}
	}
	return numTreasures;
}

int main() {
	printf("TESTING adventurer card:\n");
	//p = current player
	int i = 0, p = 0, j = 0;
	int numPlayers = 2;
	//treasureXXXCount refers to the number of treasure cards in XXX
	int deckCount, discardCount, handCount, treasureDeckCount, treasureDiscardCount, treasureHandCount, treasureType;
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
    
	/* Things that matter/vary for this card are:
	 * type of treasure cards in hand/deck/discard
	 * number of treasure cards in hand/deck/discard
	 * number of cards in deck/discard
	 */
	srand(time(NULL));
	for(j = 0; j < 100; j++) {
			//clear game state
			memset(&state, 0, sizeof(struct gameState));
			initializeGame(2, k, randseed, &state);
			
			p = genRand(0, 1);
			deckCount = genRand(0, 5);
			treasureDeckCount = genRand(0, deckCount);
			discardCount = genRand(0, 5);
			treasureDiscardCount = genRand(0, discardCount);
			handCount = genRand(1, 5);
			treasureHandCount = genRand(0, handCount);
			treasureType = genRand(copper, gold);
			
			printf("START Testing Gamestate: deckCount = %d, treasureDeckCount = %d, discardCount = %d, treasureDiscardCount = %d\nhandCount = %d, treasureHandCount = %d treasureType = %d, player = %d\n",
					deckCount, treasureDeckCount, discardCount, treasureDiscardCount, handCount, treasureHandCount, treasureType, p);
			
			state.deckCount[p] = deckCount;
			//fill deck with given number and type of treasure cards
			memset(state.deck[p], treasureType, sizeof(int) * treasureDeckCount);
			//fill the rest of the deck with estates
			for(i = treasureDeckCount; i < deckCount; i++) {
				state.deck[p][i] = estate;
			}
			state.discardCount[p] = discardCount;
			//fill the discard deck with given number and type of treasure cards
			memset(state.discard[p], treasureType, sizeof(int) * treasureDiscardCount);
			//fill the rest of the discard with estates
			for(i = treasureDiscardCount; i < discardCount; i++) {
				state.discard[p][i] = estate;
			}
			state.handCount[p] = handCount;
			//fill the hand with the given number and type of treasure cards
			memset(state.hand[p], treasureType, sizeof(int) * treasureHandCount);
			//fill the rest of the hand with estates
			for(i = treasureHandCount; i < handCount; i++) {
				state.hand[p][i] = estate;
			}
			//add village to currentPlayer's hand
			state.handCount[p]++;
			handpos = state.handCount[p] - 1;
			state.hand[p][handpos] = adventurer; //add it to the end of the hand to keep treasure count accurate
			//make a copy of the game state
			memcpy(&stateOriginal, &state, sizeof(struct gameState));
			
			/*
			printf("END Testing Gamestate: deckCount = %d, treasureDeckCount = %d, discardCount = %d, treasureDiscardCount = %d\nhandCount = %d, treasureHandCount = %d treasureType = %d, player = %d\n",
					stateOriginal.deckCount[p], treasureDeckCount, stateOriginal.discardCount[p], treasureDiscardCount, stateOriginal.handCount[p], treasureHandCount, treasureType, p);
			*/
			
			//get ready to play the adventurer card
			state.whoseTurn = p;
			state.phase = 0; //action phase
			
			playCard(handpos, choice1, choice2, choice3, &state);  //the played adventurer card is discarded!
			
			
			//TEST1: exactly 2 treasure cards drawn
			int oldNumTreasures = countTreasure(p, &stateOriginal);
			//printf("old num treasures = %d\n", oldNumTreasures);  //DEBUG
			int newNumTreasures = countTreasure(p, &state);
			int drawnTreasures = newNumTreasures - oldNumTreasures;
			//printf("new num treasures = %d\n", newNumTreasures);  //DEBUG
			if(!myAssert(drawnTreasures, 2)) {
				printf("\tsee test 1\n");
				testFlags[0] = 1;
			}
			
			
			
			//TEST2: discard all other revealed cards
			//find the number of cards added to the discard pile
			int discardedDrawn = state.discardCount[p] - stateOriginal.discardCount[p];
			//find the number of cards added to currentPlayer's hand
			int totalDrawn = state.handCount[p] - stateOriginal.handCount[p];
			//printf("New handcount = %d, old hand count = %d\n", state.handCount[currentPlayer], stateOriginal.handCount[currentPlayer]);  //DEBUG
			//+2 for drawn treasures
			if(!myAssert(totalDrawn, discardedDrawn + 2)) {
				printf("\tsee test2\n");
				testFlags[1] = 1;
			}
			
			
			
			//TEST3: if cards run out, make sure revealed cards are not shuffled into the deck
			//make sure that the deck count does not become greater than the original discard count
			//find original discard count
			int discardOriginal = stateOriginal.discardCount[p];
			int newDiscard = state.deckCount[p];
			if(!myAssert(newDiscard > discardOriginal, 0)) {
				printf("\tsee test3\n");
				testFlags[2] = 1;
			}
			
			
			//TEST4: state stays the same for other players
			int nextPlayer = !p;
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
				printf("\tsee test4\n");
				testFlags[3] = 1;
			}
			
			
			
			//TEST5: no change to supply cards
			flag = 0;
			for( i = 0; i < great_hall + 1; i++) {
				if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
					flag = 1;
				}
			}
			if(!myAssert(flag, 0)) {
				printf("\tsee test5\n");
				testFlags[4] = 1;
			}
			
	
	}
	//debug random number generator
	/*
	int low = 0;
	int high = 0;
	for(i = 0; i < 1000; i++) {
		printf("random number between %d and %d is %d\n", low, high, genRand(low, high));
		//delay(100000);
	}
	*/
	
	//print overall results
	printf("Summary:\n");
	for(i = 0; i < 5; i++) {
		int failed = testFlags[i];
		//int failed = 0;
		if(failed) {
			printf("test #%d FAILED in at least 1 random iteration!\n", i + 1);
		}
		else {
			printf("test #%d PASSED in all random iterations!\n", i + 1);
		}
	}

	printf("DONE testing adventurer card\n\n");
	return 0;
}
