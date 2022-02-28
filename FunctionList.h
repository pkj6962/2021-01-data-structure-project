#pragma once
void player_initialize();
void map_initialize();
void landAssign(void);
void land_initialize();
void edge_initialize();
void capital_initialize();

void print_basic_info();
void print_map();
void printLink(int idx);
void printAction(int player, int action, int stats, int from, int to, int value_before_change);
void connection_with_capital(void);
void linkLand(int from, int to); /*FROM land�� ���� ����� TO land�� ���Խ�Ų��.*/

void user_choice(int*);		
void ai_choice(void);		
void attack(int player);
void upgrade(int player, int stats, int increment);

void ai_attack(void);		/*���� ���� */
void findTarget(int player, int* from, int* to); /*AI�� ������ ���ݷ�Ʈ�� ã�� �Լ�*/

int GameProgress(void);
int WinOrLose(void); 

void dfs(int*, int v);		/*���� ���� */
void push(int idx);
int pop(void);
int is_Empty(void);

int* cardShuffle();  /*8���� ī�� �� k���� ī�带 �̴´�. */
void suggestCard(int*); 
void select_card(int*); 

void buy(void); 
void show(card* target);
void setbasiccard(); // ������� �⺻ ���� �����ϴ� �Լ� 
void printbox(char* str);
void gentreeatk(card** temp);
void gentreeatkplus(card** temp);
void gentreedefplus(card** temp);
void gentreecarduse(card** temp);
card* check(card** target);
