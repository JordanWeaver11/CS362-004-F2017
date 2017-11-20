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

 printf(" This Test Is to TEST The function ( getCoast ) : \n");

 printf("*********************************************************************************\n");

 printf("i will pick 10 random cards and use the function to get their result, and we wil compare it to the real coast of the card. If they are equal then the function pased the test  \n");

printf("\n");

 printf("Card is (smithy) \n");
 result=getCost(smithy);
printf("card result = %d, espected= 4 \n",result);
if (result==4){ count++;

}

printf("\n");


 printf("Card is (estate) \n");
 result=getCost(estate);
printf("card result = %d, espected= 2 \n",result);
if (result==2){ count++;

}

printf("\n");




 printf("Card is (minion) \n");
 result=getCost(minion);
printf("card result = %d, espected= 5 \n",result);
if (result==5){ count++;

}

printf("\n");




 printf("Card is (baron) \n");
 result=getCost(baron);
printf("card result = %d, espected= 4 \n",result);
if (result==4){ count++;

}

printf("\n");




 printf("Card is (embargo) \n");
 result=getCost(embargo);
printf("card result = %d, espected= 2 \n",result);
if (result==2){ count++;

}

printf("\n");



 printf("Card is (treasure_map) \n");
 result=getCost(treasure_map);
printf("card result = %d, espected= 4 \n",result);
if (result==4){ count++;

}

printf("\n");



 printf("Card is (salvager) \n");
 result=getCost(salvager);
printf("card result = %d, espected= 4 \n",result);
if (result==4){ count++;

}

printf("\n");



 printf("Card is (duchy) \n");
 result=getCost(duchy);
printf("card result = %d, espected= 5 \n",result);
if (result==5){ count++;

}

printf("\n");


 printf("Card is (gold) \n");
 result=getCost(gold);
printf("card result = %d, espected= 6 \n",result);
if (result==6){ count++;

}

printf("\n");


 printf("Card is (mine) \n");
 result=getCost(mine);
printf("card result = %d, espected= 5 \n",result);
if (result==5){ count++;

}

printf("\n");


if(count==10){

	printf(" THE TEST PASSES \n");

}

else{

 printf(" THE TEST FAIL \n");


}

return 0;
}

