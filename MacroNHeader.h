#pragma once
#define MAX_TURNS 100
#define MAX 50
#define MAP_ROW 33
#define MAP_COL 110

#define NODE_ROW 4
#define NODE_COL 6 

#define LINE_NUM 3		/*���带 �����ϴ� ���� ������ ��('-')�� ����*/
#define EDGE_NUM 30		/* ���� ����(�׵θ� ������) ����*/
#define NODE_NUM 24+1		//24��. �ε����� 1���� �����ϹǷ� plus 1
#define EDGE_COL_NUM 18 + 1		/*������ ����� ���带 �����ϴ� ������ ����*/
#define NUM 20

#define DEFAULT_ATT 5
#define MIN_ATT 1		/*�ڱ� ���ݷ��� ��� �������� �� �ּ� ���ݷ�*/
#define DEFAULT_DEF 10

#define DEFAULT_AI_INCREMENT 5 /*Ai�� ���׷��̵� �� default ������  */

#define DEFAULT_CARD_AVAIL 1	/*�÷��̾ ��밡���� �⺻ ī�� ���� */
#define MAX_STATS 35	/*stat(���ݷ°� ����)�� �ִ� */


#define MAX_CARD_NUM 6
#define GAME_TURN_NUM 3
#define SUGGEST_CARD_NUM 6	/*�������� ���õǴ� ī���� ����*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>