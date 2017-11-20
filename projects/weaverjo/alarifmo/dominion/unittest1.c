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
	int expected=1;

/*Here is the test for the function is game over *****************/
initializeGame(players, k, rand, &realGame);

/*now we cope the game to our test struct type */
/*so we dont need to initilize more than one time*/


memcpy(&testGame, &realGame, sizeof(struct gameState));



		printf(" This Test Is to TEST The function ( isGameOver() ) : \n");


		printf("Gmae is over when stack of Province cards has been exhausted, or when any three other stacks in the Supply have been exhausted.\n");
		printf("\n");
		printf("*********************************************************************************\n");
		printf("The first test is when 3 stacks exhusted (we tried curse,gold, and copper \n");
		testGame.supplyCount[curse]=0;
		testGame.supplyCount[copper] =0;
		testGame.supplyCount[gold] = 0;

		result=isGameOver(&testGame);

		if (result==1){
                        printf("result =%d expected result is = %d \n", result, expected);
                        printf(" The TEST PASSED \n");
                } 

                else {

                  printf("result  =%d |||| expected result is = %d \n", result, expected);
                  printf(" The TEST FAIL \n");
                }



//************************************************************************//
		printf("**************************************************************\n");
		initializeGame(players, k, rand, &realGame);
		memcpy(&testGame, &realGame, sizeof(struct gameState));

		printf(" The test here is for shen the province been exhusted \n");
		testGame.supplyCount[province] = 0;
		result=isGameOver(&testGame);

		if (result==1){
			printf("The result is =%d and the expected result is = %d \n", result, expected);
			printf(" SO the test Passed \n");
		} 

		else {

		  printf("The result is =%d and the expected result is = %d \n", result, expected);
                  printf(" SO the test Fail \n");
                } 



return 0;
			}
