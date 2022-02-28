#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"


void printLink(int idx)
/***************************************************
/idx��° �ε����� ����� ����� ������� ����� ���*/
{
	printf("���� %2d�� ���� ����:  ", idx);
	land_link* temp;
	temp = land_list[idx]->link;

	for (; temp; temp = temp->next)
		printf("%d ", temp->num);
	printf("\n");
	return;
}
void print_basic_info()
{
	system("cls"); 

	printf("���� �� ��:  %d\n", remaining_turns);
	printf("������ ��ȿ���� ���� ��  / �� ���� ���� ��: %d / %d\n", User->valid_land, User->total_land);
	printf("AI�� ��ȿ���� ���� �� / �� ���� ���� ��: %d / %d\n", Ai->valid_land, Ai->total_land);
	return;
}
void print_map()
{
	int i, j;

	/*����, ��ȭ �� ��/���� ��ȭ �� ������ ��ȭ�� ��ݿ� */
	for (i = 1; i < NODE_NUM; i++)
	{

		/*���ݷ��� 10�̻��� ���� �׷��� ���� ��츦 ������ �Ҵ�*/

		if (land_list[i]->att >= 10) {
			ptr[Att_index[i] + 5] = land_list[i]->att + 55;
		}
		else {
			ptr[Att_index[i] + 5] = land_list[i]->att + 48;
		}

		if (land_list[i]->def >= 10) {
			ptr[Att_index[i] + MAP_COL + 5] = land_list[i]->def + 55;
		}
		else {
			ptr[Att_index[i] + MAP_COL + 5] = land_list[i]->def + 48;

		}
		if (land_list[i]->owner == 0)
		{
			for (j = 0; j < EDGE_NUM; j++)
				ptr[NODE[i][j]] = '@';
		}
		else if (land_list[i]->owner == 1)
		{
			for (j = 0; j < EDGE_NUM; j++)
				ptr[NODE[i][j]] = '*';
		}
		else
		{
			for (j = 0; j < 4; j++)
			{
				ptr[Att_index[newtral_land[j]] + 5] = '\\';
				ptr[Att_index[newtral_land[j]] + 110 + 5] = '\\';
			}
		}
	}




	printf("\n");
	printf("\t\t\t\t\t   USER\n\t\t\t\t\t    ��\n");

	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			printf("%c", map[i][j]);

	for (i = 0; i < 134; i++)
		printf(" ");
	printf("��\n");
	for (i = 0; i < 134; i++)
		printf(" ");
	printf("AI\n");

}
void printAction(int player, int action, int stats, int from, int to, int value_before_change)
{
	struct player* Player; 
	if (player == user)
		Player = User;
	else
		Player = Ai;

	if (action == Att)
	{
		printf("\n%s�� ����[%d]���� ����[%d]��(��) �����߽��ϴ�.\n", PlayerList[player], from, to);
		Sleep(2000);
		if (land_owner[to] == player)
		{
			printf("%s�� ����[%d]��(��) �����߽��ϴ�.\n", PlayerList[player], to);	Sleep(2000);

			if (to == capital_of_player[!player])
			{
				printf("%s�� �������带 �����߽��ϴ�.\n", PlayerList[player]); Sleep(2000);

				printf("%s�� �������� �¸��Ͽ����ϴ�!\n", PlayerList[player]); Sleep(2000); 
			}
		
		}
		else {
			printf("����[%d]�� ������ %d���� %d��(��) �Ǿ����ϴ�.\n", to, value_before_change, land_list[to]->def); Sleep(2000); 
		}
	}
	else if (action == Upg)
	{
		if (stats == att)
		{
			printf("%s�� ����[%d]�� %s��(��) %d���� %d�� ���׷��̵��Ͽ����ϴ�.\n", PlayerList[player], from, StatsList[stats], value_before_change,land_list[from]->att); Sleep(2000); 
		} 
		else if (stats == def)
		{
			printf("%s�� ����[%d]�� %s��(��) %d���� %d�� ���׷��̵��Ͽ����ϴ�.\n", PlayerList[player], from, StatsList[stats], value_before_change, land_list[from]->def); Sleep(2000);
		}
		else /*stats == cardnum*/
		{
			printf("%s�� �ڽ��� %s��(��) %d���� %d�� ���׷��̵��Ͽ����ϴ�.\n", PlayerList[player], StatsList[stats], value_before_change, Player->card_num); Sleep(2000);
		}
	}

	
	/*player�� �ൿ�� ����� ����Ѵ�.
	���ݽ�:
	~~�� ���� a���� ���� b�� �����߽��ϴ�.
	���ɽ�
	~~�� ���� b�� �����߽��ϴ�.
		���� ��� ���ɽ�
		~~�� ~~�� ���� ��带 �����߽��ϴ�.
		~~�� �������� �¸��Ͽ����ϴ�!
		~~����Ʈ�� ȹ���ϼ̽��ϴ�. 
	
	���ɽ��н� 
	����b�� ������ i���� j��(��) �Ǿ����ϴ�. 
	
	���׷��̵��
	~�� ����a�� ���ݷ��� k��ŭ ���׷��̵��߽��ϴ�. 
	~�� ����a�� ������ k��ŭ ���׷��̵��߽��ϴ�.
	~�� �ڽ��� �ൿ���� k��ŭ ���׷��̵��߽��ϴ�. 
	*/
}

