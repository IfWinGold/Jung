#include<iostream>
#include"Header.h"

//C_Gamemanager

C_Gamemanager::C_Gamemanager()
{
	//1번 아이템 만듦
	S_Item* hppotion = new S_Item();
	hppotion->name = "HP포션";
	hppotion->effect = "체력을 10 회복합니다.";
	hppotion->type = 1;
	item.push_back(hppotion);

	//2번 아이템 만듦
	S_Item* mppotion = new S_Item();
	mppotion->name = "MP포션";
	mppotion->effect = "마나를 10 회복합니다.";
	mppotion->type = 2;
	item.push_back(mppotion);

	//3번 아이템 만듦
	S_Item* ston = new S_Item();
	ston->name = "짱돌";
	ston->effect = "단일대상에게 40의 데미지를 줍니다.";
	ston->type = 3;
	item.push_back(ston);

	//4번 아이템 만듦
	S_Item* bomb = new S_Item();
	bomb->name = "폭탄";
	bomb->effect = "다수의 대상에게 30의 데미지를 줍니다.";
	bomb->type = 4;
	item.push_back(bomb);

	//5번 아이템 만듦
	S_Item* weapon = new S_Item();
	weapon->name = "무기";
	weapon->effect = "데미지가 20 증가합니다.";
	weapon->type = 5;
	item.push_back(weapon);

	//6번 아이템 만듦
	S_Item* armor = new S_Item();
	armor->name = "방어구";
	armor->effect = "방어력이 20 증가합니다.";
	armor->type = 6;
	item.push_back(armor);

	//7번 아이템 만듦
	S_Item* accessories = new S_Item();
	accessories->name = "악세사리";
	accessories->effect = "HP가 100 증가합니다.";
	accessories->type = 7;
	item.push_back(accessories);
}
S_Item* C_Gamemanager::itempush(int n)
{
	n--;
	S_Item* temp = new S_Item();
	temp->name = item[n]->name;
	temp->effect = item[n]->effect;
	temp->num = item[n]->num;
	temp->type = item[n]->type;

	return temp;
}
C_Gamemanager::~C_Gamemanager()
{
	item.clear();
}
void C_Gamemanager::show()
{
	for (it_item = item.begin(); it_item != item.end(); ++it_item)
	{
		cout << (*it_item)->name << endl;
	}
}









//C_Plyaer 
C_Player::~C_Player()
{
	v_inventory.clear();
}

void C_Player::setname()
{
	cin >> C_Player::m_name;
}
string C_Player::getname() const
{
	return C_Player::m_name;
}
int C_Player::getlevel() const
{
	return C_Player::m_level;
}
double C_Player::gethp() const
{
	return C_Player::m_hp;
}
double C_Player::getmp() const
{
	return C_Player::m_mp;
}
int C_Player::getatk() const
{
	return C_Player::m_atk;
}
double C_Player::getexp() const
{
	return C_Player::m_exp;
}
void C_Player::setlocation(int n)
{
	this->m_BackLocation = this->m_Location;
	this->m_Location = n;
}
int C_Player::getlocation()
{
	return this->m_Location;
}
int C_Player::getgold() const
{
	return this->m_gold;
}
bool C_Player::setgold(int n, const char* oper = "+")
{
	if (oper == "+")
	{
		this->m_gold += n;
		return true;
	}
	else if (oper == "-")
	{
		this->m_gold -= n;
		return true;
	}
	else
	{
		return false;
	}
}
bool C_Player::haveitem(S_Item* item)
{
	for (it = v_inventory.begin(); it != v_inventory.end(); ++it)
	{
		if ((*it)->type == item->type)
		{
			return true; //해당 아이템을 소지하고 있다.
		}
	}
	return false; //해당 아이템을 소지하고 있지 않다.
}
void C_Player::getitem(S_Item* item)
{
	if (haveitem(item) == false) //해당 아이템을 소지하고 있지 않으면
	{
		this->v_inventory.push_back(item);
	}
	else if (haveitem(item) == true) //소유하고 있다면
	{
		for (it = v_inventory.begin(); (*it)->type != item->type; ++it)
		{
		}
		(*it)->num++;
	}
}
int C_Player::getitemsize(int m_type)
{
	int temp = 0;
	for (it = v_inventory.begin(); it != v_inventory.end(); ++it)
	{
		if ((*it)->type == m_type)
		{
			temp++;
		}
	}
	return temp;
}
void C_Player::inventory() //미완성
{
	/*
<아이템 목록>
1)hp포션
2)mp포션
3)짱돌:단일대상에게 데미지
4)폭탄:다수의 적에게 데미지
------------------------
5)무기:데미지 증가
6)방어구:방어력
7)악세사리:HP증가
*/
	int temp;
	if (this->InventorySize() == 0)
	{
		while (1)
		{
			cout << endl;
			cout << endl;
			cout << "GOLD : " << this->getgold() << "G" << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□인벤토리□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			cout << "▶인벤토리가 비었습니다.";
			cout << endl;
			cout << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "◀뒤로 : 0" << endl;
			cout << "　입력 : ";
			cin.clear();
			cin >> temp;
			if (cin.fail() || temp != 0)
			{
				system("cls");
				cout << "\a!:입력이 바르지 않습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else
			{
				this->m_Location = this->m_BackLocation;
				system("cls");
				return;
			}
		}
	}
	else
	{
		while (1)
		{
			it = v_inventory.begin();
			int NUM = 0;
			cout << endl;
			cout << endl;
			cout << "GOLD : " << this->getgold() << "G" << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□인벤토리□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			for (NUM; it != v_inventory.end(); NUM++)
			{
				cout << NUM + 1 << " ) " << (*it)->name << " : " << (*it)->num << endl;
				++it;
			}
			cout << endl;
			cout << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "◀뒤로 : 0" << endl;
			cout << "　입력 : ";
			cin.clear();
			cin >> temp;
			if (cin.fail() || temp != 0)
			{
				system("cls");
				cout << "\a!:입력이 바르지 않습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else
			{
				this->m_Location = this->m_BackLocation;
				system("cls");
				return;
			}
		}
	}

}
int C_Player::InventorySize()
{
	return this->v_inventory.size();
}
void C_Player::Back() //상황에 맞춰 메뉴를 뒤로 이동합니다.
{
	this->m_Location = this->m_BackLocation;
	system("cls");
}
bool C_Player::Decision(Monster* monster)
{
	int lvPlayer = this->getlevel();
	int lvMonster = monster->getlevel();
	bool temp = lvPlayer >= lvMonster;
	return temp;
}
void C_Player::SetMinorhp(int n)
{
	this->m_hp -= n;
}
void C_Player::SetPlushp(int n)
{
	this->m_hp += n;
}






// C_Village

C_Village::C_Village()
{
	cout << "store = " << &m_C_Store << endl;
	cout << "field = " << &m_C_Field << endl;
}
C_Village::~C_Village()
{
	delete m_C_Store;
	delete m_C_Field;
}
void C_Village::Show()
{
	cout << "--------------------------------" << endl;
	cout << "1)인벤토리 정비하기" << endl;
	cout << "2)상점" << endl;
	cout << "3)필드" << endl;
	cout << "--------------------------------" << endl;
}
int C_Village::input()
{
	int in;
	cout << "입력: ";
	cin >> in;
	if (cin.fail())
	{
		system("cls");
		cout << "\a(!)입력이 모호합니다." << endl;;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	else
	{
		return in;
	}
}
void C_Village::Store(C_Player* player, C_Gamemanager* gamemanager)
{
	m_C_Store->Show(player, gamemanager);
}
void C_Village::Field(C_Player* player, C_Gamemanager* gamemanager)
{
	m_C_Field->Show(player, gamemanager);
}






//C_Store
void C_Store::Show(C_Player* player, C_Gamemanager* gamemanager)
{
	while (1)
	{
		int choice;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "□□□□□□□□□□□□□□□□□□□□상점□□□□□□□□□□□□□□□□□□□□" << endl;
		cout << endl;
		cout << "1) HP포션   10 G\n" << endl;
		cout << "2) MP포션   10 G\n" << endl;
		cout << "3) 짱돌     40 G\n" << endl;
		cout << "4) 폭탄     100G\n" << endl;
		cout << "5) 무기     500G\n" << endl;
		cout << "6) 방어구   500G\n" << endl;
		cout << "7) 악세사리 500G\n" << endl;
		cout << endl;
		cout << endl;
		cout << "                                      Gold : " << player->getgold() << "G" << endl;
		cout << endl;
		cout << endl;
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;

		cout << "반갑습니다 손님! 원하시는 번호를 입력해주세요!\n" << endl;
		cout << "◀뒤로 : 0" << endl;
		cout << "입력 : ";
		cin >> choice;
		if (cin.fail() || choice <= -1 || choice > 7)
		{
			system("cls");
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << endl;
			cout << "\a(!)입력이 바르지 않습니다." << endl;
			cout << endl;
			choice = -1;
		}
		cout << "choice = " << choice;
		switch (choice)
		{
		case -1:
			break;
		case 0:
			player->Back();
			return;
		case 1: //HP포션
			if (player->getgold() < 10)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(10, "-");
				player->getitem(gamemanager->itempush(1));
				system("cls");
			}
			break;
		case 2://MP포션
			if (player->getgold() < 10)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(10, "-");
				player->getitem(gamemanager->itempush(2));
				system("cls");
			}
			break;
		case 3://짱돌
			if (player->getgold() < 40)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(40, "-");
				player->getitem(gamemanager->itempush(3));
				system("cls");
			}
			break;
		case 4:
			if (player->getgold() < 100)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(100, "-");
				player->getitem(gamemanager->itempush(4));
				system("cls");
			}
			break;
		case 5:
			if (player->getgold() < 500)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(500, "-");
				player->getitem(gamemanager->itempush(5));
				system("cls");
			}
			break;
		case 6:
			if (player->getgold() < 500)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(500, "-");
				player->getitem(gamemanager->itempush(6));
				system("cls");
			}
			break;
		case 7:
			if (player->getgold() < 500)
			{
				cout << "\a(!)소지금이 부족합니다." << endl;
				Sleep(1000);
				break;
			}
			else
			{
				player->setgold(500, "-");
				player->getitem(gamemanager->itempush(7));
				system("cls");
			}
			break;
		}

	}
}



//C_Field

void C_Field::Show(C_Player* player, C_Gamemanager* gamemanager)
{
	srand(time(NULL));
	int random = 1;//rand() % 3 + 1;

	while(1)
	{
		switch(random)
		{
		case 1:
		{
			Monster* born = new Born();
			UI(player, born);
		}
			break;
		case 2:
		{

		}
			break;
		case 3:
		{

		}
			break;
		}
	}
}

void C_Field::UI(C_Player* player, Monster* monster)
{
	system("cls");
	int np_count;
	bool bp_count = false;
	bool b_choice = false;
	bool Attack = false;
	Commend* commend = new Commend();
	commend->Preemptive = player->Decision(monster);
	//Preemptive 가 true 이면 player가 선공 아니면 후공

	cout << "---------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << monster->getname() << " (을)를 조우했다!" << endl;
	cout << endl;
	cout << endl;
	cout << "---------------------------------" << endl;
	Sleep(2000);
	while (1)
	{
		int choice;
		system("cls");
		cout << "-----------------------------------" << endl;
		monster->ShowStat();
		cout << "-----------------------------------" << endl;
		cout << endl;
		if (Attack != true)
		{
			cout << "                VS                  " << endl;
		}
		else
		{
			if (commend->Preemptive == true)
			{
				if (np_count == 2)
				{
					cout << player->getname() << "의 공격!" << endl;

				}
				else if (np_count == 1)
				{
					cout << monster->getname() << "의 공격!" << endl;
					Attack = false;
				}
			}
			else
			{
				if (np_count == 2)
				{
					cout << monster->getname() << "의 공격!" << endl;

				}
				else if (np_count == 1)
				{
					cout << player->getname() << "의 공격!" << endl;
					Attack = false;
				}
			}
		}
		cout << endl;
		cout << "-----------------------------------" << endl;
		player->ShowStat();
		cout << "-----------------------------------" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "<선택>" << endl;
		cout << "-----------------------------------" << endl;
		cout << "1: 공격       2: 방어" << endl;
		cout << "3: 인벤토리   4: 도망간다!" << endl;
		cout << "-----------------------------------" << endl;
		if (b_choice != true) //명령줄을 입력제어 할 수 있음
		{
			cout << "입력 : ";
			cin >> choice;
			if (cin.fail() || choice >= 5 || choice <= 0)
			{
				cout << "\a" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				choice = -1;
				cout << "b_choice = " << b_choice << endl;
			}
			else
			{
				b_choice = true;
				switch (choice)
				{
				case 1:
					choice = 0;
					Attack = true;
					commend->P_commend = 1;
					commend->M_commend = rand() % 2 + 1;
					np_count = 2;
					bp_count = true;
					break;
				}
			}

		}
		else //bp_count 중일때(bp_count = true)
		{
			Sleep(1000);
			if (commend->Preemptive == true)
			{
				if (np_count == 2)
				{//플레이어의 공격
					monster->SetMinorhp(player->getatk());
					np_count--;
				}
				else if (np_count == 1)
				{//몬스터의 공격
					player->SetMinorhp(monster->getatk());
					Attack = false;
					b_choice = false;
				}
			}
			else
			{
				if (np_count == 2)
				{//몬스터의 공격
					player->SetMinorhp(monster->getatk());		
					np_count--;
				}
				else if (np_count == 1)
				{//플레이어의 공격
					monster->SetMinorhp(player->getatk());
					Attack = false;
					b_choice = false;
				}
			}

		}//bp_count 중일때(bp_count = true)
			
	}
	delete commend;
}


//Monster

Born::Born()
{
	this->name = "스켈레톤";
	this->level = 1;
	this->hp = 10;
	this->mp = 10;
	this->atk = 10;
	this-> gold = 20;
}


void GameStart(C_Player* player, C_Gamemanager* manager)
{
	cout << "게임을 시작합니다." << endl;
	cout << endl;
	cout << "-------------------------" << endl;
	cout << "이름 : ";
	player->setname();
	system("cls");
	cout << "-------------------------------------" << endl;
	cout << "LV  : " << player->getlevel() << endl;
	cout << "NAME: " << player->getname() << endl;
	cout << "HP  : " << player->gethp() << endl;
	cout << "MP  : " << player->getmp() << endl;
	cout << "ATK : " << player->getatk() << endl;
	cout << "EXP : " << player->getexp() << endl;
	cout << "-------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "모든 출정을 준비완료 하였습니다." << endl;
	cout << "5초후 마을로 이동합니다." << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	Sleep(5000);
	system("cls");
	cout << "마을로 이동합니다."; //아이템 게임매니저에 등록
	Sleep(500);

	system("cls");
	cout << "마을로 이동합니다.  .";
	Sleep(500);
	system("cls");
	cout << "마을로 이동합니다.  .  .";
	Sleep(500);

	system("cls");
}