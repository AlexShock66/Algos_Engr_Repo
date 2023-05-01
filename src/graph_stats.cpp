//
// Created by Alex Shockley on 4/25/2023.
//
#include <fstream>
#include "GraphGenerator.h"
int main(int argc, char**argv ) {
    std::ofstream out;

    out.open("../graph_stats/test.csv");

    GraphGenerator::generate_stats(out,"uniform",100,1000,500,4500,100,100);


    return 0;
}