//
// Created by Alex Shockley on 4/5/23.
//

#ifndef DATA_STRUCTURES_GRAPHGENERATOR_H
#define DATA_STRUCTURES_GRAPHGENERATOR_H
#include "./Data_Structures/Adj_List.h"
#include <string>
#include <random>
#include <algorithm>
class GraphGenerator {
private:
    static Adj_List<uint> _make_uniform(size_t num_verts,size_t num_edges);
    static Adj_List<uint> _make_linear(size_t num_verts, size_t num_edges);
public:
    static Adj_List<uint> generate_distro(std::string dist,size_t num_verts=40,size_t num_edges=100);
    static Adj_List<uint> generate_cycle(size_t num_verts);
    static Adj_List<uint> generate_complete(size_t num_verts);

};

Adj_List<uint> GraphGenerator::generate_distro(std::string dist, size_t num_verts, size_t num_edges) {
    if(dist == "uniform") {
        return _make_uniform(num_verts, num_edges);
    } else if(dist == "linear") {
        return _make_linear(num_verts,num_edges);
    }
}

Adj_List<uint> GraphGenerator::_make_uniform(size_t num_verts, size_t num_edges) {
    //TODO Handle Case where num_edges > num_verts^2
    uint adj_matrix[num_verts][num_verts];


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



    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<uint> distribution(0,num_verts -1);

    for(auto i = 0; i < num_edges; i ++) {
        auto first = distribution(generator);
        auto second = distribution(generator);
        uint left = std::min(first,second);
        auto third = distribution(generator);
        auto forth = distribution(generator);
        uint right = std::min(first,second);
    }

    return Adj_List<uint>();
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

#endif //DATA_STRUCTURES_GRAPHGENERATOR_H
