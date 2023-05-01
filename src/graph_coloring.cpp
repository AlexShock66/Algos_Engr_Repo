//
// Created by Alex Shockley on 4/30/2023.
//
#include "GraphGenerator.h"
#include "GraphColorer.h"
int main(int argc, char** argv) {
    std::ofstream out;

//    auto theList = GraphGenerator::generate_distro("uniform",10,20);

//    auto theList = GraphGenerator::generate_distro("uniform",100,500);

    auto theList = Adj_List<uint>();
    theList.push_root(0);
    theList.push_root(1);
    theList.push_root(2);
    theList.push_root(3);

    theList.push_value(0,1);

    theList.push_value(1,0);
    theList.push_value(1,2);
    theList.push_value(1,3);

    theList.push_value(2,1);
    theList.push_value(2,3);

    theList.push_value(3,2);
    theList.push_value(3,1);

    GraphColorer::color_graph("SLV",theList);

//    out.open("../graph_files/coloring_test.txt");
//    theList.prettyPrint(out);

//    out.close();

    return 0;
}