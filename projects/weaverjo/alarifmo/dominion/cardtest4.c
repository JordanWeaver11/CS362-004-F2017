#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
int main(){
        struct gameState realGame, testGame;
        int result;
        int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                        sea_hag, tribute, smithy};
	int i=0, j=0, h=0;
        int count=0;
        int rand=1000;

printf(" Here is the Test For the Card ( Steward ) \n");
initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));
shuffle(0,&testGame);
printf("\n **************the test begin here****************** \n");
printf("Choice =1        +2 cards in hand   , -2 cards from deck \n");
i=testGame.discardCount[0];
j=testGame.deckCount[0];
h=testGame.coins;


cardEffect(steward,1,0,0,&testGame,0,0);
result=testGame.handCount[0];
printf("The number of discards cards before = %d, and now =%d \n", i,testGame.discardCount[0]);
printf("The number of cards in hand = %d, and expected =6 \n", result);
printf("The number of cards in deck before = %d, and now =%d \n", j,testGame.deckCount[0]);
printf("The coins player have before = %d, and now %d \n", h,testGame.coins);
if( result==6 || testGame.discardCount[0]==0 || testGame.deckCount[0]==j-2 ){
	count++;
}

/***********************************************************************************************/
initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));

printf("Choice =2          +2 coins after playing the card, nothing else change \n");
i=testGame.discardCount[0];
j=testGame.deckCount[0];
h=testGame.coins;


cardEffect(steward,2,0,0,&testGame,0,0);
result=testGame.handCount[0];
printf("The number of discards cards before = %d, and now =%d \n", i,testGame.discardCount[0]);
printf("The number of cards in hand = %d, and expected =4 \n", result);
printf("The number of cards in deck before = %d, and expected =%d \n", j,testGame.deckCount[0]);
printf("The coins player have before = %d, and now %d \n", h,testGame.coins);

if( result==4 && testGame.discardCount[0]==0 && testGame.deckCount[0]==j ){
        count++;
}
/*************************************************************/
initializeGame(2, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));

printf("Choice =3         trash two cards \n");
i=testGame.discardCount[0];
j=testGame.deckCount[0];
h=testGame.coins;


cardEffect(steward,3,0,0,&testGame,0,0);
result=testGame.handCount[0];
printf("The number of discards cards before = %d, and now =%d \n", i,testGame.discardCount[0]);
printf("The number of cards in hand = %d, and expected =2 \n", result);
printf("The number of cards in deck before = %d, and expected =%d \n", j,testGame.deckCount[0]);
printf("The coins player have before = %d, and now %d \n", h,testGame.coins);

if( result==2 && testGame.discardCount[0]==0 && testGame.deckCount[0]==j ){
        count++;
}

/**********************************************************************************************/

if( count==3){

	printf("ALL TESTS PASSED \n");


}
else{

	printf("TEST FAILED, ONE OR MORE TEST DID NOT PASS \n");
}

return 0;
}
