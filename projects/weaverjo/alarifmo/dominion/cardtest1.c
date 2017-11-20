#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(){
        struct gameState realGame, testGame;
        int result;
        int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                        sea_hag, tribute, smithy};

        int count=0;
        int rand=1000;

printf(" Here is the Test For the Card (Adventurer ) \n");

printf("i will set the cards in the seck and in the player hand manually to be able to test it effecintly \n");

initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));

	/*i will make the dick contain 4 cards, the second and the third are trsure cards*/
	testGame.deckCount[0] = 4;
	testGame.deck[0][0] = minion;     
        testGame.deck[0][1] = gold;     
        testGame.deck[0][2] = gold;    
        testGame.deck[0][3] = minion;

	testGame.handCount[0]=5;
	testGame.hand[0][0] = minion;     
        testGame.hand[0][1] = minion;     
        testGame.hand[0][2] = minion;    
        testGame.hand[0][3] = minion;
        testGame.hand[0][4] = minion;

	cardEffect(adventurer, 0, 0, 0, &testGame, 0, 0);

	/* the card in deck most equal to 3, and the hand count will equal to 7*/
	/* i have edited the advenrrer code function to et the player to only draw one card, so the function must FAIL */


	printf("the hand count = %d , The expected = 7, the deck = %d , The expected= 2\n", testGame.handCount[0], testGame.deckCount[0]);
	if (testGame.handCount[0]== 7){

	count++;
	}

	if(testGame.deckCount[0]==1){

	count++;


	}












/***************************************************************/
initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));

        /*i will make the dick contain 4 cards, the second and the third are trsure cards*/
        testGame.deckCount[0] = 4;
        testGame.deck[0][0] = gold;
        testGame.deck[0][1] = minion;
        testGame.deck[0][2] = minion;
        testGame.deck[0][3] = gold;

        testGame.handCount[0]=5;
        testGame.hand[0][0] = minion;
        testGame.hand[0][1] = minion;
        testGame.hand[0][2] = minion;
        testGame.hand[0][3] = minion;
        testGame.hand[0][4] = minion;

        cardEffect(adventurer, 0, 0, 0, &testGame, 0, 0);

        /* the card in deck most equal to 3, and the hand count will equal to 7*/
        /* i have edited the advenrrer code function to et the player to only draw one card, so the function must FAIL */


        printf("the hand count = %d , the expected=7, the deck = %d , the expected= 3\n", testGame.handCount[0], testGame.deckCount[0]);
        if (testGame.handCount[0]== 7){

        count++;
        }

        if(testGame.deckCount[0]==3){

        count++;


        }




 if (count==4){

        printf("the test passed \n");


       }

        else {
                printf(" The test failled \n");


 } 


return 0;      }
