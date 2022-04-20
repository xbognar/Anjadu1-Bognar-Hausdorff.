#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    float x;
    float y;
}LINE;


float dist_haus_line_line(LINE* l1, LINE* l2){
    LINE max_kor1;
    LINE max_kor2;
    float max1,max2,hausd1,hausd2,vzd1a,vzd1b,vzd2a,vzd2b;
    int i,j;

    //: nájdime najvzdialenejší bod od prvej usecky (l1) na druhej usecke (l2) - a ulozime jeho koordinaty

    max1 = sqrt(pow(l1[0].x-l2[0].x,2)+pow(l1[0].y-l2[0].y,2));
    for(i=1;i<=50;i++){
        for(j=1;j<=50;j++){
            vzd1a = sqrt(pow(l1[i].x-l2[j].x,2)+pow(l1[i].y-l2[j].y,2));
            if(vzd1a > max1){
                max1 = vzd1a;
                max_kor1.x = l2[j].x;
                max_kor1.y = l2[j].y;
            }
        }
    }

    //: vzhľadom k nájdenému najvzdialenejšiemu bodu (max) nájdime teraz ten, ktorý je k nemu najbližšie lezi na druhej usecke

    hausd1 = sqrt(pow(l1[0].x-max_kor1.x,2)+(l1[0].y-max_kor1.y,2));
    for(i=1;i<=50;i++){
        vzd1b = sqrt(pow(l1[i].x-max_kor1.x,2)+pow(l1[i].y-max_kor1.y,2));
        if(vzd1b < hausd1){
            hausd1 = vzd1b;
        }
    }

    //: nájdime najvzdialenejší bod od prvej usecky (l2) na druhej usecke (l1) - a ulozime jeho koordinaty

    max2 = sqrt(pow(l1[0].x-l2[0].x,2)+pow(l1[0].y-l2[0].y,2));
    for(i=1;i<=50;i++){
        for(j=1;j<=50;j++){
            vzd2a = sqrt(pow(l2[i].x-l1[j].x,2)+pow(l2[i].y-l1[j].y,2));
            if(vzd2a > max2){
                max2 = vzd2a;
                max_kor2.x = l1[j].x;
                max_kor2.y = l1[j].y;
            }
        }
    }

    //: vzhľadom k nájdenému najvzdialenejšiemu bodu (max) nájdime teraz ten, ktorý je k nemu najbližšie lezi na druhej usecke

    hausd2 = sqrt(pow(l2[0].x-max_kor2.x,2)+(l2[0].y-max_kor2.y,2));
    for(i=1;i<=50;i++){
        vzd2b = sqrt(pow(l2[i].x-max_kor2.x,2)+pow(l2[i].y-max_kor2.y,2));
        if(vzd2b < hausd2){
            hausd2 = vzd2b;
        }
    }

    //: porovnáme dve získané vzdialenosti - menšia je Hausdorffova vzdialenosť, jeho hodnotu vratime do mainu

    if(hausd1 >= hausd2){
        return hausd2;
    }
    else{
        return hausd1;
    }
    
}
 
int main()
{
    LINE l1[51]={{0,0},{0,0},{0,0}};
    LINE l2[51]={{0,0},{0,0},{0,0}};
    float dist=0;
    int i;
    
    //: Pouzivatel zada zaciatocne a koncove body useciek

    printf("Zadajte prvu x-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[0].x);
    printf("Zadajte prvu y-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[0].y);

    printf("Zadajte druhu x-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[50].x);
    printf("Zadajte druhu y-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[50].y);

    printf("Zadajte prvu x-ovu koordinatu, pre L2 : \n");
    scanf("%f", &l2[0].x);
    printf("Zadajte prvu y-ovu koordinatu, pre L2 : \n");
    scanf("%f", &l2[0].y);

    printf("Zadajte druhu x-ovu koordinatu, pre L2 : \n");
    scanf("%f", &l2[50].x);
    printf("Zadajte druhu y-ovu koordinatu, pre l2 : \n");
    scanf("%f", &l2[50].y);

    //: Usecky rozdelime na 50 rovnakych casti

    for(i=1;i<50;i++){
        l1[i].x = l1[0].x+((i/49)*(l1[50].x-l1[0].x));
    }

    for(i=1;i<50;i++){
        l1[i].y = l1[0].y+((i/49)*(l1[50].y-l1[0].y));
    }

    for(i=1;i<50;i++){
        l2[i].x = l2[0].x+((i/49)*(l2[50].x-l2[0].x));
    }

    for(i=1;i<50;i++){
        l2[i].y = l2[0].y+((i/49)*(l2[50].y-l2[0].y));
    }

    //:Posleme usecky do funkcii

    dist = dist_haus_line_line(&l1, &l2);

    printf("Hausdorff vzdialenost medzi dvoma useckami je : %f", dist);
}
