#include<iostream>
#include"Header.h"

//C_Gamemanager
using namespace std;

C_Gamemanager::C_Gamemanager()
{
	//1번 아이템 만듦
	S_Item* hppotion = new S_Item();
	hppotion->name = "HP포션";
	hppotion->effect = "체력을 회복합니다.";
	hppotion->type = 1;
	item.push_back(hppotion);

	//2번 아이템 만듦
	S_Item* mppotion = new S_Item();
	mppotion->name = "MP포션";
	mppotion->effect = "마나를 회복합니다.";
	mppotion->type = 2;
	item.push_back(mppotion);

	//3번 아이템 만듦
	S_Item* ston = new S_Item();
	ston->name = "짱돌";
	ston->effect = "단일대상에게 데미지를 줍니다. ((atk)+30)";
	ston->type = 3;
	item.push_back(ston);

	//4번 아이템 만듦
	S_Item* bomb = new S_Item();
	bomb->name = "폭탄";
	bomb->effect = "단일대상에게 큰 데미지를 줍니다.((atk)+100)";
	bomb->type = 4;
	item.push_back(bomb);

	//5번 아이템 만듦
	S_Item* weapon = new S_Item();
	weapon->name = "무기";
	weapon->effect = "공격력이 증가합니다.";
	weapon->type = 5;
	item.push_back(weapon);

	//6번 아이템 만듦
	S_Item* armor = new S_Item();
	armor->name = "방어구";
	armor->effect = "방어력이 증가합니다.";
	armor->type = 6;
	item.push_back(armor);

	//7번 아이템 만듦
	S_Item* accessories = new S_Item();
	accessories->name = "악세사리";
	accessories->effect = "최대체력이 증가합니다.";
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
double C_Player::getMAXEXP() const
{
	return this->m_MAXEXP;
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
void C_Player::SetPlusexp(double n)
{
	this->m_exp += n;
}
void C_Player::Recovery()
{
	m_hp = m_MAXHP;
	m_mp = m_MAXMP;
}
void C_Player::Arrangement()
{
	it = v_inventory.begin();
	/*
	함수는 해당 인덱스의 데이터를 지우고 그 뒤에 있는 데이터를 남은 자리만큼 앞으로 이동시킨다.
	*/
	for (it; it != v_inventory.end();)
	{
		if ((*it)->num <= 0)
		{
			it = v_inventory.erase(it);
			//erase의 반환값을 다시 it에 대입시키면
			//삭제에 성공할시 삭제한 요소의 바름 다음 it를 return한다.
			//그러므로 it에 그대로 대입시켜주면 된다.
		}
		else
		{
			++it;
		}
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
string C_Player::getitemname(int Number)
{
	return v_inventory[Number - 1]->name;
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
void C_Player::UseItem(int inputNum) //인벤토리에서 번호를 받습니다.
{
	int n_item = inputNum - 1;
	int temp = v_inventory[n_item]->type;
	string on = "장착중";
	string off = "해제";
	switch (temp)
	{
	case 1: //HP 포션
		if (this->m_hp != m_MAXHP)
		{
			v_inventory[n_item]->num--;
			Arrangement();
			if (this->m_hp + 30 > m_MAXHP)
			{
				this->m_hp = m_MAXHP;
			}
			else
			{
				m_hp + 30;
			}
		}
		else
		{
			cout << "\a(!)이미 최대 체력입니다." << endl;
			Sleep(1000);
		}
		break;
	case 2: //MP 포션
		if (this->m_mp != m_MAXMP)
		{
			v_inventory[n_item]->num--;
			Arrangement();
			if (this->m_mp + 30 > m_MAXMP)
			{
				this->m_mp = m_MAXMP;
			}
			else
			{
				m_mp + 30;
			}
		}
		else
		{
			cout << "\a(!)이미 최대 마나입니다." << endl;
			Sleep(1000);
		}
		break;
	case 3: //짱돌
		cout << "\a(!)해당 아이템은 '필드'에서만 사용 가능합니다." << endl;
		Sleep(1000);
		break;
	case 4: //폭탄
		cout << "\a(!)해당 아이템은 '필드'에서만 사용 가능합니다." << endl;
		Sleep(1000);
		break;
	case 5: //무기
		if (b_mWeapon != true)
		{
			b_mWeapon = true;
			v_inventory[n_item]->effect = on;
			m_atk += 30;
		}
		else
		{
			b_mWeapon = false;
			v_inventory[n_item]->effect = off;
			m_atk -= 30;
		}
		break;
	case 6: //방어구
		if (b_mArmor != true)
		{
			b_mArmor = true;
			v_inventory[n_item]->effect = on;
		}
		else
		{
			b_mArmor = false;
			v_inventory[n_item]->effect = off;
		}
		break;
	case 7: //악세사리
		if (b_mAccessories != true)
		{
			b_mAccessories = true;
			v_inventory[n_item]->effect = on;
			m_MAXHP += 50.00;
		}
		else
		{
			b_mAccessories = false;
			v_inventory[n_item]->effect = off;
			m_MAXHP -= 50.00;
		}
		break;
	}
}
void C_Player::UseItem(int inputNum, Monster* monster)
{
	int n_item = inputNum - 1;
	int temp = v_inventory[n_item]->type;
	string on = "장착중";
	string off = "해제";
	switch (temp)
	{
	case 1: //HP 포션
		if (this->m_hp != m_MAXHP)
		{
			v_inventory[n_item]->num--;
			Arrangement();
			if (this->m_hp + 30 > m_MAXHP)
			{
				this->m_hp = m_MAXHP;
			}
			else
			{
				m_hp + 30;
			}
		}
		else
		{
			cout << "\a(!)이미 최대 체력입니다." << endl;
			Sleep(1000);
		}
		break;
	case 2: //MP 포션
		if (this->m_mp != m_MAXMP)
		{
			v_inventory[n_item]->num--;
			Arrangement();
			if (this->m_mp + 30 > m_MAXMP)
			{
				this->m_mp = m_MAXMP;
			}
			else
			{
				m_mp + 30;
			}
		}
		else
		{
			cout << "\a(!)이미 최대 마나입니다." << endl;
			Sleep(1000);
		}
		break;
	case 3: //짱돌
		monster->SetMinorhp(this->getatk() + 30);
		v_inventory[n_item]->num--;
		Arrangement();
		break;
	case 4: //폭탄
		monster->SetMinorhp(this->getatk() + 100);
		v_inventory[n_item]->num--;
		Arrangement();
		break;
	case 5: //무기
		if (b_mWeapon != true)
		{
			b_mWeapon = true;
			v_inventory[n_item]->effect = on;
			m_atk += 30;
		}
		else
		{
			b_mWeapon = false;
			v_inventory[n_item]->effect = off;
			m_atk -= 30;
		}
		break;
	case 6: //방어구
		if (b_mArmor != true)
		{
			b_mArmor = true;
			v_inventory[n_item]->effect = on;
		}
		else
		{
			b_mArmor = false;
			v_inventory[n_item]->effect = off;
		}
		break;
	case 7: //악세사리
		if (b_mAccessories != true)
		{
			b_mAccessories = true;
			v_inventory[n_item]->effect = on;
			m_MAXHP += 50.00;
		}
		else
		{
			b_mAccessories = false;
			v_inventory[n_item]->effect = off;
			m_MAXHP -= 50.00;
		}
		break;
	}
}
void C_Player::inventory() //미완성
{
	/*
<아이템 목록>(type)
1)hp포션
2)mp포션
3)짱돌:단일대상 에게 데미지
4)폭탄:단일대상 에게 큰데미지
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
			cout << "LV : " << this->getlevel() << endl;
			cout << "HP : " << this->gethp() <<"/"<<this->m_MAXHP<<endl;
			cout << "MP : " << this->getmp() << "/" << this->m_MAXMP << endl;
			cout << "ATK: " << this->getatk() << endl;
			cout << "EXP: " << this->getexp() <<"/"<<this->m_MAXEXP<< endl;

			cout << "□□□□□□□□□□□□□□□□□□□□인벤토리□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			cout << "▶인벤토리가 비었습니다.";
			cout << endl;
			cout << endl;
			cout << "GOLD : " << this->getgold() << "G" << endl;
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
			cout << "LV : " << this->getlevel() << endl;
			cout << "HP : " << this->gethp() << "/" << this->m_MAXHP << endl;
			cout << "MP : " << this->getmp() << "/" << this->m_MAXMP << endl;
			cout << "ATK: " << this->getatk() << endl;
			cout << "EXP: " << this->getexp() << "/" << this->m_MAXEXP << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□인벤토리□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			for (NUM; it != v_inventory.end(); NUM++)
			{
				cout << NUM + 1 << " ) " << (*it)->name <<" : "<<(*it)->num<<endl;
				cout << "     "<<(*it)->effect << endl;
				cout << endl;
				++it;
			}
			cout << endl;
			cout << endl;
			cout << "GOLD : " << this->getgold() << "G" << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			cout << "◀뒤로 : 0" << endl;
			cout << "　입력 : ";
			cin.clear();
			cin >> temp;
			if (cin.fail() || temp < 0 || temp > NUM)
			{
				system("cls");
				cout << "\a!:입력이 바르지 않습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else if (temp == 0)
			{
				this->m_Location = this->m_BackLocation;
				system("cls");
				return;
			}
			else
			{
				if (v_inventory[temp - 1]->num != 0)
				{
					UseItem(temp);
					system("cls");
				}
			}
		}
	}

}
bool C_Player::inventory(Monster* monster,Command* command)
{
	int temp;
	if (this->InventorySize() == 0)
	{
		cout << "LV : " << this->getlevel() << endl;
		cout << "HP : " << this->gethp() << "/" << this->m_MAXHP << endl;
		cout << "MP : " << this->getmp() << "/" << this->m_MAXMP << endl;
		cout << "ATK: " << this->getatk() << endl;
		cout << "EXP: " << this->getexp() << "/" << this->m_MAXEXP << endl;
		cout << "□□□□□□□□□□□□□□□□□□□□인벤토리□□□□□□□□□□□□□□□□□□□□" << endl;
		cout << endl;
		cout << "▶인벤토리가 비었습니다.";
		cout << endl;
		cout << endl;
		cout << "GOLD : " << this->getgold() << "G" << endl;
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		while (1)
		{
			cout << "◀종료 : 0" << endl;
			cout << "　입력 : ";
			cin.clear();
			cin >> temp;
			if (cin.fail() || temp != 0)
			{
				cout << "\a(!):입력이 바르지 않습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		while (1)
		{
			it = v_inventory.begin();
			int NUM = 0;
			cout << "LV : " << this->getlevel() << endl;
			cout << "HP : " << this->gethp() << "/" << this->m_MAXHP << endl;
			cout << "MP : " << this->getmp() << "/" << this->m_MAXMP << endl;
			cout << "ATK: " << this->getatk() << endl;
			cout << "EXP: " << this->getexp() << "/" << this->m_MAXEXP << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□인벤토리□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			for (NUM; it != v_inventory.end(); NUM++)
			{
				cout << NUM + 1 << " ) " << (*it)->name << " : " << (*it)->num << endl;
				cout << "     " << (*it)->effect << endl;
				cout << endl;
				++it;
			}
			cout << endl;
			cout << endl;
			cout << "GOLD : " << this->getgold() << "G" << endl;
			cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;
			cout << endl;
			cout << "◀뒤로 : 0" << endl;
			cout << "　입력 : ";
			cin.clear();
			cin >> temp;
			if (temp == 0)
			{
				return false;
			}
			if (cin.fail() || temp < 0 || temp > NUM)
			{
				cout << "\a!:입력이 바르지 않습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else if (v_inventory[temp - 1]->type == 1 && this->m_hp == this->m_MAXHP)
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "\a(!)현재 이미 체력이 가득 찼습니다." << endl;
				Sleep(1000);
				return false;
			}//체력이 가득 차있을경우
			else if (v_inventory[temp - 1]->type == 2 && this->m_mp == this->m_MAXMP)
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "\a(!)현재 이미 마나가 가득 찼습니다." << endl;
				Sleep(1000);
				return false;
			}//마나가 가득 차있을경우
			else
			{
				if (v_inventory[temp - 1]->num != 0)
				{
					if (v_inventory[temp - 1]->type < 5)
					{
						command->P_commend2 = temp;
						return true;
					}
					else
					{
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "\a(!)전투중에는 사용이 불가능합니다." << endl;
						Sleep(1000);
					}					
				}
				else
				{
					return false;
				}

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
	if (this->b_mArmor != true)
	{
		this->m_hp -= n;
	}
	else
	{
		this->m_hp -= n * 0.80;
	}
}
void C_Player::SetPlushp(int n)
{
	this->m_hp += n;
}
bool C_Player::getArmor()
{
	return b_mArmor;
}
void C_Player::levelup()
{
	double temp;
	system("cls");
	cout << "\a<<<<<<<<<<<<<<<<<<<<LEVEL UP!!>>>>>>>>>>>>>>>>>>>>" << endl;
	Sleep(1000);
	cout << this->getname() << "\a의 LEVEL이 1 증가했다!!" << endl;
	Sleep(500);
	cout << this->getname() << "\a의 최대체력이 10 증가했다!!" << endl;
	Sleep(500);
	cout << this->getname() << "\a의 최대마나가 10 증가했다!!" << endl;
	Sleep(500);
	cout << this->getname() << "\a의 공격력이 10 증가했다!!" << endl;
	Sleep(500);
	cout << "LV : "<<this->getlevel() << " → " << this->getlevel()+1 << endl;
	Sleep(500);
	cout << "HP : "<<this->m_MAXHP << " → " << this->m_MAXHP + 10 << endl;
	Sleep(500);
	cout << "MP : "<<this->m_MAXMP << " → " << this->m_MAXMP + 10 << endl;
	Sleep(500);
	cout << "ATK: "<<this->m_atk << " → " << this->m_atk + 10 << endl;
	if (this->m_exp > this->m_MAXEXP)
	{
		temp = m_exp - m_MAXEXP;
		this->m_exp = 0.00;
		this->SetPlusexp(temp);
		this->m_level++;
		this->m_MAXHP += 10;
		this->m_hp = m_MAXHP;
		this->m_MAXMP += 10;
		this->m_mp = m_MAXMP;
		this->m_MAXEXP += 20;
		this->m_atk += 10;		
	}
	else
	{
		this->m_exp = 0.00;
		this->m_level++;
		this->m_MAXHP += 10;
		this->m_hp = m_MAXHP;
		this->m_MAXMP += 10;
		this->m_mp = m_MAXMP;
		this->m_MAXEXP += 20;
		this->m_atk += 10;
	}
	Sleep(2000);
	system("cls");
}





// C_Village

C_Village::C_Village()
{
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

	while (1)
	{
		switch (random)
		{
		case 1:
			Monster * born = new Born();
			UI(player, born, gamemanager);

			player->Back();
			break;
		}
		break;
	}
}

void C_Field::UI(C_Player* player, Monster* monster, C_Gamemanager* gamemanager)
{
	system("cls");
	int np_count;
	bool b_choice = false;
	bool Attack = false;
	Command* command = new Command();
	command->Preemptive = player->Decision(monster);
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
			if (command->Preemptive == true) //플레이어가 선일경우
			{
				if (np_count == 2)
				{
					cout << player->getname() << "\a의 ";
					switch (command->P_commend)
					{
					case 1:
						cout << "공격!" << endl;
						break;
					case 2:
						cout << "방어!" << endl;
						break;
					case 3:
						cout << "'" << player->getitemname(command->P_commend2) << "'" << "사용!" << endl;
						break;
					}
				}
				else if (np_count == 1)
				{
					cout << monster->getname() << "\a의 ";
					switch (command->M_commend)
					{
					case 1:
						cout << "공격!" << endl;
						if (player->getArmor())
						{
							cout << endl;
							cout << player->getname() << " \a의 방어구로 인해" << monster->getname() << " 의 데미지를 " << monster->getatk() * 0.80 << "만큼 막았다!" << endl;
						}
						break;
					case 2:
						cout << "방어!" << endl;
						break;
					}
					Attack = false;
				}
			}
			else //플레이어가 선이 아닐경우
			{
				if (np_count == 2)
				{
					cout << monster->getname() << "\a의 ";
					switch (command->M_commend)
					{
					case 1:
						cout << "공격!" << endl;
						if (player->getArmor())
						{
							cout << endl;
							cout << player->getname() << "\a의 방어구로 인해" << monster->getname() << " 의 데미지를 " << monster->getatk() * 0.80 << "만큼 막았다!" << endl;
						}
						break;
					case 2:
						cout << "방어!" << endl;
						break;
					}
				}
				else if (np_count == 1)
				{
					cout << player->getname() << "\a의 ";
					switch (command->P_commend)
					{
					case 1:
						cout << "공격!" << endl;
						break;
					case 2:
						cout << "방어!" << endl;
						break;
					case 3:
						cout <<"'"<<player->getitemname(command->P_commend2)<<"'"<<"사용!" << endl;
						break;
					}
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
			else //이곳에서 공격 , 방어 , 인벤토리를 구현합니다.
			{
				b_choice = true;
				switch (choice)
				{
				case 1:
					choice = 0;
					Attack = true;
					command->P_commend = 1;
					srand(time(NULL));
					command->M_commend = rand() % 2 + 1;
					np_count = 2;
					break;
				case 2:
					choice = 0;
					Attack = true;
					command->P_commend = 2;
					srand(time(NULL));
					command->M_commend = rand() % 2 + 1;
					np_count = 2;
					break;
				case 3:
					if (player->inventory(monster,command) != false)
					{
						choice = 0;
						Attack = true;
						command->P_commend = 3;
						srand(time(NULL));
						command->M_commend = rand() % 2 + 1;
						np_count = 2;
					}
					else
					{
						b_choice = false;
						choice = 0;
						Attack = false;
						command->P_commend = NULL;
						command->P_commend2 = NULL;
						srand(time(NULL));
						command->M_commend = NULL;
						np_count = NULL;
					}
					break;
				case 4:
					system("cls");				
					cout << player->getname() << "\a가 도망쳤습니다.!!" << endl;
					Sleep(1000);
					return;
				}
			}

		}
		else //bp_count 중일때(bp_count = true) / b_choice 가 아닐때
		{
			Sleep(1000);
			if (command->Preemptive == true) //플레이어가 선일때
			{
				switch (command->P_commend) //플레이어 선
				{
				case 1: //플레이어가 선이고 플레이어가 공격을 선택했을때
					if (np_count == 2)
					{//플레이어의 공격
						monster->SetMinorhp(player->getatk());
						np_count--;
					}
					else if (np_count == 1)
					{//몬스터의 공격
						switch (command->M_commend)
						{
						case 1:
							player->SetMinorhp(monster->getatk());
							Attack = false;
							b_choice = false;
							break;
						case 2:
							monster->SetPlushp(10);
							Attack = false;
							b_choice = false;
							break;
						}
					}
					break;
				case 2://플레이어가 선이고 플레이어가 방어를 선택했을때
					if (np_count == 2)
					{//플레이어의 공격
						player->SetPlushp(10);
						np_count--;
					}
					else if (np_count == 1)
					{//몬스터의 공격
						switch (command->M_commend)
						{
						case 1:
							player->SetMinorhp(monster->getatk());
							Attack = false;
							b_choice = false;
							break;
						case 2:
							monster->SetPlushp(10);
							Attack = false;
							b_choice = false;
							break;
						}
					}
					break;
				case 3:
					if (np_count == 2)
					{
						player->UseItem(command->P_commend2, monster);
						np_count--;
					}
					else if (np_count == 1)
					{
						switch (command->M_commend)
						{
						case 1:
							player->SetMinorhp(monster->getatk());
							Attack = false;
							b_choice = false;
							break;
						case 2:
							monster->SetPlushp(10);
							Attack = false;
							b_choice = false;
							break;
						}
					}
				}
			}
			else //플레이어가 선이 아닐때
			{
				switch (command->M_commend) //몬스터 선
				{
				case 1: //몬스터가 선이고 몬스터가 공격을 선택했을때
					if (np_count == 2)
					{ //몬스터 공격
						player->SetMinorhp(monster->getatk());
						np_count--;
					}
					else if (np_count == 1)
					{ //플레이어 공격
						switch (command->P_commend)
						{
						case 1:
							monster->SetMinorhp(player->getatk());
							Attack = false;
							b_choice = false;
							break;
						case 2:
							player->SetPlushp(10);
							Attack = false;
							b_choice = false;
							break;
						case 3:
							player->UseItem(command->P_commend2, monster);
							Attack = false;
							b_choice = false;
						}
					}
					break;
				case 2: //몬스터가 선이고 몬스터가 방어를 선택했을때
					if (np_count == 2)
					{
						monster->SetPlushp(10);
						np_count--;
					}
					else if (np_count == 1)
					{
						switch (command->P_commend)
						{
						case 1:
							monster->SetMinorhp(player->getatk());
							Attack = false;
							b_choice = false;
							break;
						case 2:
							player->SetPlushp(10);
							Attack = false;
							b_choice = false;
							break;
						case 3:
							player->UseItem(command->P_commend2, monster);
							Attack = false;
							b_choice = false;
						}
					}
					break;
				}
			}

		}
		if (monster->gethp() <= 0 || player->gethp() <= 0)
		{
			if (monster->gethp() <= 0)
			{
				system("cls");
				cout << monster->getname() << "\a(을) 처치했다!" << endl;

				cout << "<보상>--------------" << endl;
				Sleep(1000);
				cout << "\aGOLD + " << monster->getgold() << endl;
				Sleep(1000);
				cout << "\aEXP + " << monster->getexp() << endl;
				cout << "-------------------" << endl;
				Sleep(1000);
				system("cls");
				int temp = player->getgold() + monster->getgold();
				for (int i = player->getgold(); i != temp; i++)
				{
					cout << "\aGOLD : " << i;
					system("cls");
				}
				player->setgold(monster->getgold(), "+");
				player->SetPlusexp(monster->getexp());
				break;
			}
			else if (player->gethp() <= 0)
			{
				system("cls");
				GameOver(player, gamemanager);
				cout << "GAME OVER" << endl;
				cout << "3초후 화면이 종료됩니다." << endl;
				Sleep(3000);
				exit(0); //콘솔이 바로 종료된다.
				return;
			}
		}

	}
	delete command;
}


//Monster

Born::Born()
{
	this->m_name = "스켈레톤";
	this->m_level = 1;
	this->m_hp = 150;
	this->m_mp = 150;
	this->atk = 10;
	this->gold = 20;
	this->m_MAXHP = 150;
	this->m_MAXMP = 150;
	this->exp = 25.5;
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
void GameOver(C_Player* player, C_Gamemanager* manager)
{
	delete player;
	delete manager;
}