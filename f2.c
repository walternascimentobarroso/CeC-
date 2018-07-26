#include<stdio.h>
void main() {

int weight[20], profit[20], item[20];
int i,j,numOfItems,sizeOfBag,totalProfit,swap;
printf ("Enter the number of items \n");
scanf("%d",&numOfItems); 
printf("enter the size of the Bag\n");
scanf("%d", &sizeOfBag);

//getting the inputs
for( i = 0; i < numOfItems; i++) {
 item[i] = i;
 printf(" Enter the Item %d's weight and profit\n",i);
 scanf("%d %d", &weight[i], &profit[i]);
 }

// sorting all three arrays based on the profit array
for (i = 0 ; i < ( numOfItems - 1 ); i++)
  {
    for (j = 0 ; j < numOfItems - i - 1; j++)
    {
      if (profit[j] < profit[j+1]) /* For decreasing order use < */
      {
        swap = profit[j];
        profit[j] = profit[j+1];
        profit[j+1] = swap;

	swap = weight[j];
	weight[j] = weight[j+1];
	weight[j+1] = swap;

	swap = item[j];
	item[j] = item[j+1];
	item[j+1] = swap;
      }
    }
  }
  
printf("After sorting based on profits\n");

for(i = 0;i < numOfItems; i++) {
 printf("Item %d profit %d weight %d\n", item[i], profit[i], weight[i]); 
}

for(i=0;i<numOfItems;i++) {
 if(sizeOfBag > 0) {
  if(weight[i] <= sizeOfBag) {
    totalProfit += (weight[i] * profit[i]);
    sizeOfBag -= weight[i];
 }
  else {
    totalProfit += (sizeOfBag * profit[i]);
    sizeOfBag = 0;  
 }
}

}
printf("Total Profit = %d", totalProfit);
}
