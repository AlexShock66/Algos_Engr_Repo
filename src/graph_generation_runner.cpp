//
// Created by Alex Shockley on 4/5/23.
//
#include <fstream>
#include "GraphGenerator.h"
using namespace std;
int main(int argc, char** argv) {

    std::ofstream out;

//    out.open("../graph_files/cycle_10.txt");
//    GraphGenerator::generate_cycle(10).prettyPrint(out);
//    out.close();
//
//    out.open("../graph_files/complete_10.txt");
//    GraphGenerator::generate_complete(10).prettyPrint(out);
//    out.close();

//    out.open("../graph_files/uniform_5_8.txt");
//    GraphGenerator::generate_distro("uniform",5,8).prettyPrint(out);
//    out.close();
//
//    out.open("../graph_files/linear_5_8.txt");
//    GraphGenerator::generate_distro("linear",5,8).prettyPrint(out);
//    out.close();

    out.open("../graph_files/uniform_10_30.txt");
    GraphGenerator::generate_distro("uniform",10,30).prettyPrint(out);
    out.close();

//    auto a = GraphGenerator::generate_distro("triangular",20,100000);
    return 0;
}