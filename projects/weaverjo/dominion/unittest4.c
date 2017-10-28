#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
/*
 * unittest4 tests the fullDeckCount() function.
 * fullDeckCount() counts the number of a specific card in a specific player's
 * hand, deck, and discard pile.
 * 
int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
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
	printf("TESTING fullDeckCount():\n");
	
	//if boundary cases pass for 1 type of card, then it should pass for all other types of cards.
	int i = 0;
	int player = 0;
	//test 1: card cound == 0
	//fill deck and hand with adventurer
	for (i = 0; i < state.deckCount[player]; i++) {
		state.deck[player][i] = adventurer;
    }
	for (i = 0; i < state.handCount[player]; i++) {
		state.hand[player][i] = adventurer;
    }
    //check for council_room
    checkEqual(fullDeckCount(player, council_room, &state), 0);
    printf("deck contains %d council_room, expected %d\n", fullDeckCount(player, council_room, &state), 0);
	
	
	//test 2: card count == 1, 1 in deck, 0 in hand, 0 in discard
	state.deck[player][0] = council_room;
    //check for council_room
    checkEqual(fullDeckCount(player, council_room, &state), 1);
    printf("deck contains %d council_room, expected %d\n", fullDeckCount(player, council_room, &state), 1);
    
    //test 3: card count == 1, 0 in deck, 1 in hand, 0 in discard
    state.deck[player][0] = adventurer;
    state.hand[player][0] = council_room;
    //check for council_room
    checkEqual(fullDeckCount(player, council_room, &state), 1);
    printf("deck contains %d council_room, expected %d\n", fullDeckCount(player, council_room, &state), 1);
    
    //test4: card count == 1, 0 in deck, 0 in hand, 1 in discard
    state.hand[player][0] = adventurer;
    state.discardCount[player] += 1;
    state.discard[player][0] = council_room;
    //check for council_room
    checkEqual(fullDeckCount(player, council_room, &state), 1);
    printf("deck contains %d council_room, expected %d\n", fullDeckCount(player, council_room, &state), 1);
    
    //test5: card count == 3, 1 in deck, 1 in hand, 1 in discard
    state.hand[player][0] = council_room;
    state.deck[player][0] = council_room;
    //check for council_room
    checkEqual(fullDeckCount(player, council_room, &state), 3);
    printf("deck contains %d council_room, expected %d\n", fullDeckCount(player, council_room, &state), 3);
    
	printf("DONE testing fullDeckCount\n\n");
	return 0;
}
