#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
} POINT;

float dist_haus_line_line(POINT *l1, POINT *l2)
{
    POINT max_kor1;
    POINT max_kor2;
    float max1, max2, hausd1, hausd2, vzd1a, vzd1b, vzd2a, vzd2b;
    int i, j;

    //: nájdime najvzdialenejší bod od prvej usecky (l1) na druhej usecke (l2) - a ulozime jeho koordinaty

   // max1 = sqrt(pow(l1[0].x - l2[0].x, 2) + pow(l1[0].y - l2[0].y, 2));
    max1 = sqrt((l1[0].x - l2[0].x) * (l1[0].x - l2[0].x) + (l1[0].y - l2[0].y) * (l1[0].y - l2[0].y));
    for (i = 1; i <= 100; i++)
    {
        for (j = 1; j <= 100; j++)
        {

            vzd1a = sqrt((l1[i].x - l2[j].x) * (l1[i].x - l2[j].x) + (l1[i].y - l2[j].y) * (l1[i].y - l2[j].y));
            if (vzd1a > max1)
            {
                max1 = vzd1a;
                max_kor1.x = l2[j].x;
                max_kor1.y = l2[j].y;
                max_kor2.x = l1[i].x;
                max_kor2.y = l1[i].y;
            }
        }
    }

    //: vzhľadom k nájdenému najvzdialenejšiemu bodu (max) nájdime teraz ten, ktorý je k nemu najbližšie lezi na druhej usecke

    hausd1 = sqrt(pow(l1[0].x - max_kor1.x, 2) + pow(l1[0].y - max_kor1.y, 2));
    for (i = 1; i <= 100; i++)
    {
        vzd1b = sqrt(pow(l1[i].x - max_kor1.x, 2) + pow(l1[i].y - max_kor1.y, 2));
        if (vzd1b < hausd1)
        {
            hausd1 = vzd1b;
        }
    }

    //: vzhľadom k nájdenému najvzdialenejšiemu bodu (max) nájdime teraz ten, ktorý je k nemu najbližšie lezi na druhej usecke

    hausd2 = sqrt(pow(l2[0].x - max_kor2.x, 2) + pow(l2[0].y - max_kor2.y, 2));
    for (i = 1; i <= 100; i++)
    {
        vzd2b = sqrt(pow(l2[i].x - max_kor2.x, 2) + pow(l2[i].y - max_kor2.y, 2));
        if (vzd2b < hausd2)
        {
            hausd2 = vzd2b;
        }
    }

    //: porovnáme dve získané vzdialenosti - menšia je Hausdorffova vzdialenosť, jeho hodnotu vratime do mainu

    if (hausd1 <= hausd2)
    {
        return hausd2;
    }
    else
    {
        return hausd1;
    }
}

int main()
{
    POINT l1[101] = {{0, 0}, {0, 0}, {0, 0}};
    POINT l2[101] = {{0, 0}, {0, 0}, {0, 0}};
    float dist = 0;
    int i = 0;
    double q = 1;

    //: Pouzivatel zada zaciatocne a koncove body useciek

    printf("Zadajte prvu x-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[0].x);
    printf("Zadajte prvu y-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[0].y);

    printf("Zadajte druhu x-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[100].x);
    printf("Zadajte druhu y-ovu koordinatu, pre L1 : \n");
    scanf("%f", &l1[100].y);

    printf("Zadajte prvu x-ovu koordinatu, pre L2 : \n");
    scanf("%f", &l2[0].x);
    printf("Zadajte prvu y-ovu koordinatu, pre L2 : \n");
    scanf("%f", &l2[0].y);

    printf("Zadajte druhu x-ovu koordinatu, pre L2 : \n");
    scanf("%f", &l2[100].x);
    printf("Zadajte druhu y-ovu koordinatu, pre l2 : \n");
    scanf("%f", &l2[100].y);

    //: Usecky rozdelime na 50 rovnakych casti

    for (i = 1; i < 100; i++)
    {
        l1[i].x = l1[0].x + ((q / 99) * (l1[100].x - l1[0].x));
        q++;
    }

    q = 1;
    for (i = 1; i < 100; i++)
    {
        l1[i].y = l1[0].y + ((q / 99) * (l1[100].y - l1[0].y));
        q++;
    }

    q = 1;
    for (i = 1; i < 100; i++)
    {
        l2[i].x = l2[0].x + ((q / 99) * (l2[100].x - l2[0].x));
        q++;
    }

    q = 1;
    for (i = 1; i < 100; i++)
    {
        l2[i].y = l2[0].y + ((q / 99) * (l2[100].y - l2[0].y));
        q++;
    }

    //: Posleme usecky do funkcii

    dist = dist_haus_line_line(&l1, &l2);

    printf("Hausdorff vzdialenost medzi dvoma useckami je : %.4f", dist);
}
