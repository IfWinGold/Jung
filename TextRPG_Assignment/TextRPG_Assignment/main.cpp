#include<iostream>
#include"Header.h"

void main()
{
	/*
	업데이트 날짜 : 2021-02-23 23:09

	<해놓은것> 
	*필드->전투 소량 구현


	<해야할것> 
	*void C_Field::UI 에서 
	  방어 , 인벤토리 , 도망 구현
	  Header.cpp -> 536 줄 
	*/
	C_Player* player = new C_Player;
	C_Gamemanager* gamemanager = new C_Gamemanager;
	//GameStart(player,gamemanager);
	C_Village village;
	cout << "Test " << player->InventorySize() << endl;

	int test1 = 10;
	int test2 = 20;


	while (1)
	{
		village.Show(); //입력창을 보여줍니다.
		player->setlocation(village.input());
		switch (player->getlocation())
		{
		case 1: //인벤토리
			system("cls");
			player->inventory();
			break;
		case 2: //상점
			system("cls");
			village.Store(player, gamemanager);
			break;
		case 3: //필드
			system("cls");
			village.Field(player, gamemanager);
			break;
		}
	}	
	//cout << "1) HP포션   10 G\n" << endl;
	//cout << "2) MP포션   10 G\n" << endl;
	//cout << "3) 짱돌     40 G\n" << endl;
	//cout << "4) 폭탄     100G\n" << endl;
	//cout << "5) 무기     500G\n" << endl;
	//cout << "6) 방어구   500G\n" << endl;
	//cout << "7) 악세사리 500G\n" << endl;
	//소멸
	delete player;
	delete gamemanager;
}