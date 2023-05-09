//
// Created by Alex Shockley on 4/25/2023.
//
#include <fstream>
#include "GraphGenerator.h"
#include "GraphColorer.h"
void generate_creation_stats(){
    std::ofstream out;

    out.open("../graph_stats/complete_report.csv");

    GraphGenerator::generate_stats(out,"complete",100,5000,500,1000,100,100);

}

void generate_coloring_stats() {
    std::ofstream out;

    out.open("../graph_stats/least_degree_last.csv");

    GraphColorer::generate_stats(out,"uniform","least_degree_last",100,1000,500,4500,100,100);
}

void generate_comparison_stats() {
    std::ofstream out;

    out.open("../graph_stats/SLV.csv");

//    GraphColorer::generate_stats(out,"uniform","least_degree_last",100,1000,500,4500,100,100);
    auto g1 = GraphGenerator::generate_distro("uniform",20,75);

    GraphColorer::color_graph("SLV",g1,out);
}

void generate_capabilities(string distro) {
    ofstream out_slv;
    ofstream out_dfs;
    ofstream out_random;
    ofstream out_least;

    out_slv.open("../graph_stats/capabilities_SLV_" + distro + ".csv");
    out_dfs.open("../graph_stats/capabilities_DFS_" + distro + ".csv");
    out_random.open("../graph_stats/capabilities_rand_" + distro + ".csv");
    out_least.open("../graph_stats/capabilities_least_" + distro + ".csv");

    ofstream out_graph;
    out_graph.open("../graph_files/capibility_" + distro +  ".txt");

//     auto theGraph = GraphGenerator::generate_distro(distro,20,100);
    auto theGraph = GraphGenerator::generate_complete(20);
     theGraph.prettyPrint(out_graph);
     GraphColorer::color_graph("SLV",theGraph,out_slv);
    GraphColorer::color_graph("DFS",theGraph,out_dfs);
    GraphColorer::color_graph("random",theGraph,out_random);
    GraphColorer::color_graph("least_degree_last",theGraph,out_least);


    out_slv.close();
    out_dfs.close();
    out_random.close();
    out_least.close();

    out_graph.close();


}
int main(int argc, char**argv ) {

//    generate_creation_stats();
    generate_capabilities("complete");
    return 0;
}