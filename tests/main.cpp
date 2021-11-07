#include <System/System.h>
#include <System/Library.h>
#include <System/Filesystem.h>

#include <iostream>

int main(int argc, char *argv[])
{
    System::Library shared;
    std::string lib_path = System::Filesystem::join(System::Filesystem::dirname(System::GetExecutablePath()), "shared");
    shared.OpenLibrary(lib_path, true);                                                                                           

    std::cout << "From executable: " << System::GetExecutablePath() << ' ' << System::GetModulePath() << ' ' << shared.GetModulePath() << std::endl;

    return 0;
}
