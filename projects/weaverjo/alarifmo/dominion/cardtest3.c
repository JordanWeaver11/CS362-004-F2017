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

printf(" Here is the Test For the Card ( Sea hag) \n");
printf("\n The functualty if Sea Hag card has changed, so instead every other player getting a curse card, they will get an estate card instead \n");

initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));
testGame.whoseTurn++;
printf("\n **************the test begin here****************** \n");

printf("the number of card in the deck before playing sea hag= %d \n ", testGame.deckCount[0]);
printf("Now is turn = %d \n", whoseTurn(&testGame));

printf("The player number 1 will play, so the deck for player number 0 should change and have curse in the top of it to pass the test\n");

if ( testGame.deck[0][4]!=curse){
        printf(" the first initially is not curse \n");
}


cardEffect(sea_hag, 0, 0, 0, &testGame, 4, 0);
printf("\nthe number of card in the deck after playing sea hag= %d , expected =5 \n ", testGame.deckCount[0]);
printf("the the result = the expected, and the top card is = curse  -> the test will pass \n");


if ( testGame.deck[0][4]==curse|| testGame.deckCount[0] ==5){
	printf(" ****Passed the test *****\n");

}
else {


	printf("*****The test FAILl***** \n");


}

return 0;
}

