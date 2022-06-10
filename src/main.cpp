#include <iostream>
#include <fstream>

#include "tokenizer.hpp"

void usage(const char *name)
{
    std::cerr << "Usage error\n\tUsage: " << name << " <file_name>\n";
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage(argv[0]);
    }

#if 1

    Tokenizer tknizer (argv[1]);

    if (!tknizer.is_open())
    {
        return -1;
    }

    Token token;
    do
    {
        token = tknizer.nextToken();
        token.print();
    }
    while (token.cat() != END_OF_FILE);

#else

    std::fstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "file does not exists\n";
    }
    
    auto token_list = tokenizer(file);

    Token token;
    do
    {
        token = token_list.nextToken();
        token.print();
    }
    while (token.cat() != END_OF_FILE);

#endif

    return 0;
}