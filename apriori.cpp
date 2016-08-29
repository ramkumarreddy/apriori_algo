#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream  data("input.csv");

    std::string line;
    while(std::getline(data,line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        while(std::getline(lineStream,cell,','))
        {
            std::cout << cell+" ";
        }
        std::cout << "\n";
    }
}