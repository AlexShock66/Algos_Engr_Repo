//
// Created by Alex Shockley on 4/5/23.
//
#include <fstream>
#include "GraphGenerator.h"
using namespace std;
int main(int argc, char** argv) {

//    std::ofstream out;
//
//    out.open("../graph_files/cycle_10.txt");
//    auto cycle = GraphGenerator::generate_cycle(10);
//    cycle.prettyPrint(out);
//    out.close();
//
//    out.open("../graph_files/complete_10.txt");
//    auto complete = GraphGenerator::generate_complete(10);
//    complete.prettyPrint(out);
//    out.close();
//
//    out.open("../graph_files/uniform_10_25.txt");
//    auto uniform = GraphGenerator::generate_distro("uniform",10,25);
//    uniform.prettyPrint(out);
//    out.close();

    auto a = GraphGenerator::generate_distro("linear",20,100000);
    return 0;
}