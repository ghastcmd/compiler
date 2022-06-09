#include <iostream>
#include <fstream>

#include "tokenizer.hpp"

void usage(const char *name)
{
    std::cerr << "Usage error\n\tUsage: " << name << " <file_name>\n";
}

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
    
    Token token;
    do
    {
        token = token_list.nextToken();
        token.print();
    }
    while (token.cat() != END_OF_FILE);

    return 0;
}