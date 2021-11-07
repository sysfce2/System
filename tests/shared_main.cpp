#include <System/System.h>

#include <iostream>

void shared_library_load()
{
    std::cout << "From library: " << System::GetExecutablePath() << ' ' << System::GetModulePath() << std::endl;
}

void shared_library_unload()
{
}
