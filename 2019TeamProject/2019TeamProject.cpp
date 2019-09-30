#include <iostream>
#include "Window.h"

int main(int argc, char* args[])
{
	try
	{
		Window window{};
		window.Initialize("SDL Game", 1280, 768);

		while (window.IsInit()) {
			window.Broadcast();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << "\n";
		return -1;
	}

	return 0;
}