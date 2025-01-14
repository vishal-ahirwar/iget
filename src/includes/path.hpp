#ifndef _PATH_HPP_
#define _PATH_HPP_
#include <vector>
#include <string>
#include <filesystem>
void generatePath(const std::string &path)
{
    std::vector<std::string> directories;
    std::string directory;
    for (char i : path)
    {
        if (i == '/' || i == '\\')
        {
            directories.push_back(directory);
            directory += i;
        }
        else
        {
            directory += i;
        }
    };
    for (const auto &dir : directories)
    {
        if (!std::filesystem::exists(dir))
        {
            std::filesystem::create_directory(dir);
        }
    }
};

#endif