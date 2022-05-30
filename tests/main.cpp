#include <System/System.h>
#include <System/Library.h>
#include <System/Filesystem.h>
#include <System/SystemDetector.h>
#include <System/String.hpp>

#include <iostream>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}

TEST_CASE("Load library", "[loadlibrary]")
{
    System::Library::Library shared;
    std::string lib_path = System::Filesystem::Join(System::Filesystem::Dirname(System::GetExecutablePath()), "shared");
    shared.OpenLibrary(lib_path, true);
    std::cout << "From executable: " << std::endl
        << "  Executable path       : " << System::GetExecutablePath() << std::endl
        << "  Executable module path: " << System::GetModulePath() << std::endl
        << "  Library module path   : " << shared.GetLibraryPath() << std::endl << std::endl;
}

TEST_CASE("Show modules", "[showmodules]")
{
    std::cout << "Loaded modules: " << std::endl;
    auto modules = System::GetModules();
    for (auto const& item : modules)
    {
        std::cout << "  " << item << std::endl;
    }
}

TEST_CASE("Dirname", "[dirname]")
{
#if defined(SYSTEM_OS_WINDOWS)
    CHECK(System::Filesystem::Dirname("D:\\test1\\test2\\//\\\\\\\\//test3\\") == "D:\\test1\\test2\\test3");
    CHECK(System::Filesystem::Dirname("D:\\test1\\test2/test3") == "D:\\test1\\test2");
    CHECK(System::Filesystem::Dirname("D:\\test1\\test2") == "D:\\test1");
    CHECK(System::Filesystem::Dirname("D:\\test1") == "D:");
    CHECK(System::Filesystem::Dirname("D:") == "");

    CHECK(System::Filesystem::Dirname("test1/test2") == "test1");
    CHECK(System::Filesystem::Dirname("test1\\test2") == "test1");
    CHECK(System::Filesystem::Dirname("test1") == "");
    CHECK(System::Filesystem::Dirname("") == "");

#else
    CHECK(System::Filesystem::Dirname("/test1/test2\\//\\\\\\\\//test3\\") == "/test1/test2/test3");
    CHECK(System::Filesystem::Dirname("/test1/test2\\test3") == "/test1/test2");
    CHECK(System::Filesystem::Dirname("/test1/test2") == "/test1");
    CHECK(System::Filesystem::Dirname("/test1") == "/");
    CHECK(System::Filesystem::Dirname("/") == "");

    CHECK(System::Filesystem::Dirname("test1/test2") == "test1");
    CHECK(System::Filesystem::Dirname("test1\\test2") == "test1");
    CHECK(System::Filesystem::Dirname("test1") == "");
    CHECK(System::Filesystem::Dirname("") == "");
#endif
}

TEST_CASE("Filename", "[filename]")
{
#if defined(SYSTEM_OS_WINDOWS)
    CHECK(System::Filesystem::Filename("D:\\dir\\file") == "file");
    CHECK(System::Filesystem::Filename("D:\\dir\\file\\") == "");
    CHECK(System::Filesystem::Filename("file") == "file");
#else
    CHECK(System::Filesystem::Filename("/dir/file") == "file");
    CHECK(System::Filesystem::Filename("/dir/file/") == "");
    CHECK(System::Filesystem::Filename("file") == "file");
#endif
}

TEST_CASE("Join", "[join]")
{
#if defined(SYSTEM_OS_WINDOWS)
    #define TSEP "\\"
#else
    #define TSEP "/"
#endif
    CHECK(System::Filesystem::Join("a", "b") == "a" TSEP "b");
    CHECK(System::Filesystem::Join("a\\", "b") == "a" TSEP "b");
    CHECK(System::Filesystem::Join("a", "\\b") == "a" TSEP "b");
    CHECK(System::Filesystem::Join("a/", "b") == "a" TSEP "b");
    CHECK(System::Filesystem::Join("a", "/b") == "a" TSEP "b");
    CHECK(System::Filesystem::Join("a") == "a");
    CHECK(System::Filesystem::Join("a", "b", "c") == "a" TSEP "b" TSEP "c");

#undef TSEP
}

TEST_CASE("ToLower", "[to_lower]")
{
    // inplace char* (nullptr)
    {
        // don't crash
        System::String::ToLower(nullptr);
    }
    // inplace char*
    {
        char buffer[] = "TO LOWER";
        System::String::ToLower(buffer);
        CHECK(strcmp(buffer, "to lower") == 0);
    }
    // inplace std::string&
    {
        std::string buffer = "TO LOWER";
        System::String::ToLower(buffer);
        CHECK(buffer == "to lower");
    }
    // copy const char*
    {
        char buffer[] = "TO LOWER";
        std::string result = System::String::CopyLower(buffer);
        CHECK(strcmp(buffer, "TO LOWER") == 0);
        CHECK(result == "to lower");
    }
    // copy std::string const&
    {
        std::string buffer = "TO LOWER";
        std::string result = System::String::CopyLower(buffer);
        CHECK(buffer == "TO LOWER");
        CHECK(result == "to lower");
    }
    // copy System::StringView
    {
        System::StringView buffer = "TO LOWER";
        std::string result = System::String::CopyLower(buffer);
        CHECK(strcmp(&buffer[0], "TO LOWER") == 0);
        CHECK(result == "to lower");
    }
}

TEST_CASE("ToUpper", "[to_upper]")
{
    // inplace char* (nullptr)
    {
        // don't crash
        System::String::ToUpper(nullptr);
    }
    // inplace char*
    {
        char buffer[] = "to upper";
        System::String::ToUpper(buffer);
        CHECK(strcmp(buffer, "TO UPPER") == 0);
    }
    // inplace std::string&
    {
        std::string buffer = "to upper";
        System::String::ToUpper(buffer);
        CHECK(buffer == "TO UPPER");
    }
    // copy const char*
    {
        char buffer[] = "to upper";
        std::string result = System::String::CopyUpper(buffer);
        CHECK(strcmp(buffer, "to upper") == 0);
        CHECK(result == "TO UPPER");
    }
    // copy std::string const&
    {
        std::string buffer = "to upper";
        std::string result = System::String::CopyUpper(buffer);
        CHECK(buffer == "to upper");
        CHECK(result == "TO UPPER");
    }
    // copy System::StringView
    {
        System::StringView buffer = "to upper";
        std::string result = System::String::CopyUpper(buffer);
        CHECK(strcmp(&buffer[0], "to upper") == 0);
        CHECK(result == "TO UPPER");
    }
}

TEST_CASE("CloneString", "[clone_string]")
{
    char* result = nullptr;

    // const char* (nullptr)
    {
        result = System::String::CloneString(nullptr);
        CHECK((result != nullptr && strcmp(result, "") == 0));
        delete[] result; result = nullptr;
    }
    // const char*
    {
        const char* tmp = "Clone test";
        result = System::String::CloneString(tmp);
        CHECK((result != nullptr && strcmp(result, "Clone test") == 0));
        delete[] result; result = nullptr;
    }
    // std::string const&
    {
        result = System::String::CloneString(std::string("Clone test"));
        CHECK((result != nullptr && strcmp(result, "Clone test") == 0));
        delete[] result; result = nullptr;
    }
    // System::StringView
    {
        result = System::String::CloneString(System::StringView("Clone test"));
        CHECK((result != nullptr && strcmp(result, "Clone test") == 0));
        delete[] result; result = nullptr;
    }
}

TEST_CASE("CopyString", "[copy_string]")
{
    size_t result;
    {
        char buffer[200];
        // const char* (nullptr)
        result = System::String::CopyString(nullptr, buffer, 200);
        CHECK((result == 0 && strcmp(buffer, "") == 0));
        memset(buffer, 0, 200);
        // const char*
        result = System::String::CopyString("Copy test", buffer, 200);
        CHECK((result == 9 && strcmp(buffer, "Copy test") == 0));
        memset(buffer, 0, 200);
        // System::StringView
        result = System::String::CopyString(System::StringView("Copy test sv"), buffer, 200);
        CHECK((result == 12 && strcmp(buffer, "Copy test sv") == 0));
        memset(buffer, 0, 200);
        // std::string const&
        result = System::String::CopyString(std::string("Copy test string"), buffer, 200);
        CHECK((result == 16 && strcmp(buffer, "Copy test string") == 0));
        memset(buffer, 0, 200);
    }
    {
        char buffer[5];
        // const char* (nullptr)
        result = System::String::CopyString(nullptr, buffer, 5);
        CHECK((result == 0 && strcmp(buffer, "") == 0));
        memset(buffer, 0, 5);
        // const char*
        result = System::String::CopyString("Copy test", buffer, 5);
        CHECK((result == 4 && strcmp(buffer, "Copy") == 0));
        memset(buffer, 0, 5);
        // System::StringView
        result = System::String::CopyString(System::StringView("Copy test sv"), buffer, 5);
        CHECK((result == 4 && strcmp(buffer, "Copy") == 0));
        memset(buffer, 0, 5);
        // std::string const&
        result = System::String::CopyString(std::string("Copy test string"), buffer, 5);
        CHECK((result == 4 && strcmp(buffer, "Copy") == 0));
        memset(buffer, 0, 5);
    }

    //
    {
        char buffer[200];
        // const char* (nullptr)
        result = System::String::CopyString(nullptr, buffer);
        CHECK((result == 0 && strcmp(buffer, "") == 0));
        memset(buffer, 0, 200);
        // const char*
        result = System::String::CopyString("Copy test", buffer);
        CHECK((result == 9 && strcmp(buffer, "Copy test") == 0));
        memset(buffer, 0, 200);
        // System::StringView
        result = System::String::CopyString(System::StringView("Copy test sv"), buffer);
        CHECK((result == 12 && strcmp(buffer, "Copy test sv") == 0));
        memset(buffer, 0, 200);
        // std::string const&
        result = System::String::CopyString(std::string("Copy test string"), buffer);
        CHECK((result == 16 && strcmp(buffer, "Copy test string") == 0));
        memset(buffer, 0, 200);
    }
    {
        char buffer[5];
        // const char* (nullptr)
        result = System::String::CopyString(nullptr, buffer);
        CHECK((result == 0 && strcmp(buffer, "") == 0));
        memset(buffer, 0, 5);
        // const char*
        result = System::String::CopyString("Copy test", buffer);
        CHECK((result == 4 && strcmp(buffer, "Copy") == 0));
        memset(buffer, 0, 5);
        // System::StringView
        result = System::String::CopyString(System::StringView("Copy test sv"), buffer);
        CHECK((result == 4 && strcmp(buffer, "Copy") == 0));
        memset(buffer, 0, 5);
        // std::string const&
        result = System::String::CopyString(std::string("Copy test string"), buffer);
        CHECK((result == 4 && strcmp(buffer, "Copy") == 0));
        memset(buffer, 0, 5);
    }
}