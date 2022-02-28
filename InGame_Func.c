#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"

void unionLand(int x, int y)
{
	/*x�� 1(user�� ����) �ƴϸ� 24(AI�� ����)�̴�. Y�� x�� ����� ����� ���Խ�Ų��. */
	if (x == 1)
	{
		capital[y] = capital[x];
	}
	else /*24, �� ai�� �����̸�*/
	{
		capital[x] = capital[y];
	}
	return;
}
int choose_from(int player, int action)
{
	int from, owner;
	do {
		printf("�Ʊ��� ���並 �������ֽʽÿ�.(1-24): ");
		scanf("%d", &from);

		if ((from > 24) || (from <= 0))
		{
			printf("�߸��� �Է��Դϴ�.\n\n");
			Sleep(500);
			continue;
		}
		owner = land_list[from]->owner;
		if (owner != player)
		{
			printf("�߸��� �����Դϴ�. �Ʊ��� ���信�� ������ �� �ֽ��ϴ�.\n\n");
			Sleep(500);
			continue;
		}
		if ((action == Att) && (capital[from] != capital_of_player[player])) /*�÷��̾��� ������ '����'�ε� �������� �������� ������ */
		{
			printf("������ ������ ���信���� ������ �� �ֽ��ϴ�.\n\n");
			Sleep(500);
			continue;
		}
		break;
	} while (1);





	return from;
}
int choose_to(int player, int* from)
{
	int to, owner, exit_flag;
	land_link* temp;
	temp = land_list[*from]->link;
	
	do {
		printf("�� �� ���並 �����Ͻðڽ��ϱ�?(�������� �ǵ��ư���: 0��): ");
		scanf("%d", &to);
		if (to == 0)
		{
			*from = choose_from(player, Att);
			to = choose_to(player, from);
		}
		if ((to > 24) || (to <= 0))
		{
			printf("�߸��� �Է��Դϴ�.\n\n");
			continue;
		}
		owner = land_list[to]->owner;
		if (owner == -1) /*�߸����븦 ����������*/
		{
			printf("�߸������ ������ �� �����ϴ�.\n\n");
			continue;
		}
		if (owner == player)	/*�Ʊ��� ���並 ���� ������� �������*/
		{
			printf("�߸��� �����Դϴ�. �Ʊ��� ����� ������ �� �����ϴ�.\n\n");
			continue;
		}
		/*from land�� ���� ���带 ���鼭 to land�� �ִ��� ã�´�. ������ break, ������ �ݺ�*/
		for (temp = land_list[*from]->link; temp; temp = temp->next)
		{
			if (temp->num == to)
			{
				break;
				exit_flag = 1;
			}
		}
		if (!temp)
		{
			printf("�߸��� �����Դϴ�. ������ ���丸 ������ �� �ֽ��ϴ�.\n\n");
			continue;
		}
		break;
	} while (1);
	return to;
}
void attack(int player)
{
	int from, to;
	int exit_flag = 0; /*while���� Ż���ϱ� ���� flag */
	int def_before_change; /*���� �ޱ� �� ������ ����. printAction�� parameter�� ���� ���� ���� */

	if (player == user)
	{
		from = choose_from(player, Att);
		to = choose_to(player, &from);
	}
	else {
		findTarget(ai, &from, &to); 
	}

	land* ATT = land_list[from];
	land* DEF = land_list[to];


	def_before_change = DEF->def; 
	if (DEF->def - ATT->att > 0)
	{
		DEF->def = DEF->def - ATT->att;
		ATT->att = MIN_ATT;
	}
	else   /*DEF <= ATT : ���� ������ ����, connection ���� ��Ȯ�� */
	{
		if (ATT->att == DEF->def)
			ATT->att = DEFAULT_ATT;
		else
			ATT->att = ATT->att - DEF->def;

		DEF->def = DEFAULT_DEF; /*default ������ */

		DEF->owner = player;
		land_owner[to] = player;
		connection_with_capital();

		if (player == user)
		{
			User->total_land++;
			Ai->total_land--;
		}
		else
		{
			User->total_land--;
			Ai->total_land++;
		}
	}
	printAction(player, Att, 0, from, to, def_before_change); 




	return;

}
void ai_attack()
{
	//findTarget(); 
	//attack(ai);

}

void upgrade(int player,int stats, int increment) 
{
		/*Player�� Ư�� ������ ���ݷ�(����) Ȥ�� Player�� �ൿ���� ���������ִ� �Լ�
		*statts: ���ݷ��ΰ�� --> land_list[land_num]->att�� ������Ų��. 
		stats: �����ΰ�� --> land_list[land_num]->def�� ������Ų��.
		���� ���� : land_num: Ai�� User���忡���� findTarget()���ν� ��ȭ�� ���並 ���Ѵ�. User�� choose_from()�Լ��� ���� �Է¹޴´�.  
		*/ 
	struct player* Player; 
	int land_num;
	int from, to; 
	int value_before_change; 
	/*stats�� increment�� �Է¹޵��� ����*/

	if (stats == cardnum)
	{
		value_before_change = User->card_num;
		if (User->card_num + increment >= MAX_CARD_NUM)
			User->card_num = MAX_CARD_NUM;
		else
			User->card_num += increment;
		printAction(player, Upg, stats, 0, 0, value_before_change);
		return; 

	}
	if (player == user)
	{
		Player = User;
		land_num = choose_from(user, Upg);
	}
	else
	{
		Player = Ai;
		
		findTarget(user, &from, &to); /*User���忡���� ������ ���� ã�´�. �ش� ���並 ��ȭ�Ѵ�.*/
		/*to�� �ش��ϴ� ���尡 AI�� ��ȿ����μ� �����ϴ��� Ȯ��*/
		
		land_num = to; 
	}

	/*stats�� ���� Player�� land�� ���ݷ�/���� �Ǵ� �ൿ�� ��ȭ */
	
	land* target = land_list[land_num]; 
	if (stats == att)
	{
		value_before_change = target->att; 
		if ((target->att + increment) >= MAX_STATS)
			target->att = MAX_STATS;
		else {
			target->att += increment; 
		}
	}
	else if (stats == def)
	{
		value_before_change = target->def ; 
		if ((target->def + increment) >= MAX_STATS)
			target->def = MAX_STATS; 
		else {
			target->def += increment; 
		}
	}
	else    /*stats�� ������ �ൿ��(card_num)�� ���*/
	{
		value_before_change = Player->card_num; 
		if (Player->card_num + increment >= MAX_CARD_NUM)
			Player->card_num = MAX_CARD_NUM; 
		else
			Player->card_num += increment;
	}

	printAction(player, Upg, stats, land_num, 0, value_before_change); 
}

