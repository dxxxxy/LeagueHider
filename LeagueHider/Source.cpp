#include <iostream>
#include <Windows.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>

//get all window titles
/*BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (!IsWindowVisible(hwnd)) return TRUE;
	char class_name[250];
	char title[250];
	GetClassNameA(hwnd, class_name, sizeof(class_name));
	GetWindowTextA(hwnd, title, sizeof(title));
	std::cout << "Window title: " << title << std::endl;
	std::cout << "Class name: " << class_name << std::endl << std::endl;
	return TRUE;
}*/
//test
IAudioEndpointVolume* GetEndpointVolume() {
	HRESULT hr;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
	IMMDevice* defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume* endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;
	return endpointVolume;
}

bool SetMute(bool mute) {
	HRESULT hr;
	CoInitialize(NULL);
	IAudioEndpointVolume* endpointVolume = GetEndpointVolume();
	hr = endpointVolume->SetMute((bool)(mute), NULL);
	endpointVolume->Release();
	CoUninitialize();
	return 0;
}

bool close = false;

int main() {
	//EnumWindows(EnumWindowsProc, NULL);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	while (true) {
		if (GetAsyncKeyState(VK_INSERT)) {
			close = !close;

			HWND hWnd = FindWindowA(NULL, "League of Legends (TM) Client"); //find the league client handle
			ShowWindow(hWnd, close ? SW_HIDE : SW_SHOW);
			SetMute(close); //system mute
		}
		else if (GetAsyncKeyState(VK_END)) {
			Beep(500, 500);
			return 0;
		}
		Sleep(100);
	}
}