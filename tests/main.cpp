#include <System/System.h>
#include <System/Library.h>
#include <System/Filesystem.h>

#include <iostream>

int main(int argc, char *argv[])
{
    System::Library shared;
    std::string lib_path = System::Filesystem::Join(System::Filesystem::Dirname(System::GetExecutablePath()), "shared");
    shared.OpenLibrary(lib_path, true);                                                                                           
    auto modules = System::GetModules();
    std::cout << "From executable: " << std::endl
              << "  Executable path       : " << System::GetExecutablePath() << std::endl
              << "  Executable module path: " << System::GetModulePath() << std::endl
              << "  Library module path   : " << shared.GetModulePath() << std::endl << std::endl;

    std::cout << "Loaded modules: " << std::endl;
    for (auto const& item : modules)
    {
        std::cout << "  " << item << std::endl;
    }

    return 0;
}
