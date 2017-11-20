#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
 * unittest2 tests function whoseTurn()
int whoseTurn(struct gameState *state) {
  return state->whoseTurn;
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

int main() {
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state;
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state);
	
	printf("TESTING whoseTurn():\n");
	//manually change whose turn it is
	//boundary of whoseTurn == 0
	state.whoseTurn = 0;  //player1's turn
	//print pass or fail
	checkEqual(whoseTurn(&state), 0);
	//print useful debugging information
	printf("Player%d turn, expected Player%d turn\n", whoseTurn(&state), 0);
	
	//boundary of whoseTurn > 0
	//boundary of whoseTurn == 0
	state.whoseTurn = 1;  //player2's turn
	//print pass or fail
	checkEqual(whoseTurn(&state), 1);
	//print useful debugging information
	printf("Player%d turn, expected Player%d turn\n", whoseTurn(&state), 1);
	
	//This class never goes past 2 players, so those are sufficient test cases

	printf("DONE testing whoseTurn()\n\n");
	return 0;
}
