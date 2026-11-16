#include "zaller.h"
int zaller_day(int *pys,int month,int day){
        // there all d,m,c belong tha Z+ and there all y belong than N
        int c= (*(pys)*10)+(*(pys+1));
        int years = (*(pys+2)*10)+(*(pys+3));
        if (month<3){
                month +=12;
                years -=1;
                if(years<0){
                        years=99;
                        c-=1;
                }
        }

        int h = (day+(13*(month+1)/5)+years+(years/4)+(c/4)+(c*5));
        h = (h+7)%7;
        return h;
}
