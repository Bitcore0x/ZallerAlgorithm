#include "stdio.h"
#include "zaller.h"
int main(void){
        int years[4]={2,0,2,6}; /*2026/day/mm */
        int *pys=&years[0];
        int day,month;
        printf("write the month and day: \n");
        scanf("%hhd %hhd",&month,&day);
        switch(zaller_day(pys,month,day)){
                case 0: printf("Saturday"); break;
                case 1: printf("Sunday"); break;
                case 2: printf("Monday"); break;
                case 3: printf("Tuesday");break;
                case 4: printf("Wensday"); break;
                case 5: printf("Thursday"); break;
                case 6: printf("Friday"); break;
        }
}
