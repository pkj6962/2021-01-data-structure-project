#pragma once

typedef enum PLAYER { user = 0, ai } PLAYER;
typedef enum STATS{att = 0, def, cardnum}STATS;
typedef enum ACTION {Att = 0, Upg} ACTION;


typedef struct _tag_land_link
{
	int num; //land ��ȣ
	struct land_link* next;
}land_link;

typedef struct _tag_land {
	char att;
	char def;
	int owner;
	//land* link;
	struct land_link* link;
}land;
typedef struct player {
	int valid_land;		/*credit���μ� ��ȿ�� ������ ����(���� ����� ����)*/
	int total_land;		/*�� ������ ���� */
	int card_num;		/*��밡���� ī���� ����*/
}player;

typedef enum what { // � �׸��� ��ȭ�ϴ����� ��Ÿ���� ������ ���� 
	nothing = 0,
	atk,
	dff,
	cardraw
}what;

typedef struct card {
	struct card* left_node;
	what thing1; // ��ȭ�ϴ� ���� �������� �˷��ִ� ���� 1
	what thing2; // ��ȭ�ϴ� ���� �������� �˷��ִ� ���� 2
	int plus;
	int price;
	int buy;  // 0�� �Ȼ� ī��, 1�� �� ī�� 
	struct card* right_node;
}card;


typedef enum function {
	none = 0,  // addwork�� ���� ��.
	atck, // ����ī�� 
	upgradeatk, // ���ݷ� ��ȭ ī�� 
	upgradedef, // ���� ��ȭ ī�� 
	percard, // ������ ī����Ƚ�� ���� ī�� 
}function;

typedef struct basiccard {
	function basicwork;
	function addwork;
	int basicpower;
	int addpower;
}basiccard;

