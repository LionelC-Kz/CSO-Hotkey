#pragma once
#include "pch.h"

class CSOScript
{
public:
	void GF2()
	{
		press_key('G');
		release_key('G');
		press_key(113);
		release_key(113);
	}

	void Singgimdefence()
	{
		press_key(51);//3
		Sleep(125);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(25);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(25);
		press_key(113);//F2
		Sleep(25);
		release_key(51);//3
		Sleep(25);
		release_key(113);//F2
		press_key(81);//Q
		release_key(81);//Q
		Sleep(2730);
	}

	void DPS_Left()
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(520);
		press_key('J');
		Sleep(15);
		release_key('J');
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(200);
		press_key(51);//3
		Sleep(25);
		release_key(51);//3
		Sleep(25);
	}
	void DPS_Right()
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(300);
		press_key('J');
		Sleep(5);
		release_key('J');
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(200);
		press_key(51);//3
		Sleep(25);
		release_key(51);//3
		Sleep(25);
	}
private:
	BYTE scan_code(DWORD pKey)
	{
		const DWORD result = MapVirtualKey(pKey, MAPVK_VK_TO_VSC);
		return (BYTE)(result);
	}
	void press_key(DWORD pKey)
	{
		keybd_event((BYTE)(pKey), scan_code(pKey), 0, 0);
	}
	void release_key(DWORD pKey)
	{
		keybd_event((BYTE)(pKey), scan_code(pKey), KEYEVENTF_KEYUP, 0);
	}
};