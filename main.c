#pragma once
#include "MacroNHeader.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"

int main(void)
{
	int output;
	int end=1;
	int n;
	setbasiccard();




	while(end){
		system("cls");
		printf("� �ൿ�� �� �� �������ּ���\n");
		printf("1 : ����    2 : �����̿�   3 : ���Ӳ��� => ");
		scanf(" %d", &n);
		switch(n)
		{ 
		case(1):system("cls");
				output = GameProgress(); 
				break; 
		case(2): system("cls");
				 buy();
				 break;
		case(3): end = 0;  break;
		default: 	
				printf("\n�߸��� �Է��Դϴ�. �ٽ� ������ �ּ���. ������ 1~4�� �����մϴ�\n");
				system("pause");
				break;
		}
		printf("Bye!\n"); 
	}
	return 0;
}










