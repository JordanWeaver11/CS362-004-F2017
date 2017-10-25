#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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
	int i = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int nextPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state); //deck starts with 7 copper and 3 estates
	//add adventurer card to currentPlayer's hand
	state.hand[currentPlayer][0] = adventurer;
	//make sure that player 2 has cards in his hand
	for (i = 0; i < 5; i++){
		drawCard(nextPlayer, &state);
	}
	//make a copy of the state to compare to
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	
	
	//initialize values to use in cardEffect()
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	playCard(handpos, choice1, choice2, choice3, &state);  //the played adventurer card is discarded!
	
	//test1: exactly 2 treasure cards drawn
	int oldNumTreasures = countTreasure(currentPlayer, &stateOriginal);
	//printf("old num treasures = %d\n", oldNumTreasures);  //DEBUG
	int newNumTreasures = countTreasure(currentPlayer, &state);
	int drawnTreasures = newNumTreasures - oldNumTreasures;
	//printf("new num treasures = %d\n", newNumTreasures);  //DEBUG
	checkEqual(drawnTreasures, 2);
	printf("Number of treasure cards drawn = %d, expected %d\n", drawnTreasures, 2);
	
	//test2: discard all other revealed cards
	//find the number of cards added to the discard pile
	int discardedDrawn = state.discardCount[currentPlayer] - stateOriginal.discardCount[currentPlayer];
	//find the number of cards added to currentPlayer's hand
	int totalDrawn = state.handCount[currentPlayer] - stateOriginal.handCount[currentPlayer];
	//printf("New handcount = %d, old hand count = %d\n", state.handCount[currentPlayer], stateOriginal.handCount[currentPlayer]);  //DEBUG
	//-2 for drawn treasures
	checkEqual(totalDrawn - 2, discardedDrawn);
	printf("Did we discard all other revealed cards (True/False) = %d, expected %d\n", (totalDrawn - 2) == discardedDrawn, 1);
	printf("\tTotal cards discarded = %d, expected %d\n", discardedDrawn, totalDrawn - 2);
	
	//test3: if cards run out, make sure revealed cards are not shuffled into the deck
	//copy original gamestate back into state to re-initialize
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	//setup the game with a deck that will run out, and a non-empty discard pile
	//game automatically starts with 5 in hand, 5 in deck, and 0 in discard
	//draw 4 cards
	for(i = 0; i < 4; i++) {
		drawCard(currentPlayer, &state);
	}
	//discard 4 cards
	for(i = 0; i < 4; i++) {
		discardCard(0, currentPlayer, &state, 0);
	}
	//now 5 cards in hand, 1 card in deck, and 4 in discard
	//add the adventurer card
	state.hand[currentPlayer][0] = adventurer;
	//make a new original copy of the game
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	//play the card
	playCard(handpos, choice1, choice2, choice3, &state);  //the played adventurer card is discarded!
	
	//make sure that the deck count does not become greater than the original discard count
	//find original discard count
	int discardOriginal = stateOriginal.discardCount[currentPlayer];
	//deck size after cardEffect easy to find
	checkEqual((state.deckCount[currentPlayer] > discardOriginal), 0);
	printf("Were revealed cards shuffled back into the deck (True/False) = %d, expected %d\n", state.deckCount[currentPlayer] > discardOriginal, 0);
	
	//test4: only 1 shuffle
	//impossible to test without opening adventurer function
	
	//test5: state stays the same for other players
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
    
    //test6: no change to supply cards
    flag = 0;
	for( i = 0; i < great_hall + 1; i++) {
		if(supplyCount(i, &state) != supplyCount(i, &stateOriginal)) {
			flag = 1;
		}
	}
	checkEqual(flag, 0);
	printf("Were supply cards changed (True/False) = %d, expected %d\n", flag, 0);
	
	printf("DONE testing adventurer card\n\n");
	return 0;
}
