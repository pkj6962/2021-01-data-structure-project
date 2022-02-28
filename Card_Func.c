#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"

int* cardShuffle() /*8���� ī�� �� k���� ī�带 �̴´�. */
{
    int i, j, num, temp;
    int k = SUGGEST_CARD_NUM;
    int* card_list = (int*)malloc(sizeof(int) * k);
    for (i = 0; i < k; i++)
    {
        card_list[i] = -1;
    }

    int idx = 0;
    srand(time(NULL));
    for (i = 0; i < k; i++)
    {
        num = rand() % 8;
        for (j = 0; j < k; j++)
        {
            if (num == card_list[j])
                break;
        }
        if (j != k) /*�̹� ���õ� ī���� ��*/
        {
            i--;
            continue;
        }
        else {
            card_list[idx++] = num;
        }
    }

    /*sort�� ����*/
    for (i = 0; i < k - 1; i++)
    {
        for (j = 0; j < k - 1; j++)
        {
            if (card_list[j] > card_list[j + 1])
            {
                temp = card_list[j + 1];
                card_list[j + 1] = card_list[j];
                card_list[j] = temp;
            }
        }
    }
    return card_list; 
}
void suggestCard(int card_list[])
{
    /*�������� k��*/
    int num, i; 
    int k = SUGGEST_CARD_NUM; 
    int first, second; 
    for (i = 0; i < k; i++)
    {
        num = card_list[i]; 
        printf("%d. ", num + 1); 
        first = cardlist[num].basicwork; 
        second = cardlist[num].addwork; 
        
        switch (first) {
        case(atk):          printf("���� ");     break;
        case(upgradeatk):   printf("���ݷ� ��ȭ "); break;
        case(upgradedef):   printf("���� ��ȭ "); break; 
        case(percard):      printf("ī�� ��� Ƚ�� ���� "); break; 
        }
        switch (second) {
        case(none):         printf("\n");  break;
        case(atk):          printf("+ ����\n");  break; 
        case(upgradeatk):   printf("+ ���ݷ� ��ȭ\n"); break; 
        case(upgradedef):   printf("+ ���� ��ȭ\n"); break; 
        case(percard):      printf("+ ī�� ��� Ƚ�� ����\n"); break; 
        }
    }
}
