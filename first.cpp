#include <Windows.h>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

map<BYTE, bool> keyState;
map<BYTE, BYTE> keyMap;
map<BYTE, BYTE> keyMap1 = {
	{0x51, 0x42}, // Q -> A
	{0x57, 0x42}, // W -> B
	{0x45, 0x43}, // E -> C
	{0x52, 0x44}, // R -> D
	{0x54, 0x45}, // T -> E
	{0x59, 0x46}, // Y -> F
	{0x55, 0x47}, // U -> G
	{0x49, 0x48}, // I -> H
	{0x4F, 0x49}, // O -> I
	{0x50, 0x4A}, // P -> J
	{0x41, 0x4B}, // A -> K
	{0x53, 0x4C}, // S -> L
	{0x44, 0x4D}, // D -> M
	{0x46, 0x4E}, // F -> N
	{0x47, 0x4F}, // G -> O
	{0x48, 0x50}, // H -> P
	{0x4A, 0x51}, // J -> Q
	{0x4B, 0x52}, // K -> R
	{0x4C, 0x53}, // L -> S
	{0x5A, 0x54}, // Z -> T
	{0x58, 0x55}, // X -> U
	{0x43, 0x56}, // C -> V
	{0x56, 0x57}, // V -> W
	{0x42, 0x58}, // B -> X
	{0x4E, 0x59}, // N -> Y
	{0x4D, 0x5A}, // M -> Z
	{0x31, 41},	  // 1 to Ctrl+A (Select All)
};

void assign_default()
{
	keyMap = keyMap1;
}

void assign_user()
{
	keyMap.clear();
	ifstream configFile("config.txt");
	if (!configFile.is_open())
	{
		cout << "Not able to open config file" << endl;
		return;
	}

	string line;
	while (getline(configFile, line))
	{
		istringstream iss(line);
		BYTE originalKey, remappedKey;
		if (iss >> originalKey >> remappedKey)
		{
			keyMap[originalKey] = remappedKey;
		}
	}
	configFile.close();
}

void action1(BYTE key)
{
	if (key == 41)
	{
		keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0x1d, 0, 0);
		Sleep(1);
		keybd_event(0x41, 0, 0, 0);
		Sleep(1);
		keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
		Sleep(10);
		keybd_event(VK_CONTROL, 0x1d, KEYEVENTF_KEYUP, 0);
		Sleep(10);
	}
	else
	{
		keybd_event(0x08, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(0x08, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	}
}

int main()
{
	assign_default();
	cout << "Do you want to use your own cofiguration file ?\nIf yes press 1 and enter, else press 2" << endl;
	int temp;
	cin >> temp;

	if (temp == 1)
	{
		assign_user();
	}
	else
	{
		assign_default();
	}

	int flag1 = false;

	while (true)
	{
		// Sleep(1);
		if (GetAsyncKeyState(0x10) < 0)
		{
			if (flag1)
			{
				assign_user();
				Sleep(1);
			}
			else
			{
				assign_default();
				Sleep(1);
			}
			flag1 = !flag1;
		}
		for (const auto &pair : keyMap)
		{
			if (GetAsyncKeyState(pair.first) < 0)
			{
				if (!keyState[pair.first])
				{
					action1(pair.second);
					keyState[pair.first] = true;
				}
			}
			else
			{
				keyState[pair.first] = false;
			}
		}
	}

	return 0;
}

// int main()
// {
// 	while (true)
// 	{
// 		// 1->Ctrl+A
// 		if (GetAsyncKeyState(0x31))
// 		{
// 			action2(0x41, 0x31);
// 		}
// 	}
// 	return 0;
// }

// int main()
// {
// 	while (true)
// 	{
// 		// Sleep(1);
// 		for (const auto &pair : keyMap)
// 		{
// 			if (GetAsyncKeyState(pair.first) < 0)
// 			{
// 				if (!keyState[pair.first])
// 				{
// 					action1(pair.second);
// 					keyState[pair.first] = true;
// 				}
// 			}
// 			else
// 			{
// 				keyState[pair.first] = false;
// 			}
// 		}
// 	}

// 	return 0;
// }

// #include <Windows.h>
// #include <iostream>
// #include <conio.h>
// #include<map>

// using namespace std;

// void action1(BYTE A) {
//     Sleep(10);
//     keybd_event(0x08, 0, KEYEVENTF_EXTENDEDKEY, 0);
//     keybd_event(0x08, 0, KEYEVENTF_KEYUP, 0);
//     Sleep(100);
//     keybd_event(A, 0, KEYEVENTF_EXTENDEDKEY, 0);
//     Sleep(1);
//     keybd_event(A, 0, KEYEVENTF_KEYUP, 0);
//     Sleep(10);
// }

// map<BYTE, bool> keyState;

// int main()
// {
// 	while (true) {
//     //Q->A
//     if (GetAsyncKeyState(0x51) && !keyState[0x51]) {
// 	action1(0x41);
// 	keyState[0x51] = true;
// }//W->B
// else if (GetAsyncKeyState(0x57) && !keyState[0x57]) {
// 	action1(0x42);
// 	keyState[0x57] = true;
// }//E->C
// else if (GetAsyncKeyState(0x45) && !keyState[0x45]) {
// 	action1(0x43);
// 	keyState[0x45] = true;
// }//R->D
// else if (GetAsyncKeyState(0x52) && !keyState[0x52]) {
// 	action1(0x44);
// 	keyState[0x52] = true;
// }//T->E
// else if (GetAsyncKeyState(0x54) && !keyState[0x54]) {
// 	action1(0x45);
// 	keyState[0x54] = true;
// }//Y->F
// else if (GetAsyncKeyState(0x59) && !keyState[0x59]) {
// 	action1(0x46);
// 	keyState[0x59] = true;
// }//U->G
// else if (GetAsyncKeyState(0x55) && !keyState[0x55]) {
// 	action1(0x47);
// 	keyState[0x55] = true;
// }
// }

// }