#include <iostream>
#include <Windows.h>

bool close = false;

int main() {
	Beep(900, 500);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	while (true) {
		if (GetAsyncKeyState(VK_INSERT)) {
			close = !close;

			HWND hWnd = FindWindowA(NULL, "League of Legends (TM) Client"); //find the league gamet handle
			HWND hWnd2 = FindWindowA(NULL, "League of Legends"); //find the league client handle

			ShowWindow(hWnd, close ? SW_HIDE : SW_SHOW);
			ShowWindow(hWnd2, close ? SW_HIDE : SW_SHOW);

			std::system("nircmd.exe muteappvolume LeagueClientUxRender.exe 2");
			std::system("nircmd.exe muteappvolume LeagueClientUx.exe 2");

			DWORD pid;
			GetWindowThreadProcessId(hWnd, &pid);
			CHAR buf[100];

			sprintf_s(buf, sizeof(buf), "nircmd.exe muteappvolume /%d 2", pid);

			std::system(buf);
		}
		else if (GetAsyncKeyState(VK_END)) {
			Beep(500, 500);
			return 0;
		}
		Sleep(100);
	}
}
