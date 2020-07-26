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
	void kaahung()
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		int x = 0, y = 0;

		POINT pos;
		GetCursorPos(&pos);
		HWND processHANDLE = WindowFromPoint(pos);
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
		Sleep(25);
		press_key(13);//Enter
		Sleep(25);
		release_key(13);//Enter
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		pos.x = 910, pos.y = -15;
		ClientToScreen(processHANDLE, &pos);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, dx(pos.x, desktop), dy(pos.y, desktop), 0, 0);
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, dx(pos.x - 398, desktop), dy(pos.y + 387, desktop), 0, 0);
		Sleep(2750);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		press_key(13);//Enter
		Sleep(25);
		release_key(13);//Enter
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
	int dx(int p_x, RECT desktop)
	{
		float x = p_x * (65535.0 / desktop.right);
		return int(x);
	}

	int dy(int p_y, RECT desktop)
	{
		float y = p_y * (65535.0 / desktop.bottom);
		return int(y);
	} 
};