#ifndef _PATH_HPP_
#define _PATH_HPP_
#include <vector>
#include <string>
#include <filesystem>
void generatePath(const std::string &path)
{
    auto valid_path=path.find_last_of("/");
    if(valid_path!=std::string::npos)
    {
        std::string temp=path.substr(0,valid_path);
        std::filesystem::create_directories(temp);
    }
};

#endif