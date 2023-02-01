#include <iostream>
#include "src/Linked_List.h"

int main() {

    Linked_List<int> theList;
    theList.push_back(5);
    theList.pop_back();
//    theList.pop_back();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
