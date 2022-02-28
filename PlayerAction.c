#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"


void user_choice(int* card_list)
{
    /*������ �ڽ��� �ൿ�� ������ŭ ī�带 �̴´�. �ߺ� ó��, ���� ó�� �Ĳ���*/
    int k = SUGGEST_CARD_NUM;
    int i, j;
    int num;
    int avail_num = User->card_num;
    User->card_num = DEFAULT_CARD_AVAIL;
    int avail = avail_num;  /*���ʿ� ��밡���ߴ� ī�� ���� */
    int* used = (int*)malloc(sizeof(int) * avail_num); /*����� ī��*/
    int idx_for_used = 0;
    for (i = 0; i < avail_num; i++)
    {
        used[i] = -1;
    }

    for (i = 0; i < avail_num; i++)
    {
        printf("\nī�带 �������ּ���(���� ī�� ��� Ƚ�� : %d): ", avail);
        scanf("%d", &num);
        num--; /*�ε����� 1�������Ѽ� �����߱� ������ 1 ���ҽ��Ѿ� �Ѵ�.*/

        /*card_list�� ���� ī�带 ������ ��� �ٽ�*/
        for (j = 0; j < k; j++)
        {
            if (num == card_list[j])
                break;
        }
        if (j == k) /*������ ������ ī�尡 �̾ȿ� ���ٴ� ��*/
        {
            printf("������ �� ���� ī���Դϴ�. �ٽ� �������ּ���.\n"); Sleep(1000);
            i--;
            continue;
        }

        for (j = 0; j < avail; j++)
        {
            if (num == used[j])
            {
                break;
            }
        }
        if (j != avail)  /*������ ������ ī�尡 ����� ī�忡 �ִٴ� ��*/
        {
            printf("�̹� ����� ī���Դϴ�. �ٽ� �������ּ���. \n"); Sleep(1000);
            i--;
            continue;
        }

        used[idx_for_used++] = num;
        avail--;


        /*������ ī�忡 ���� ������ �����ϰų� ���׷��̵带 �Ѵ�. */
        int first, second, first_increment, second_increment;
        first = cardlist[num].basicwork;
        second = cardlist[num].addwork;
        first_increment = cardlist[num].basicpower;
        second_increment = cardlist[num].addpower;

        switch (first) {
        case (atk):         attack(user); break;
        case(upgradeatk):   upgrade(user, att, first_increment); break;
        case(upgradedef):   upgrade(user, def, first_increment); break;
        case(percard):      upgrade(user, cardnum, first_increment); break;
        }
        /*������ ������带 �������� ���� �ߴ� ����. */

        switch (second) {
        case(none):         break;
        case(atk):          attack(user); break;
        case(upgradeatk):   upgrade(user, att, second_increment); break;
        case(upgradedef):   upgrade(user, def, second_increment); break;
        case(percard):      upgrade(user, cardnum, second_increment); break; 
        }
        printf("�� ����.\n\n"); Sleep(1000); 
    }
    /*���⼭ ������� ī�� ���Ƚ���� ����Ʈ�� �ǵ�����? ���࿡ ������ ī�� ���Ƚ���� �÷�����?
    ����Ʈ�� �ǵ����� ������, ������ ī�� ���Ƚ���� ���������� ������ ���·� �����ȴ�. */
}

void ai_choice(void)
{
    /*ai�� �˰��� 
    
    ���: ai�� �γ��� ������ ���Դϴ� 
    ai�� �ּ��� �ൿ�� ����ϴ� ���Դϴ�
    ai�� ��� ����� ���� �м��ϴ� ���Դϴ� 

    ai�� ���� �� �ִ� ����� �� 
    1. ����
    2. ���ݷ� ��ȭ  : findTarget�� �ߴµ� from�� ���ݷº��� to�� ������ ���� ��
    3. ���� ��ȭ 
    4. ī�� ��� Ƚ�� ���� --> ��� ����. 
    
    ����? ������? 
    */
    int from, to; 
    int AttOrDef;
    int increment;
    increment = level;

    printf("AI�� ��� ���Դϴ�...\n\n"); 
    Sleep(1500); 

    srand(time(NULL)); 
    AttOrDef = rand() % 2; 

    if (AttOrDef)   /*1�̸� ����(Ȥ�� ���ݷ� ��ȭ)*/
    {
        findTarget(ai, &from, &to); 
        if (land_list[from]->att < land_list[to]->def)
            upgrade(ai, att, increment);
        else
            attack(ai);
    }
    else {      /*0�̸� ���� ��ȭ*/
        findTarget(user, &from, &to);
        upgrade(ai, def, increment); 
    }
    printf("�� ����.\n\n"); Sleep(1500); 




    
}