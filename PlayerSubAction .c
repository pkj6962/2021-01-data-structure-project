#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"


void connection_with_capital(void) /*<-- ���� ���� ����� ������� capital[]�� �ݿ��Ѵ�. .*/
{
	int i = 0;
	int idx;
	land_link* linked;
	short int visited[NODE_NUM];
	int owner;
	int CAPITAL[] = { 1, 24 };
	int player[] = { 0, 1 };
	int cap;
	int count;

	capital_initialize();
	for (i = 1; i < NODE_NUM; i++)
	{
		visited[i] = 0;
	}



	for (int j = 0; j < 2; j++)
	{
		cap = CAPITAL[j];
		owner = land_list[cap]->owner;
		count = 0;

		push(cap);
		visited[cap] = 1;
		count++;
		while (!is_Empty())
		{
			idx = pop();
			linked = land_list[idx]->link;
			for (; linked; linked = linked->next)
			{
				if (visited[linked->num] == 1)
					continue;
				if (land_list[linked->num]->owner == owner)
				{
					capital[linked->num] = capital[cap];
					push(linked->num);
					visited[linked->num] = 1;
					count++;
				}
			}
		}
		if (j == 0)
			User->valid_land = count;
		else
			Ai->valid_land = count;

		/*
		����ؾ� �ϴ� �κ�
		1. ������ ���並 ���Ѿ��� ��(�������� �Լ� �簡��)
		2. ���Ѱ��� ��(���ѱ� ���尡 ������ ����Ǿ����� Ȯ�� -> ������ ������������ �ٽ� Ȯ�� ����
		*/
	}

	return;

}
void capital_initialize(void)
{
	int i;
	for (i = 1; i < NODE_NUM; i++)
	{
		capital[i] = i;
	}
}
void findTarget(int player, int* from, int* to) /*AI�� ������ ���ݷ�Ʈ�� ã�� �Լ�*/
{
	/*
		0. valid land�� ǥ���� capital�� �����Ѵ�.
		1. �ڽ��� ��ȿ ���� �� ��� ����� ������ ���並 ã�Ƽ� �����Ѵ�.(malloc ���)
		2. �ش� ����鿡�� ���ݰ����� ��� ��츦 ���鼭, ��� ���並 �������� ��
		����� ��ȿ������ ��ȭ�� Ȯ���Ѵ�.
		3. (������)(ai�� ��ȿ������ �� - ������ ��ȿ������ ��)�� �ִ밡 �Ǵ� ���(from, to)�� �����Ѵ�.
		4. ��� ��츦 ���鼭 �ִ밡 �Ǵ� ���� �����Ѵ�.
	*/

	/*�������忡���� �ּ��� ���ݷ�Ʈ�� ã�� �� �ְ� �Լ��� �����ؼ� AI�� ���� ��ȭ�� �� ���带 ������ �� �ְ� �ؾ� �Ѵ�. */


	int i, j;
	int copy_capital[NODE_NUM];
	land_link* Att_avail_land = (land_link*)malloc(sizeof(land_link));
	Att_avail_land = NULL;
	int* valid_land;


	struct player* Att, * Def;

	if (player == user)
	{
		Att = User;
		Def = Ai;
	}
	else
	{
		Att = Ai;
		Def = User;
	}

	valid_land = (int*)malloc(sizeof(int) * (Att->valid_land));


	for (i = 1; i < NODE_NUM; i++)
	{
		copy_capital[i] = capital[i];
	}
	/*���߿� ������ų ����.*/

	j = 0;
	for (i = NODE_NUM - 1; i != 0; i--)
	{
		/*���� ������ ���鼭 ��ȿ���带 Ȯ���Ѵ�.*/

		if (j == Att->valid_land)
			break;

		if (capital[i] == capital_of_player[player])
			valid_land[j++] = i;
	}

	int valSave[2];
	int land_num;
	land_link* node;
	int diff;  /*Ai's valid land  - User's valid land*/
	int highest = -24; /*diff �� �ִ� ����: ���� ȿ������ ���ݷ�Ʈ */
	int source;	/*highest�� ���� ���������*/
	int dest; /*highest�� ���� ���ݵ�����*/


	/*valid ���带 ���鼭, ��� ����� ������, ���ݰ����� ���带 ã�� �����Ѵ�*/
	for (i = 0; i < Att->valid_land; i++)
	{
		land_num = valid_land[i];
		node = land_list[land_num]->link;

		for (; node; node = node->next)
		{
			if (land_list[node->num]->owner == !player)		/*������ ���� ����� ���� ��*/
			{
				/*�� ��� ���� �������� ���� player�� ��ȿ������ ���� ���Ѵ�.*/

				int valSave[2];
				valSave[0] = User->valid_land;
				valSave[1] = Ai->valid_land;


				land_list[node->num]->owner = player;		/*Attacker�� ������ �������� �ٲ� �� �ٲ� ���� ��ȿ������ ���� ���� ����غ���.*/

				connection_with_capital();

				diff = Att->valid_land - Def->valid_land;

				if (highest < diff)
				{
					highest = diff;
					source = land_num;
					dest = node->num;
				}

				/*3. ����*/
				User->valid_land = valSave[0];
				Ai->valid_land = valSave[1];
				for (j = 1; j < NODE_NUM; j++)
				{
					capital[j] = copy_capital[j];
				}
				land_list[node->num]->owner = !player;
			}
			//���� ���� ���忡 ���ؼ� �ݺ�
		}


	}
	*from = source;
	*to = dest;
}