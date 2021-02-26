#include <iostream>
#include<filesystem>
#include<string>
#include<ShlObj.h>
#include<Windows.h>

using namespace std;
namespace fs = std::filesystem;

bool NodeModules(fs::path path);
bool CreateShortCut(fs::path from, fs::path to);
int distance(string a, string b);

int main(int argc, const char** argv)
{
	fs::path baseDir = fs::path("C:\\ModuleManager");
	if (!fs::exists(baseDir))
	{
		if (fs::create_directory(baseDir))
		{
			cout << "[+] - Create base directory " << baseDir.u8string() << endl;
		}
		else
		{
			cout << "[-] - Fail to create base directory " << baseDir.u8string() << endl;
			return 1;
		}
	}
	else
	{
		cout << "[!] - Find base directory " << baseDir.u8string() << endl;
	}

	if (argc > 2)
	{

		if (!string(argv[1]).compare("add"))
		{
			if (NodeModules(fs::current_path()))
			{
				cout << "[!] - Find node_modules" << endl;
				fs::path moduleBasePath = fs::path(baseDir.u8string() + "\\" + argv[2]);
				fs::path nodemodules = fs::path(fs::current_path().u8string() + "\\node_modules\\" + argv[2] + ".lnk");
				if (fs::exists(moduleBasePath))
				{
					cout << "[!] - Find module " << argv[2] << " in base directory" << endl;
					if (CreateShortCut(moduleBasePath, nodemodules))
					{
						cout << "[+] - Import module " << argv[2] << endl;
					}
					else {
						cout << "[-] - Fail to import module " << argv[2] << endl;
						return 1;
					}
				}
				else {
					cout << "[-] - No found module " << argv[2] << " in base directory" << endl;
					return 1;
				}
			}
			else {
				cout << "[-] - No found node_modules" << endl;
				return 1;
			}
		}
		else if (!string(argv[1]).compare("del"))
		{
			if (NodeModules(fs::current_path()))
			{
				cout << "[!] - Find node_modules" << endl;
				fs::path nodemodules = fs::path(fs::current_path().u8string() + "\\node_modules\\" + argv[2] + ".lnk");
				if (fs::exists(nodemodules))
				{
					cout << "[!] - Find module import " << argv[2] << endl;
					if (fs::remove(nodemodules))
					{
						cout << "[+] - Remove module import" << endl;
					}
					else {
						cout << "[-] - Fail to remove module import" << endl;
					}
				}
				else {
					cout << "[-] - No found module import " << argv[2] << endl;
					return 1;
				}
			}
			else {
				cout << "[-] - No found node_modules" << endl;
				return 1;
			}
		}
		else if (!string(argv[1]).compare("publish"))
		{
			fs::path modulePath = fs::path(fs::current_path().u8string() + "\\" + argv[2]);
			if (fs::exists(modulePath) && fs::is_directory(modulePath))
			{
				cout << "[!] - Find module " << argv[2] << endl;

				fs::path moduleBasePath = fs::path(baseDir.u8string() + "\\" + argv[2]);
				if (!fs::exists(fs::path(moduleBasePath)))
				{
					cout << "[+] - Copying files in base directory" << endl;
					if (fs::create_directories(moduleBasePath))
					{
						fs::copy(modulePath, moduleBasePath);
						cout << "[+] - Files copied in " << baseDir.u8string() << endl;
					}
					else
					{
						cout << "[-] - Fail to copy module in " << baseDir.u8string() << endl;
						return 1;
					}
				}
				else
				{
					cout << "[-] - Module already exist try update command " << endl;
					return 1;
				}
			}
			else
			{
				cout << "[-] - No found module " << argv[2] << endl;
				return 1;
			}
		}
		else if (!string(argv[1]).compare("remove"))
		{
			fs::path moduleBasePath = fs::path(baseDir.u8string() + "\\" + argv[2]);
			if (fs::exists(moduleBasePath))
			{
				cout << "[!] - Find module " << argv[2] << endl;
				if (fs::remove_all(moduleBasePath))
				{
					cout << "[+] - Remove module " << argv[2] << endl;
				}
				else {
					cout << "[-] - Fail to remove module " << argv[2] << endl;
					return 1;
				}
			}
			else {
				cout << "[-] - No found module " << argv[2] << endl;
				return 1;
			}
		}
		else if (!string(argv[1]).compare("update"))
		{
			fs::path moduleBasePath = fs::path(baseDir.u8string() + "\\" + argv[2]);
			fs::path modulePath = fs::path(fs::current_path().u8string() + "\\" + argv[2]);
			if (fs::exists(moduleBasePath))
			{
				cout << "[!] - Find module " << argv[2] << " in base directory" << endl;
				if (fs::exists(modulePath))
				{
					cout << "[!] - Find module " << argv[2] << " in current path" << endl;
					cout << "[+] - Updating files" << endl;
					const auto copyOptions = fs::copy_options::overwrite_existing;
					fs::copy(modulePath, moduleBasePath, copyOptions);
					cout << "[+] - Module updated" << endl;
				}
				else {
					cout << "[-] - No found module " << argv[2] << " in current path" << endl;
					return 1;
				}
			}
			else {
				cout << "[-] - No found module " << argv[2] << " in base directory" << endl;
				return 1;
			}
		}else if (!string(argv[1]).compare("search"))
		{
			int count = 0;
			for (const fs::directory_entry item : fs::directory_iterator(baseDir))
			{
				if (item.exists() && item.is_directory())
				{
					string folder = item.path().filename().u8string();
					string search = argv[2];
					double lv = 0.0;

					if (folder.size() == search.size())
					{
						int v = distance(folder+" ", search);
						lv = (100 - ((v * 100) / (folder.size() + 1)));
					}
					else if (folder.size() > search.size())
					{
						int v = distance(folder, search);
						lv = (100 - ((v * 100) / folder.size()));
					}
					else {
						int v = distance(search,folder);
						lv = (100 - ((v * 100) / search.size()));
					}
					if (lv >= 30)
					{
						count++;
						cout << "[!] - " << folder << " (" << lv << "%)" << endl;
					}
				}
			}
			if (count == 0)
			{
				cout << "[-] - No found module \"" << argv[2] << "\"" << endl;
			}
		}
		else {
			cout << endl << "-- Packages manager --" << endl << "publish <name>" << endl << "remove <name>" << endl << "search <name> " << endl << endl << "-- Link package in node_modules -- " << endl << "add <name>" << endl << "del <name>" << endl;
		}
	}
	else {
		cout << endl << "-- Packages manager --" << endl << "publish <name>" << endl << "remove <name>"<< endl << "search <name> " << endl << endl << "-- Link package in node_modules --" << endl << "add <name>" << endl << "del <name>" << endl;
	}
	return 0;
}

bool CreateShortCut(fs::path from,fs::path to)
{
	CoInitialize(NULL);
	IShellLink* pShellLink = NULL;
	HRESULT hres;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL,
		IID_IShellLink, (void**)&pShellLink);
	if (SUCCEEDED(hres))
	{
		pShellLink->SetPath(from.c_str());  
		//pShellLink->SetDescription(L"The Python shell");
		//pShellLink->SetIconLocation(L"C:\\Python27\\python.exe", 0);

		IPersistFile* pPersistFile;
		hres = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);

		if (SUCCEEDED(hres))
		{
			hres = pPersistFile->Save(to.c_str(), TRUE);
			pPersistFile->Release();
			return true;
		}
		else
		{
			return false;
		}
		pShellLink->Release();
	}
	else
	{
		return false;
	}
}

int distance(string a, string b)
{
	int l1 = strlen(a.c_str());
	int l2 = strlen(b.c_str());
	if (l1 == 0)
	{
		return l2;
	}
	if (l2 == 0)
	{
		return l1;
	}
	if (!a.compare(b))
	{
		return 0;
	}
	if (l1 == l2)
	{
		return 100;
	}

	int** dist = (int**)malloc(l1*l2 * sizeof(int));
	for (int i = 0; i < l1; i++)
	{
		dist[i] = (int*)malloc(l2*l1 * sizeof(int));
	}
	
	
	for (int i = 0; i <= l1; i++) {
		dist[0][i] = i;
	}
	for (int j = 0; j <= l2; j++) {
		dist[j][0] = j;
	}

	int t, track;
	for (int j = 1; j <= l1; j++) {
		for (int i = 1; i <= l2; i++) {
			if (a.c_str()[i - 1] == b.c_str()[j - 1]) {
				track = 0;
			}
			else {
				track = 1;
			}
			t = min((dist[i - 1][j] + 1), (dist[i][j - 1] + 1));
			dist[i][j] = min(t, (dist[i - 1][j - 1] + track));
		}
	}
	if (dist[l2][l1] == l1)
	{
		return l1;
	}
	int value = dist[l2][l1];
	free(dist);
	return value;
}

bool NodeModules(fs::path path)
{
	for (const fs::directory_entry item : fs::directory_iterator(path))
	{
		if (item.exists() && item.is_directory())
		{
			if (fs::path(item.path()).filename().u8string() == "node_modules")
			{
				return true;
			}
		}
	}
	return false;
}
