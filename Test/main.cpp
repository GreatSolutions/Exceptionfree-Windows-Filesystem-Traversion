//filesystem Exceptionsolution to traverse systemfiles on Windows

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <vector>
namespace fs = std::filesystem;
__declspec(dllimport)ULONG adjust_privileges();

struct DataContext
{
	std::string path;
	std::string name;
}DataContextObject;

int main(void)
{
	adjust_privileges();
	
	std::vector<DataContext> Presorted[255];
	fs::recursive_directory_iterator item(L"c:\\", fs::directory_options::skip_permission_denied);
	const fs::recursive_directory_iterator end;

	while (item != end)
	{
		//printf("%S\n", item->path().filename().c_str());
		auto _FilePath = item->path().string();
		auto _FileName = item->path().filename().string();
		DataContextObject.path = _FilePath;
		DataContextObject.name = _FileName;

		//std::cout << (int)_FileName[0] << "\n";
		Presorted[(int)_FileName[0]].push_back(DataContextObject);
		++item;
	}

	std::cout << Presorted[77][0].path;
	return 0;
}
