#include "spotify.hpp"
#include "binary.h"


std::wstring get_files_directory()
{
	std::string str = g_folder->spotify_path;
	std::wstring widestr = std::wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();
	std::wstring sz_dir = (std::wstring(widecstr) + L"\\");
	return sz_dir;
}

std::wstring get_file_name_directory(std::wstring type_file)
{
	std::wstring sz_file = get_files_directory() + type_file;
	return sz_file;
}

bool dll_dwn(std::wstring path)
{
	HANDLE h_file;
	BOOLEAN b_status = FALSE;
	DWORD byte = 0;

	h_file = CreateFileW(path.c_str(), GENERIC_ALL, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_EXISTS)
		return true;

	if (h_file == INVALID_HANDLE_VALUE)
		return false;

	b_status = WriteFile(h_file, binary, sizeof(binary), &byte, nullptr);
	CloseHandle(h_file);

	if (!b_status)
		return false;

	return true;
}


void folder::setup()
{
	
	std::filesystem::path p = g_folder->spotify_path;
	auto chromeelf_backup = g_folder->spotify_path + "\\chrome_elf_backup.dll";
	std::wstring sz_dll = get_file_name_directory(L"chrome_elf.dll");
	if (!std::filesystem::exists(chromeelf_backup))
	{
		system("TASKKILL /F /IM spotify.exe >NUL 2> 1");
		try
		{
		
			std::filesystem::rename(p / "chrome_elf.dll", p / "chrome_elf_backup.dll");
			Sleep(2000);
			dll_dwn(sz_dll);
			//wprintf(L"%s\n", sz_dll);
			Sleep(2000);
			ShellExecute(NULL, ("runas"), ("Spotify.exe"), NULL, g_folder->spotify_path.c_str(), SW_SHOWNORMAL);
			std::cout << YELLOW "\n  [SUCCES]  :  " RESET << YELLOW "BlockSpotify ACTIVE" RESET << std::endl;
	
		
		}
		catch (...)
		{
			std::cout << RED "\n  [ERROR]  :  " RESET << YELLOW "chrome_elf.dll" <<  RED " NOT FOUND" RESET << std::endl;
		}
	
	}
	else
	{
		std::cout << RED "\n  [ERROR]  :  " RESET << YELLOW "YOU ALREADY HAVE THIS " RESET << std::endl;
	}

}


void folder::removeall()
{
	std::filesystem::path p = g_folder->spotify_path;
	auto chromeelf_backup = g_folder->spotify_path + "\\chrome_elf_backup.dll";
	auto chromeelf = g_folder->spotify_path + "\\chrome_elf.dll";
	if (std::filesystem::exists(chromeelf_backup))
	{
		system("TASKKILL /F /IM spotify.exe >NUL 2> 1");
		Sleep(2000);
		try
		{
			std::filesystem::remove_all(chromeelf);
			std::filesystem::rename(p / "chrome_elf_backup.dll", p / "chrome_elf.dll");

			std::cout << GREEN "  [SUCCES]  :  " RESET << YELLOW "DELETED BlockSpotify" RESET << std::endl;
		}
		catch (...)
		{
			std::cout << RED "  [ERROR]  :  " RESET << YELLOW "chrome_elf.dll"<< RED " NOT FOUND" RESET << std::endl;
		}

	}
	else
	{
		std::cout << RED "  [ERROR]  :  " RESET << YELLOW "YOU HAVE NOT BlockSpotify" RESET << std::endl;
	}


}

INT CALLBACK browse_callback_proc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData)
{
	if (uMsg == BFFM_INITIALIZED) SendMessage(hwnd, BFFM_SETSELECTION, TRUE, pData);
	return 0;
}

std::string folder::set_folder(std::string title)
{

	std::ifstream path(save_path_folder);
	std::string appdata = getenv("APPDATA");
	if (!path.good())
	{
		
		auto SpotifyPath = appdata + "\\" + "Spotify";
	
		BROWSEINFO br;
		ZeroMemory(&br, sizeof(BROWSEINFO));
		br.lpfn = browse_callback_proc;
		br.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
		br.hwndOwner = NULL;
		br.lpszTitle = title.c_str();
		br.lParam = (LPARAM)SpotifyPath.c_str();

		std::string ret;

		LPITEMIDLIST pidl = NULL;
		if ((pidl = SHBrowseForFolder(&br)) != NULL)
		{
			char buffer[_MAX_PATH];
			if (SHGetPathFromIDList(pidl, buffer)) ret = buffer;
		}

		if (!ret.empty())
		{
			std::ofstream save_path(save_path_folder);
			save_path << ret << std::endl;
			save_path.close();
		}

		return ret;
	}
	else
	{
			std::string name;
			path >> name;
			return name;
	}
}

