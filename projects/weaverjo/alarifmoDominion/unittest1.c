#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
 * Unittest1 tests the supplyCount() function
	int supplyCount(int card, struct gameState *state) {
	  return state->supplyCount[card];
	}
*/

//compares two ints and prints PASS if equal, FAIL otherwise
void checkEqual(int i, int j) {
	if(i == j) {
		printf("PASS: ");
	}
	else {
		printf("FAIL: ");
	}
}

//takes an enum value and returns the enumerated value as a string
const char* getCardNameE(enum CARD card) {
	switch(card) {
		case curse: return "Curse";
		case duchy: return "Duchy";
		case province: return "Province";
		case copper: return "Copper";
		case silver: return "Silver";
		case gold: return "Gold";
		case adventurer: return "Adventurer";
		case council_room: return "Council Room";
		case feast: return "Feast";
		case gardens: return "Gardens";
		case mine: return "Mine";
		case remodel: return "Remodel";
		case smithy: return "Smithy";
		case village: return "Village";
		case baron: return "Baron";
		case great_hall: return "Great Hall";
	}
	return "Invalid card";
}

//takes an int and returns the corresponding enumerated value as a string
const char* getCardNameI(int cardNum) {
	switch(cardNum) {
		case 0: return "Curse";
		case 1: return "Duchy";
		case 2: return "Province";
		case 3: return "Copper";
		case 4: return "Silver";
		case 5: return "Gold";
		case 6: return "Adventurer";
		case 7: return "Council Room";
		case 8: return "Feast";
		case 9: return "Gardens";
		case 10: return "Mine";
		case 11: return "Remodel";
		case 12: return "Smithy";
		case 13: return "Village";
		case 14: return "Baron";
		case 15: return "Great Hall";
	}
	return "Invalid card";
}

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state;
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state);
	
	//now explicitly set the number of cards in supply for every kind of card
	int i = 0;
	
	//boundary where supplycount > 0
	printf("TESTING supplyCount():\n");
	for(i = 0; i < great_hall + 1; i++) { //all cards use range from 0 to great_hall
		state.supplyCount[i] = 1;
		//print pass or fail
		checkEqual(supplyCount(i, &state), 1);
		//print useful debugging stuff
		printf("Supply count of card %s: %d, expected: %d\n", getCardNameI(i), supplyCount(i, &state), 1);
	}
	//boundary where supplycount == 0
	for(i = 0; i < great_hall + 1; i++) { //all cards use range from 0 to great_hall
		state.supplyCount[i] = 0;
		//print pass or fail
		checkEqual(supplyCount(i, &state), 0);
		//print usefule debugging stuff
		printf("Supply count of card %s: %d, expected: %d\n", getCardNameI(i), supplyCount(i, &state), 0);
	}
	//boundary where supplycount < 0 (supplyCount should never go < 0, but we can test it anyway)
	for(i = 0; i < great_hall + 1; i++) { //all cards use range from 0 to great_hall
		state.supplyCount[i] = -1;
		//print pass or fail
		checkEqual(supplyCount(i, &state), -1);
		//print useful debugging stuff
		printf("Supply count of card %s: %d, expected: %d\n", getCardNameI(i), supplyCount(i, &state), -1);
	}
	
	printf("DONE testing supplyCount()\n\n");
	return 0;
}
