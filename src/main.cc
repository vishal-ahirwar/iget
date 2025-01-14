#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <ftxui/dom/elements.hpp>  // for text, gauge, operator|, flex, hbox, Element
#include <ftxui/screen/screen.hpp> // for Screen
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui
#include<path.hpp>
using namespace ftxui;

void download_file(const std::string &url, const std::string &output_file)
{
    std::string reset_position;
    try
    {
        using namespace cpr;
        // Send a GET request to the URL
        auto response = cpr::Get(cpr::Url{url}, cpr::ProgressCallback(cpr::ProgressCallback([&](cpr::cpr_off_t downloadTotal, cpr_off_t downloadNow, cpr_off_t uploadTotal, cpr_off_t uploadNow, intptr_t userdata) -> bool
        {
                                                                                               
        float percentage{(float)downloadNow/downloadTotal};
        std::string data_downloaded =
                std::to_string(int(percentage*100)) + "/"+std::to_string(100);
            auto document = border(hbox({
                text("Downloading " + output_file + " :"),
                gauge(percentage) | flex,
                text(" " + data_downloaded),
            }));
            auto screen = Screen(100, 3);
            Render(screen, document);
            std::cout << reset_position;
            screen.Print();
            reset_position = screen.ResetPosition();//better than std::cout 
        return true; 
        })));

        // Check if the request was successful
        if (response.status_code == 200)
        {
            std::cout << "\nDownload successful! Saving to " << output_file << "\n";
            generatePath(output_file);
            // Write the response body to the output file
            std::ofstream file(output_file, std::ios::binary);
            file.write(response.text.c_str(), response.text.size());
            file.close();

            std::cout << "File saved successfully!\n";
        }
        else
        {
            std::cerr << "Failed to download file. HTTP status code: " << response.status_code << "\n";
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
    }
}

int main(int argc, char **argv)
{
    // URL of the file to download
    if (argc < 3)
    {
        Screen screen = Screen(100, 3);
        Render(screen, border(text("here is how to use it : get url outputfilename.zip")));
        screen.Print();
        std::cout << std::endl;
        return 0;
    };
    std::string url = argv[1];

    // Path to save the downloaded file
    std::string output_file = argv[2];

    // Download the file
    download_file(url, output_file);

    return 0;
}
