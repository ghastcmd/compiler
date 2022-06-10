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

    Tokenizer tokenizer (argv[1]);

    if (!tokenizer.is_open())
    {
        return -1;
    }
    
    std::cout << "Hello world!\n";

    Token token;
    do
    {
        token = tokenizer.nextToken();
        token.print();
    }
    while (token.cat() != END_OF_FILE);

    return 0;
}