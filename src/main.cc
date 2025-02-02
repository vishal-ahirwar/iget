#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <path.hpp>
#include<fmt/core.h>
#include<fmt/color.h>
void download_file(const std::string &url, const std::string &output_file)
{
    std::string reset_position;
    try
    {
        using namespace cpr;
        // Send a GET request to the URL
        auto response = cpr::Get(cpr::Url{url}, cpr::ProgressCallback(cpr::ProgressCallback([&](cpr::cpr_off_t downloadTotal, cpr_off_t downloadNow, cpr_off_t uploadTotal, cpr_off_t uploadNow, intptr_t userdata) -> bool
                                                                                            {
                                                                                                fmt::print(fmt::fg(fmt::color::green),"\rDownloading {:.2f} %",((double)downloadNow/downloadTotal)*100.f);
                                                                                                 return true; })));

        // Check if the request was successful
        if (response.status_code == 200)
        {
            fmt::print(fmt::emphasis::faint,"\nDownload successful! Saving to {}\n", output_file);
            generatePath(output_file);
            // Write the response body to the output file
            std::ofstream file(output_file, std::ios::binary);
            file.write(response.text.c_str(), response.text.size());
            file.close();

            fmt::print(fmt::emphasis::faint,"File saved successfully!\n");
        }
        else
        {
            fmt::print(fmt::emphasis::faint|fmt::fg(fmt::color::red),"Failed to download file. HTTP status code: {}\n", response.status_code);
        }
    }
    catch (const std::exception &ex)
    {
        fmt::print(fmt::emphasis::faint|fmt::fg(fmt::color::red), "Error: {}", ex.what());
    }
}

int main(int argc, char **argv)
{
    // URL of the file to download
    if (argc < 3)
    {
        fmt::print(fmt::emphasis::faint|fmt::fg(fmt::color::aqua),"here is how to use it : get url outputfilename.zip\n");
        return 0;
    };
    std::string url = argv[1];

    // Path to save the downloaded file
    std::string output_file = argv[2];

    // Download the file
    download_file(url, output_file);

    return 0;
}
