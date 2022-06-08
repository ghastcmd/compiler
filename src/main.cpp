#include <iostream>
#include <fstream>

#include "tokenizer.hpp"

void usage(const char *name)
{
    std::cerr << "Usage error\n\tUsage: " << name << " <file_name>\n";
}

// #include <regex>

// int main()
// {
//     std::string str = "char string";
//     std::smatch matches;
//     // std::cout << std::boolalpha;
//     std::regex reg ("^char");
//     std::regex_search(str, matches, reg);
//     std::cout << matches.ready() << '\n';
//     std::cout << matches.empty() << '\n';
//     std::cout << matches.size() << '\n';
//     std::cout << matches.str(0).size() << '\n';
//     return 0;
// }

int main(int argc, char **argv)
{
    std::cout << "this is the code\n";
    if (argc != 2)
    {
        usage(argv[0]);
    }
    
    std::fstream file (argv[1]);
    if (!file.is_open())
    {
        std::cerr << "File does not exits.\n Exiting...\n";
        return -1;
    }
    
    auto token_list = tokenizer(file);
    for (const auto &val : token_list)
    {
        val.print();
    }
    // auto token = token_list.nextToken();
    // token.print();
    return 0;
}