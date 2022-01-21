
#include <iostream>
#include "spotify.hpp"

int main()
{
	int choice;
	SetConsoleTitle("Spotify Loader");
	while (true)
	{
		system("cls");

		std::cout << "Select Spootify Folder which contains Spotify.exe" << '\n';

		g_folder = std::make_unique<folder>();

		while (true)
		{
			g_folder->spotify_path = g_folder->set_folder("Select Spootify Folder which contains Spotify.exe");

			system("cls");

			if (!g_folder->spotify_path.empty())
			{
				std::cout << "  [Selected Folder]  " << g_folder->spotify_path << "\n" << std::endl;

				std::cout << "  [1]  :  " << "Enable  BlockSpotify" << std::endl;
				std::cout << "  [2]  :  " << "Disable BlockSpotify" << std::endl;
				std::cout << BOLDYELLOW"  [#]  :  " RESET;
				std::cin >> choice;

				switch (choice)
				{
				case 1:
				{
					g_folder->setup();
				}
				break;
				case 2:
				{
					g_folder->removeall();
				}
				break;
				}
			}

			else
			{
				std::cout << RED "  [ERROR]  :  " << "select valid folder for Spotify" << RESET"\n" << std::endl;
			}

			system("pause");
		}

		system("pause");
	}

}