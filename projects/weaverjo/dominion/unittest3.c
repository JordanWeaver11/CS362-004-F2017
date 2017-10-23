#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
 * unitttest3 tests isGameOver() function
int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
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
	printf("TESTING isGameOver():\n");
	/* Realistically, none of the supply cards should ever become negative.
	 * So I and only going to test positive and 0 boundary conditions.
	 */
	
	//manually set province and supply card values because they are used in isGameOver()
	int i = 0;
	
	//boundary where province > 0, but 3 supply cards == 0
	for(i = 0; i < smithy + 1; i++) {
		state.supplyCount[i] = 8;
	}
	state.supplyCount[village] = 0;
	state.supplyCount[baron] = 0;
	state.supplyCount[great_hall] = 0;
	checkEqual(isGameOver(&state), 1);
	printf("Province > 0, 3 supply cards == 0. Game over %d, expected Game over %d\n", isGameOver(&state), 1);
	
	//boundary where province == 0, but 3 supply cards > 0
	for(i = 0; i < great_hall + 1; i++) {
		state.supplyCount[i] = 8;
	}
	state.supplyCount[province] = 0;
	checkEqual(isGameOver(&state), 1);
	printf("Province == 0, 3 supply cards > 0. Game over %d, expected Game over %d\n", isGameOver(&state), 1);
	
	//boundary where province > 0, but 1 supply cards == 0
	for(i = 0; i < baron + 1; i++) {
		state.supplyCount[i] = 8;
	}
	state.supplyCount[great_hall] = 0;
	checkEqual(isGameOver(&state), 0);
	printf("Province > 0, 1 supply cards == 0. Game over %d, expected Game over %d\n", isGameOver(&state), 0);
	
	/*make sure isGameOver() only checks the used kingdom cards
	 * use ambassador instead of great_hall
	 */
	int k2[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, ambassador};
	struct gameState state2;
	//initialize everything in a new gamestate for ease
	initializeGame(numPlayers, k2, randseed, &state2);
	//province > 0, and used supply cards > 0, 3 unused supply cards == 0
	for(i = 0; i < baron + 1; i++) {
		state2.supplyCount[i] = 8;
	}
	state2.supplyCount[ambassador] = 8;
	//set 3 unused supply cards to 0
	state2.supplyCount[great_hall] = 0;
	state2.supplyCount[minion] = 0;
	state2.supplyCount[steward] = 0;
	
	checkEqual(isGameOver(&state), 0);
	printf("Province > 0, 3 used supply cards > 0, 3 unused supply cards == 0.\n");
	printf("   Game over %d, expected Game over %d\n", isGameOver(&state), 0);
	
	printf("DONE testing isGameOver()\n\n");
	return 0;
}
