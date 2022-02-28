#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"


void player_initialize()
{
	User = (player*)malloc(sizeof(player));
	Ai = (player*)malloc(sizeof(player));

	User->card_num = DEFAULT_CARD_AVAIL;
	Ai->card_num = DEFAULT_CARD_AVAIL;
	return;
}

void map_initialize()
{
	int i, j;
	int idx, k;
	int Att[4] = { 'A', 'T', 'T', ':' };
	int Def[4] = { 'D', 'E', 'F', ':' };

	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			map[i][j] = ' ';

	/*���� ���� ��������ִ� ���� �ʱ�ȭ  */

	for (i = 1; i < NODE_NUM; i++)
	{
		if (i % 6 == 0)
			continue;
		for (j = 0; j < LINE_NUM; j++)
		{
			ptr[EDGE_ROW[i][j]] = '-';
			//ptr[EDGE_ROW[i][j] + 110] = '-'; 
		}
	}


	for (i = 1; i < EDGE_COL_NUM; i++)
	{
		ptr[EDGE_COL[i]] = '|';
	}



	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < 5; j++)
			map[i][j] = '\t';
	/*
	for (i = 1; i < NODE_NUM; i++)
		for (j = 0; j < EDGE_NUM; j++)
			ptr[NODE[i][j]] = '#';
	*/


	/*���ݷ�, ���� ǥ��*/
	for (i = 1; i < NODE_NUM; i++)
	{
		for (j = 0; j < 4; j++)
		{
			ptr[Att_index[i] + j] = Att[j];
			ptr[Att_index[i] + MAP_COL + j] = Def[j];
		}
		ptr[Att_index[i] + 5] = land_list[i]->att + 48;
		ptr[Att_index[i] + MAP_COL + 5] = land_list[i]->def + 48;
	}





	for (i = 1; i < NODE_NUM; i++)
		if (land_list[i]->owner == 0) /*���� �������� user���� ������*/
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
			for (j = 0; j < EDGE_NUM; j++)
				ptr[NODE[i][j]] = '\\';
			for (j = 0; j < NODE_COL - 2; j++)						/*�߸� ������ ���δ� '��İ�' ä������.  */
			{
				idx = newtral_index[j];
				for (k = NODE[i][idx]; k != NODE[i][idx + 1]; k++)
					ptr[k] = '\\';
			}
			/*�߸��ε������� �ϳ��� �����ͼ� �� ���� '\'�� ĥ�Ѵ�. */

		}

	for (i = 0; i < MAP_ROW; i++)
		map[i][MAP_COL - 1] = '\n';
}

/*24���� ���� �� ������ 4���� �߸������, 10���� user�� ������, 10���� AI�� ������ �Ҵ��ϴ� �Լ�  */
void landAssign(void)
{
	/*3��, 10��, 10���� loop. ������ RAND() ��µ� ���� �̹� ���õ� ���� ��� �����ϴ� ���� �ʿ� */
	/*1, 2, 7���� ������ ������ ����. 24, 23, 18�� ������ AI�� ����*/
	int Usersland[3] = { 1, 2, 7 };
	int AIsland[3] = { 18, 23, 24 };
	int i, j, n;
	/*���ʿ��� ��� ���並 -1(�߸�����)�� ����*/

	for (i = 1; i < NODE_NUM; i++)
	{
		land_owner[i] = -1;
	}
	for (i = 0; i < 3; i++)
	{
		land_owner[Usersland[i]] = 0;
		land_owner[AIsland[i]] = 1;
	}
	srand(time(NULL));



	for (i = 0; i < 7; i++)
	{
		n = rand() % 24 + 1;
		if ((land_owner[n] == 0) || (land_owner[n] == 1))		/*�̹� ���õ� �ѹ���*/
		{
			i--;
			continue;				/*�� �ݺ� �б�� ���� �ɷ� �ϰ� �ٽ� �ݺ�*/
		}
		land_owner[n] = 0;
	}
	User->total_land = 10;


	for (i = 0; i < 7; i++)
	{
		n = rand() % 24 + 1;
		if ((land_owner[n] == 0) || (land_owner[n] == 1))
		{
			i--;
			continue;
		}
		land_owner[n] = 1;
	}
	Ai->total_land = 10;

	for (i = 1, j = 0; i < NODE_NUM; i++)
	{
		if (land_owner[i] == -1)
		{
			newtral_land[j] = i;
			j++;
		}
	}
}
void land_initialize()
{
	/*�߸������ AI, ������ ���带 ���Ƿ� �Ҵ��Ѵ�. ���ݷ°� ������ *0���� �ʱ�ȭ�Ѵ�.--> ���ݷ��� 1�̻��� ����*/

	int i, j;

	for (i = 0; i < NODE_NUM; i++)
	{
		land_list[i] = (land*)malloc(sizeof(land));
	}

	landAssign();			/*�߸������ AI, ������ ���带 ���Ƿ� �Ҵ� */
	printf("3");



	for (i = 0; i < NODE_ROW; i++)
	{
		for (j = 1; j < NODE_COL + 1; j++)
		{
			//scanf("%d", &owner); /*get 0(player) or 1(ai)*/
			land_list[i * NODE_COL + j]->att = DEFAULT_ATT;
			land_list[i * NODE_COL + j]->def = DEFAULT_DEF;
			/*1~24��° �ε����� ���� ������ �ʱ�ȭ�Ѵ�.*/
			land_list[i * NODE_COL + j]->owner = land_owner[i * NODE_COL + j];
			land_list[i * NODE_COL + j]->link = NULL;
		}
	}
}
void linkLand(int from, int to) /*FROM land�� ���� ����� TO land�� ���Խ�Ų��.*/
{
	//land_list[from]�� linked list�� TO land�� �ε��� ����. 
	/*��ũ�帮��Ʈ�� ���� ��������� ����
	from �ε����� ���� ������ ��ũ�� to �ε����� ���� ���带 �����Ѵ�. */
	land_link* temp = (land_link*)malloc(sizeof(land_link));
	temp->num = to;
	temp->next = NULL;


	if (land_list[from]->link != NULL)
	{
		temp->next = land_list[from]->link;
	}
	land_list[from]->link = temp;
}
void edge_initialize()
/*---------------------------------------*/
/*land���� ������踦 �ʱ�ȭ�Ѵ�.*/
{
	int n;
	for (n = 1; n < NODE_NUM; n++)
	{
		if (n % 6 != 0)
			linkLand(n, n + 1);
		if (n % 6 != 1)
			linkLand(n, n - 1);
		if (n <= 18)
			linkLand(n, n + 6);
		if (n > 6)
			linkLand(n, n - 6);
	}

}

