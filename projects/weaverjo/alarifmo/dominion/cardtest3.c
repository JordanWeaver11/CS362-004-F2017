#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

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

//takes a specific card number, finds how many of that card is in player's hand
int cardHandCount(int player, int card, struct gameState *state) {
	int i = 0;
	int count;
	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == card) count++;
	}
    return count;
}

//prints out the enum value for each card in player's hand
void printHand(int player, struct gameState *state) {
	int i = 0;
	for(i = 0; i < state->handCount[player]; i++) {
		printf("player%d's card %d is %d\n", player, i, state->hand[player][i]);
	}
}

int main() {
	printf("TESTING mine card:\n");
	int i = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int nextPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state, stateOriginal;
	int randseed = 100;
	//initialize everything in a base gamestate
	initializeGame(numPlayers, k, randseed, &state); //deck starts with 7 copper and 3 estates
	//make sure that player 2 has cards in his hand
	for (i = 0; i < 5; i++){
		drawCard(nextPlayer, &state);
	}
	//add mine card to currentPlayer's hand
	state.hand[currentPlayer][0] = mine;
	//set treasure card at handpos1
	state.hand[currentPlayer][1] = copper;
	//set estate at handpos2
	state.hand[currentPlayer][2] = estate;

	//test1: error if no treasure card in hand---------------------------------------------------------------

	//make a copy of the state to compare to
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	/* initialize values to use in cardEffect()
	 * choice1 = card to trash, choice1 is a handpos for the card to discard
	 * choice2 = treasure card to take from supply
	 */
	//choice1 = 2 chooses the estate at handpos2 to trash
    int handpos = 0, choice1 = 2, choice2 = silver, choice3 = 0, bonus = 0;
    //the played mine card is discarded!
	int ret = playCard(handpos, choice1, choice2, choice3, &state);
	checkEqual((ret < 0), 1);
	printf("return value from cardEffect if trashing something other than treasure = %d\n", ret);
	printf("\texpected < %d (error value)\n", 0);

	//test2: the trashed card is a treasure card from the player's hand-----------------------------------------
	//refresh state
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	/* initialize values to use in cardEffect()
	 * choice1 = card to trash, choice1 is a handpos for the card to discard
	 * choice2 = treasure card to take from supply
	 */
	//choice1 = 1 chooses the copper at at handpos1 to trash
    handpos = 0, choice1 = 1, choice2 = silver, choice3 = 0, bonus = 0;
    playCard(handpos, choice1, choice2, choice3, &state);
    //number of copper cards in old hand
    int oldCopper = cardHandCount(currentPlayer, copper, &stateOriginal);
    //number of copper cards in new hand
    int newCopper = cardHandCount(currentPlayer, copper, &state);
	//printf("oldCopper: %d\n", oldCopper);  //DEBUG
	//printf("newCopper: %d\n", newCopper);  //DEBUG
	checkEqual(oldCopper - newCopper, 1);
	printf("The trashed card is a treasure card and came from player's hand");
	printf("(True/False) = %d, expected %d\n", (oldCopper - newCopper) == 1, 1);
	
	//test3: the used card is trashed, not discarded---------------------------------------------------------------
	//discardcount should not change either to ensure card was trashed
	int oldDiscard = stateOriginal.discardCount[currentPlayer];
	int newDiscard = state.discardCount[currentPlayer];
    checkEqual(oldDiscard, newDiscard);
    printf("the used card is trashed, not discarded (True/False) = %d, expected %d\n", (oldDiscard == newDiscard), 1);
    
	//test3: no error if treasure card taken costs exactly 3 more--------------------------------------------------------
	//refresh state
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	/* initialize values to use in cardEffect()
	 * choice1 = card to trash, choice1 is a handpos for the card to discard
	 * choice2 = treasure card to take from supply
	 */
	//choice1 = 1 chooses the copper at handpos1 to trash
    handpos = 0, choice1 = 1, choice2 = silver, choice3 = 0, bonus = 0;
    //the played mine card is discarded!
	ret = playCard(handpos, choice1, choice2, choice3, &state);
	checkEqual(ret, 0);
	printf("returns normally if treasure costs exactly 3 more (True/False) = %d\n", (ret == 0));
	printf("\texpected %d\n", 1);
	
	//test4: no error if treasure card taken costs less than 3 more------------------------------------------------------
	//refresh state
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	/* initialize values to use in cardEffect()
	 * choice1 = card to trash, choice1 is a handpos for the card to discard
	 * choice2 = treasure card to take from supply
	 */
	//choice1 = 1 chooses the copper at handpos1 to trash
    handpos = 0, choice1 = 1, choice2 = copper, choice3 = 0, bonus = 0;
    //the played mine card is discarded!
	ret = playCard(handpos, choice1, choice2, choice3, &state);
	checkEqual(ret, 0);
	printf("returns normally if treasure costs less than 3 more (True/False) = %d\n", (ret == 0));
	printf("\texpected %d\n", 1);
	
	//test5: error if treasure card taken costs more than 3 more------------------------------------------------------
	//refresh state
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	/* initialize values to use in cardEffect()
	 * choice1 = card to trash, choice1 is a handpos for the card to discard
	 * choice2 = treasure card to take from supply
	 */
	//choice1 = 1 chooses the copper at handpos1 to trash
    handpos = 0, choice1 = 1, choice2 = gold, choice3 = 0, bonus = 0;
    //the played mine card is discarded!
	ret = playCard(handpos, choice1, choice2, choice3, &state);
	checkEqual((ret < 0), 1);
	printf("returns error if treasure costs more than 3 more (True/False) = %d\n", (ret < 0));
	printf("\texpected %d\n", 1);
	
	//test6: drawn treasure card is placed in hand-----------------------------------------------------------
	//refresh state
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	/* initialize values to use in cardEffect()
	 * choice1 = card to trash, choice1 is a handpos for the card to discard
	 * choice2 = treasure card to take from supply
	 */
	//choice1 = 1 chooses the copper at handpos1 to trash
    handpos = 0, choice1 = 1, choice2 = silver, choice3 = 0, bonus = 0;
    //the played mine card is discarded!
	playCard(handpos, choice1, choice2, choice3, &state);
	//old number of silver cards in hand
	int oldSilver = cardHandCount(currentPlayer, silver, &stateOriginal);
	//new number of silver cards in hand
	int newSilver = cardHandCount(currentPlayer, silver, &state);
	//added 1 silver to hand
	checkEqual((newSilver - oldSilver), 1);
	printf("added %d of the chosen treasure card to hand, expected %d\n", newSilver - oldSilver, 1);
	/*
	printf("oldHand:\n");
	printHand(currentPlayer, &stateOriginal);
	printf("new hand:\n");
	printHand(currentPlayer, &state);
	*/
	
	//test7: card is taken from supply-----------------------------------------------------------------------
	//old supply count
	int oldSupply = stateOriginal.supplyCount[silver];
	//new supply count
	int newSupply = state.supplyCount[silver];
	checkEqual(oldSupply - newSupply, 1);
	printf("card was taken from supply (True/False) = %d, expected %d\n", (oldSupply - newSupply) == 1, 1);
	
	//test8: player's deck is not affected-------------------------------------------------------------------
	int oldDeck = stateOriginal.deckCount[currentPlayer];
	int newDeck = state.deckCount[currentPlayer];
	checkEqual(oldDeck, newDeck);
	printf("player's deck is not affected (True/False) = %d, expected %d\n", oldDeck == newDeck, 1);
	
	//test9: other players are not affected------------------------------------------------------------------
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
	
	printf("DONE testing mine card\n\n");
	return 0;
}
