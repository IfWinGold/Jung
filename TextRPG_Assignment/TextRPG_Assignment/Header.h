#ifndef HEADER_H_
#define HEADER_H_

#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<time.h>
#include<queue>

using namespace std;


class C_Player;
class C_Village;
class C_Store;
class C_Field;
class Monster;
struct S_Item;
class C_Gamemanager;
struct S_Gamemanager;

void GameStart(C_Player* player, C_Gamemanager* manager);
void GameOver(C_Player* player, C_Gamemanager* manager);



struct Command
{
	bool Preemptive;//선후공 결정 참이면 플레이어가 선
	int P_commend;
	int P_commend2;
	int M_commend;
};

struct S_Item //아이템
{
	string name; //아이템의 이름입니다.
	string effect; //아이템의 효과입니다.
	int type; //아이템의 타입입니다.
	int num = 1;  //아이템의 개수입니다.
};

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
class C_Gamemanager
{
	vector<S_Item*> item;
	vector<S_Item*>::iterator it_item = item.begin();
public:
	C_Gamemanager(); //생성자로 아이템을 만듭니다.
	//vector<C_Monster*> monster;	
	//vector<C_Monster*>::iterator it_monster = monster.begin();
	S_Item* itempush(int n); //아이템을 생성합니다.
	~C_Gamemanager();
	void show();
	
};


class C_Player
{
	vector<S_Item*> v_inventory; //인벤토리
	vector<S_Item*>::iterator it = v_inventory.begin(); //인벤토리의 이터레이터 입니다. 

	int m_Location = 0; //현재 위치를 int형으로 표시합니다.
	int m_BackLocation = 0; //이전 위치를 int형으로 표시합니다.	
	string m_name; //닉네임
	int m_level = 1; //레벨
	double m_hp = 100.00; //체력
	double m_mp = 80.00; //마나
	int m_atk = 10; //공격력
	double m_exp = 90.00; //경험치
	int m_gold = 10000000;

	double m_MAXHP = 100.00; //최대체력 입니다.
	double m_MAXMP = 80.00; //최대마나 입니다.
	double m_MAXEXP = 100.00;

	bool b_mWeapon = false;
	bool b_mArmor = false;
	bool b_mAccessories = false;
	


public:
	~C_Player();
	void ShowStat()
	{
		cout << "LV" << m_level << "<" << m_name << ">" << endl;
		cout << "HP: " << m_hp <<"/"<<m_MAXHP<< endl;
		cout << "MP: " << m_mp <<"/"<<m_MAXMP<< endl;
		if (b_mWeapon == true)
		{
			cout << "무기 장착중(atk+30)" << endl;
		}
		if (b_mArmor == true)
		{
			cout << "방어구 장착중(데미지감소)" << endl;
		}
		if (b_mAccessories == true)
		{
			cout << "악세사리 장착중(최대HP증가)" << endl;
		}
	}
	string getname() const;
	int getlevel() const;
	double gethp() const;
	double getmp() const;
	int getatk() const;
	double getexp() const;
	int getgold() const;
	int getlocation();
	bool getArmor();
	string getitemname(int Number);
	double getMAXEXP() const;
	void Recovery();


	bool haveitem(S_Item* item); //해당 아이템을 소지하고 있는지 확인합니다.
	int getitemsize(int type); //해당 아이템의 갯수를 리턴합니다.
	int InventorySize(); //현재 인벤토리의 사이즈를 리턴합니다.
	void getitem(S_Item* item); //아이템을 휙득합니다. 그 아이템을 소지하고 있으면 그 아이템의 보유수를 ++합니다.
	void inventory(); //인벤토리를 보여줍니다.
	bool inventory(Monster* monster,Command* command);

	void UseItem(int inputNum);
	void UseItem(int inputNum, Monster* monster);

	void Arrangement();

	void setname();
	void setlocation(int n);
	bool setgold(int n, const char* oper); //값이 잘못될경우 false를 리턴
	void SetPlushp(int n);
	void SetMinorhp(int n);
	void SetPlusexp(double n);



	void Back(); //상황에 맞춰 메뉴를 뒤로 이동합니다.
	void levelup();
	bool Decision(Monster* monster); //플레이어가 레벨이 더 높으면 참


};



class C_Village
{
	//2월11일 (has - a)
	//현재 만들어야 하는것:플레이어가 마을에서 스토어 , 필드 를 왔다갔다 할 수 있도록 만들어야 한다.
	//굳이 벡터나 리스트나 벡터를 만들 필요는 없을것 같다. 
	//함수를 이용하여서 만들어보자. 
	C_Store* m_C_Store;
	C_Field* m_C_Field;


public:
	C_Village();
	~C_Village();
	void Show(); //마을의 목록을 보여줍니다.
	int input(); //마을에서 이동할 키를 입력받습니다.
	void Store(C_Player* player, C_Gamemanager* gamemanager);
	void Field(C_Player* player, C_Gamemanager* gamemanager);

};

class C_Store
{

public:
	void Show(C_Player* player, C_Gamemanager* gamemanager);

};
class C_Field
{

public:
	void Show(C_Player* player, C_Gamemanager* gamemanager);
	void UI(C_Player* player, Monster* monster,C_Gamemanager* gamemanager);


};



class Monster abstract
{
protected:
	string m_name;
	int m_level;
	double m_hp;
	double m_mp;
	double exp;
	double m_MAXHP;
	double m_MAXMP;
	int atk;
	int gold;

public:
	void ShowStat()
	{
		cout << "LV" << m_level << "<" << m_name << ">" << endl;
		cout << "HP: " << m_hp << "/" << m_MAXHP << endl;
		cout << "MP: " << m_mp << "/" << m_MAXMP << endl;
	}
	string getname()
	{
		return m_name;
	}
	int getlevel()
	{
		return m_level;
	}
	int gethp()
	{
		return m_hp;
	}
	int getmp()
	{
		return m_mp;
	}
	int getatk()
	{
		return atk;
	}
	int getgold()
	{
		return gold;
	}
	double getexp()
	{
		return exp;
	}
	void SetMinorhp(int n)
	{
		m_hp -= n;
	}
	void SetPlushp(int n)
	{
		m_hp += n;
	}

};

class Born : public Monster
{
public:
	Born(); //스켈래톤이 스텟이 지정된다.
};





#endif // !HEADER_H_
