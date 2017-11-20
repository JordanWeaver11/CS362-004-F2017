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
        int players=2;
        int rand=1000;
        int expected=10;

/*Here is the test for the function is game over *****************/
initializeGame(players, k, rand, &realGame);

/*now we cope the game to our test struct type */
/*so we dont need to initilize more than one time*/


memcpy(&testGame, &realGame, sizeof(struct gameState));

 printf(" This Test Is to TEST The function ( whoseTurn ) : \n");

printf("The test is set to see if the function whoesTurn have no bugs, so i will set the turns manually to see whos turn \n");

printf(" \n \n **********The test begin here*************\n");

printf("whoes turn when the gsme is initilized \n");

result =whoseTurn(&testGame);

printf("Result= %d , expected result = 0 \n", result);
if (result==0){

	count++;
}



printf("*****************************************************");
printf("\n now we will set the turn maunaly for the second player \n");
memcpy(&testGame, &realGame, sizeof(struct gameState));

testGame.whoseTurn++;

result =whoseTurn(&testGame);

printf("Result= %d , expected result = 1 \n", result);
if (result==1){

        count++;
}



if(count==2){

	printf(" The TEST PASSED test's two conditions \n ");

}

else{

	printf(" The TEST Failed \n");

}



return 0;
}
