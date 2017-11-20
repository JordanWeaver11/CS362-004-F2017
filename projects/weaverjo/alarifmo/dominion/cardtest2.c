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

printf(" Here is the Test For the Card ( Smithy) \n");

printf("when player play smithy he will draw 3 cards, so the total number of cards will be 7 Cards. Smithy dont do anything else \n");


printf(" The TEST MUST FAIL because the Smithy card funcuality had been changed, so instead of letting the player drawing 3 cards, he will draw 2 \n");
initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));

cardEffect(smithy, 0, 0, 0, &testGame, 0, 0);


printf(" the Number of cards in hand = %d, the expected =7 \n", testGame.handCount[0]);


if (testGame.handCount[0]==7){

printf(" the Card had PASSED The TEST \n ");




}

else {


	printf(" The TEST HAD FAILED \n");

}


return 0;
}
