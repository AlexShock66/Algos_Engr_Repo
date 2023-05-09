//
// Created by Alex Shockley on 4/5/23.
//

#ifndef DATA_STRUCTURES_GRAPHGENERATOR_H
#define DATA_STRUCTURES_GRAPHGENERATOR_H
#include "./Data_Structures/Adj_List.h"
#include <string>
#include <random>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
using namespace std::chrono;
class GraphGenerator {
private:
    static Adj_List<uint> _make_uniform(size_t num_verts,size_t num_edges);
    static Adj_List<uint> _make_linear(size_t num_verts, size_t num_edges);
    static Adj_List<uint> _make_triangular(size_t num_verts, size_t num_edges);

    static Adj_List<uint> _make_uniform_removal(size_t num_verts,size_t num_edges);
    static Adj_List<uint> _make_linear_removal(size_t num_verts, size_t num_edges);
    static Adj_List<uint> _make_triangular_removal(size_t num_verts, size_t num_edges);

public:
    static Adj_List<uint> generate_distro(std::string dist,size_t num_verts=40,size_t num_edges=100);
    static Adj_List<uint> generate_cycle(size_t num_verts);
    static Adj_List<uint> generate_complete(size_t num_verts);
    static void generate_stats(std::ofstream &out, std::string distro,size_t start_verts, size_t end_verts, size_t start_edge,size_t end_edge, size_t vert_increment, size_t edge_increment);

};

Adj_List<uint> GraphGenerator::generate_distro(std::string dist, size_t num_verts, size_t num_edges) {
    if(num_edges > ((num_verts * (num_verts -1))/2.0)) {
        throw std::runtime_error("Cannot have a graph with " + std::to_string(num_edges) + " Edges and only " + std::to_string(num_verts) + " verts. Max Edges = " + std::to_string(int(num_verts * (num_verts -1)/2.0)));
    }
    if(num_edges <=  (num_verts * (num_verts -1)/4.0)) {
        if(dist == "uniform") {
            return _make_uniform(num_verts, num_edges);
        } else if(dist == "linear") {
            return _make_linear(num_verts,num_edges);
        } else if (dist == "triangular") {
            return _make_triangular(num_verts, num_edges);
        }
    } else {
//        std::cout <<"======================= RUNNING REMOVAL =======================\n";
        if(dist == "uniform") {
            return _make_uniform_removal(num_verts, num_edges);
        } else if(dist == "linear") {
            return _make_linear_removal(num_verts,num_edges);
        } else if (dist == "triangular") {
            return _make_triangular_removal(num_verts, num_edges);
        }
    }

}

Adj_List<uint> GraphGenerator::_make_triangular(size_t num_verts, size_t num_edges) {
    uint adj_matrix[num_verts][num_verts];
    memset(adj_matrix, 0, sizeof(adj_matrix[0][0]) * num_verts * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(0,(num_verts)/2.0);

    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
    }

    for(auto i = 0; i < num_edges; i ++) {
        uint left = floor(distribution(generator) + distribution(generator));
        uint right = floor(distribution(generator) + distribution(generator));

        if(left == right || adj_matrix[left][right] == 1) {
            i--;
            continue;
        } else {
            theList.push_value(left,right);
            theList.push_value(right,left);
            adj_matrix[left][right] = 1;
            adj_matrix[right][left] = 1;
        }
    }


    return theList;

}

Adj_List<uint> GraphGenerator::_make_uniform(size_t num_verts, size_t num_edges) {

    uint adj_matrix[num_verts][num_verts];

    memset(adj_matrix, 0, sizeof(adj_matrix[0][0]) * num_verts * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<size_t> distribution(0,num_verts -1);

    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
    }

    for(auto i = 0; i < num_edges; i ++) {
        auto first = distribution(generator);
        auto second = distribution(generator);
        if(first == second || adj_matrix[first][second] == 1) {
            i--;
//            std::cout << "Conflict at iteration " <<i << "| " <<first <<", " <<second<<'\n';
            continue;
        } else {
            theList.push_value(first,second);
            theList.push_value(second,first);
            adj_matrix[first][second] = 1;
            adj_matrix[second][first] = 1;
        }

    }
    return theList;
}

Adj_List<uint> GraphGenerator::_make_linear(size_t num_verts, size_t num_edges) {

    uint adj_matrix[num_verts][num_verts];
    memset(adj_matrix, 0, sizeof(adj_matrix[0][0]) * num_verts * num_verts);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<uint> distribution(0,num_verts -1);

    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
    }

    for(auto i = 0; i < num_edges; i ++) {
        auto first = distribution(generator);
        auto second = distribution(generator);
        uint left = std::min(first,second);
        auto third = distribution(generator);
        auto forth = distribution(generator);
        uint right = std::min(third,forth);
        if(left == right || adj_matrix[left][right] == 1) {
            i--;
            continue;
        } else {
            theList.push_value(left,right);
            theList.push_value(right,left);
            adj_matrix[left][right] = 1;
            adj_matrix[right][left] = 1;
        }
    }

    return theList;
}

Adj_List<uint> GraphGenerator::_make_uniform_removal(size_t num_verts, size_t num_edges) {
    uint adj_matrix[num_verts][num_verts];
    memset(adj_matrix, 0, sizeof(adj_matrix[0][0]) * num_verts * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<size_t> distribution(0,num_verts -1);

    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
    }

    auto _num_edges = size_t((num_verts * (num_verts -1)/2.0) - num_edges);

    for(auto i = 0; i < _num_edges ; i ++) {
        auto first = distribution(generator);
        auto second = distribution(generator);
        if(first == second || adj_matrix[first][second] == 1) {
            i--;
            continue;
        } else {
//            theList.push_value(first,second);
//            theList.push_value(second,first);
            adj_matrix[first][second] = 1;
            adj_matrix[second][first] = 1;
        }

    }

    for(auto i =0; i < num_verts; i ++) {

        for(auto j=i; j < num_verts; j ++) {
            if(i == j) continue;
            if(adj_matrix[i][j] != 1) {
                theList.push_value(i,j);
                theList.push_value(j,i);
            }
//            std::cout << (adj_matrix[i][j] != 1) <<" ";

        }
//        std::cout <<'\n';
    }

    return theList;
}

Adj_List<uint> GraphGenerator::_make_linear_removal(size_t num_verts, size_t num_edges) {

    uint adj_matrix[num_verts][num_verts];
    memset(adj_matrix, 0, sizeof(adj_matrix[0][0]) * num_verts * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<uint> distribution(0,num_verts -1);

    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
    }

    auto _num_edges = size_t((num_verts * (num_verts -1)/2.0) - num_edges);

    for(auto i = 0; i < _num_edges; i ++) {
        auto first = distribution(generator);
        auto second = distribution(generator);
        uint left = std::max(first,second);
        auto third = distribution(generator);
        auto forth = distribution(generator);
        uint right = std::max(third,forth);
        if(left == right || adj_matrix[left][right] == 1) {
            i--;
            continue;
        } else {
//            theList.push_value(left,right);
//            theList.push_value(right,left);
            adj_matrix[left][right] = 1;
            adj_matrix[right][left] = 1;
        }
    }



    for(auto i =0; i < num_verts; i ++) {
        for(auto j=i; j < num_verts; j ++) {
            if(i ==j) continue;
            if(adj_matrix[i][j] != 1) {
                theList.push_value(i,j);
                theList.push_value(j,i);
            }

        }
    }

    return theList;
}


Adj_List<uint> GraphGenerator::_make_triangular_removal(size_t num_verts, size_t num_edges) {

    uint adj_matrix[num_verts][num_verts];
    memset(adj_matrix, 0, sizeof(adj_matrix[0][0]) * num_verts * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(0,(num_verts)/2.0);


    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
    }

//    std::vector<uint> buckets(num_verts,0);
    auto _num_edges = size_t((num_verts * (num_verts -1)/2.0) - num_edges);
    for(auto i = 0; i < _num_edges; i ++) {
        uint left = uint(floor(distribution(generator) + distribution(generator)) + ceil(num_verts/2.0)) % num_verts;
        uint right = uint(floor(distribution(generator) + distribution(generator)) + ceil(num_verts/2.0)) % num_verts;

//        buckets[left] += 1;
//        buckets[right] +=1;
        if(left == right || adj_matrix[left][right] == 1) {
            i--;
            continue;
        } else {
            adj_matrix[left][right] = 1;
            adj_matrix[right][left] = 1;

        }
    }



    for(auto i =0; i < num_verts; i ++) {
        for(auto j=i; j < num_verts; j ++) {
            if(i ==j) continue;
            if(adj_matrix[i][j] != 1) {
                theList.push_value(i,j);
                theList.push_value(j,i);
            }

        }
    }

    return theList;


}

Adj_List<uint> GraphGenerator::generate_cycle(size_t num_verts) {

    Adj_List<uint> theList(num_verts);
    theList.push_root(0);
    uint prev_root = 0;
    for(auto i = 1; i < num_verts; i ++) {
        theList.push_root(i);
        theList.push_value(prev_root,i);
        theList.push_value(i,prev_root);
        prev_root = i;
    }
    theList.push_value(num_verts - 1,0);
    theList.push_value(0,num_verts -1);
    return theList;

}

Adj_List<uint> GraphGenerator::generate_complete(size_t num_verts) {
    Adj_List<uint> theList(num_verts);
    for(auto i =0; i < num_verts; i ++) {
        theList.push_root(i);
        for(auto j=0; j <num_verts; j ++) {
            if(j != i) theList.push_value(i,j);
        }
    }

    return theList;
}


void GraphGenerator::generate_stats(std::ofstream &out, std::string distro, size_t start_verts, size_t end_verts,
                                    size_t start_edge, size_t end_edge, size_t vert_increment, size_t edge_increment) {

    out << ",";
    for(int i=0; i < int(int((end_edge - start_edge)/edge_increment)/2.0); i ++) {
        out << " ,";
    }
    out << "Number of Edges\n";

    out <<" , ,";
    for(size_t edges= start_edge; edges <= end_edge; edges += edge_increment) { //Get horizontal headers printed (NUM EDGES)
            out << edges <<",";
    }
    out <<"\n";
    auto row_title_idx = int(int((end_verts - start_verts)/vert_increment)/2.0);
    int counter = 0;

    for(size_t verts=start_verts; verts <= end_verts; verts += vert_increment) {
        if(counter == row_title_idx) out << "Verts,";
        else out <<",";
        counter++;
        out << verts <<","; // Print vertical headers (NUM VERTS)

        for(size_t edges= start_edge; edges <= end_edge; edges += edge_increment) {
            auto start = high_resolution_clock::now();
            if(distro == "cycle") {
                GraphGenerator::generate_cycle(verts);
            } else if(distro == "complete") {
                GraphGenerator::generate_complete(verts);
            } else {
                GraphGenerator::generate_distro(distro,verts,edges);
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            out << duration.count() <<",";
            std::cout << "Finished " << verts << "x" <<edges <<'\n';
        }
        out << "\n";

    }


    out << "\n\n\n\n\n\n";


    auto outputter_verts = end_verts/2 + start_verts;
    auto outputter_edges = (outputter_verts * (outputter_verts -1) / 4);

    outputter_edges = outputter_edges + outputter_edges/2;

    Adj_List<uint> theList;
    if(distro == "cycle") {
        theList = GraphGenerator::generate_cycle(outputter_verts);
    } else if(distro == "complete") {
        theList = GraphGenerator::generate_complete(outputter_verts);
    } else {
        theList = GraphGenerator::generate_distro(distro,outputter_verts,outputter_edges);
    }
    out << "Edges Per Vert\n";
    out << "Algorithm:," << distro <<"\n";
    out << "Verts:," << outputter_verts<<"\n";
    if(distro != "cycle" && distro != "complete") out << "Edges:," << outputter_edges<<"\n";
    else out <<"Edges:," << "N/A" <<"\n";

    for(auto i=0; i < theList.get_curr_length(); i ++) {
        out << i <<"," <<theList[i].get_size() <<"\n";
    }
}

#endif //DATA_STRUCTURES_GRAPHGENERATOR_H
