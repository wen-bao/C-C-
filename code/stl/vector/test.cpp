#include <iostream>
#include "vector.h"

using namespace MyStl;


int main() {
    int a[] = {4, 4, 3, 3, 6, 1, -1, -1, 5, 4};
    int sz = sizeof(a)/sizeof(int);

    std::cout << "\n===\ntest Constructor\n";
    vector<int> mv(a, sz);
    std::cout << mv << std::endl;
    std::cout << "The cap is " << mv.capacity() << std::endl;
    std::cout << "The siz is " << mv.size() << std::endl;

    vector<int> mm(mv, 1, 4);
    std::cout << mm << std::endl;

    std::cout << "\n===\ntest deduplicate\n";
    mv.deduplicate();
    std::cout << mv << std::endl;
    
    std::cout << "\n===\ntest push_back and pop_back\n";
    mv.push_back(3);
    mv.push_back(3);
    mv.push_back(4);
    mv.push_back(4);
    std::cout << mv << std::endl;

    mv.pop_back();
    std::cout << mv << std::endl;

    std::cout << "\n===\ntest find\n";
    int aim = 100, pos = 0;
    if((pos = mv.find(aim)) == -1) {
        std::cout << "Not Found " << aim << std::endl;
    } else {
        std::cout << "Found " << aim << " at " << pos << std::endl;
    }

    std::cout << "\n===\ntest disordered\n";
    std::cout << mv.disordered() << std::endl;
    std::cout << mv << std::endl;

    std::cout << "\n===\ntest sort\n";
    mv.sort();
    std::cout << mv << std::endl;

    std::cout << "\n===\ntest uniquify\n";
    mv.uniquify();
    std::cout << mv << std::endl;

    std::cout << "\n===\ntest clear\n";
    mv.clear();
    std::cout << mv << std::endl;

    return 0;
}