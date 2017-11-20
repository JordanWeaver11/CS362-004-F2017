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


        int players=2;
        int rand=1000;
        int expected=10;

/*Here is the test for the function is game over *****************/
initializeGame(players, k, rand, &realGame);

/*now we cope the game to our test struct type */
/*so we dont need to initilize more than one time*/


memcpy(&testGame, &realGame, sizeof(struct gameState));

 printf(" This Test Is to TEST The function ( numHandCards ) : \n");

 printf("*********************************************************************************\n");

 printf("test when put the number of cards in hand =10 \n");


//testGame.handCount[0]=10;

	result= numHandCards(&testGame);

	if( result==10){

		printf("result =%d expected result is = %d \n", result, expected);

		printf(" THE TEST PASS\n");

	
	}

	else{

		 printf("result =%d expected result is = %d \n", result, expected);

                printf(" THE TEST FAIL\n");



}
/*****************************************************************/
printf("test when put the number of cards in hand =5 as it initilized \n");

initializeGame(players, k, rand, &realGame);
memcpy(&testGame, &realGame, sizeof(struct gameState));

 result= numHandCards(&testGame);

        if( result==5){

                printf("result =%d expected result is = 5 \n", result);

                printf(" THE TEST PASS\n");


        }

        else{

                 printf("result =%d expected result is =5 \n", result);

                printf(" THE TEST FAIL\n");



	}

return 0;
}

