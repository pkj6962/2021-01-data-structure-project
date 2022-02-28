#pragma once
#include "MacroNHeader.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"

int GameProgress()
{
	/*������ �����ؼ� �������� ���� ������ ������ �Լ�.
	�̱�� 1��, ���� 0, ���º��̸� -1��  ��ȯ�Ѵ�.*/
	/*�Ǽ��� Default Value�� ���� ��. �ϴ� 20������ �Ѵ�.
	20���� �� ���ų�, �÷��̾ ������ ������ �����ϸ� ������ ������.
	���� �� ������ �� ���� ��ȿ������ ������ ���� ��, �а� �����ȴ�.
	��ȿ������ ���� �����ϸ� �� ������ ���� ���Ͽ� �����Ѵ�.
	�� ������ ���� ��� ������ ���º� ó���ȴ�.*/
	//int remaining_turns = GAME_TURN_NUM;
	int* card_list; 
	printf("������ �����մϴ�.\n");

	do {
		printf("���̵��� �Է��ϼ���(1-10)\n");
		scanf("%d", &level);
		if (!(level >= 1 && level <= 10))
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		else
			break; 
	} while (1); 
	

	printf("���並 �Ҵ��ϴ� ���Դϴ�.\n");
	Sleep(2000);
	printf("�߸����븦 �����ϴ� ���Դϴ�...");
	Sleep(2000);


	player_initialize();
	land_initialize();
	edge_initialize();
	map_initialize();
	capital_initialize();
	connection_with_capital();

	while (remaining_turns > 0)	/*������ ������带 ���ΰ� ������ �ִ� ����*/
	{
		print_basic_info();
		print_map();

		card_list = cardShuffle();
		setbasiccard();
		suggestCard(card_list);
		user_choice(card_list);
		if (land_owner[24] == user)
			return 1;
		ai_choice();
		if (land_owner[1] == ai)
			return 0;
		remaining_turns--;

		system("pause"); 
	}	
	return WinOrLose(); 
}
/*������ ���и� �����ִ� �Լ�*/
int WinOrLose(void)
{
	printf("������ �������ϴ�. ���и� �����մϴ�.\n");
	printf("��ȿ ������ ��: User	%2d : %2d	Ai\n", User->valid_land, Ai->valid_land);
	printf("  �� ������ ��: User	%2d : %2d	Ai\n", User->total_land, Ai->total_land);
	Sleep(2000);
	if (User->valid_land > Ai->valid_land) {
		printf("������ �¸��Ͽ����ϴ�!");
		return 1;
	}
	else if (User->valid_land < Ai->valid_land) {
		printf("AI�� �¸��Ͽ����ϴ�!");
		return 0;
	}
	else if (User->total_land > Ai->total_land) {
		printf("User�� �¸��Ͽ����ϴ�!\n");
			return 1;
	}
	else if (User->total_land < Ai->total_land) {
		printf("AI�� �¸��Ͽ����ϴ�!\n");
		return 0;
	}
	else {
		printf("���º� ó���Ǿ����ϴ�.");
		return -1;
	}
	system("pause");
	}
	