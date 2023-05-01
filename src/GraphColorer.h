//
// Created by Alex Shockley on 4/30/2023.
//

#ifndef DATA_STRUCTURES_GRAPHCOLORER_H
#define DATA_STRUCTURES_GRAPHCOLORER_H

using namespace std;
#include <string>
#include "Data_Structures/Adj_List.h"
#include <iostream>
#include "Data_Structures/Linked_List.h"
class GraphColorer {

private:
    static void least_degree_last(Adj_List<uint> &adj_list,std::ostream &out);
    static void print_degree_array( Linked_List<uint> *theList,int theSize);
    static void color_vert(size_t vert_to_color, int *colors, Adj_List<uint> &theList);
    static void random_order_coloring(Adj_List<uint> &adj_list,std::ostream &out);
    static void smallest_last_vertex(Adj_List<uint> &adj_list,std::ostream &out);


public:

    static void color_graph(string algorithm, Adj_List<uint> adj_list,std::ostream &out=std::cout);


};

void GraphColorer::print_degree_array(Linked_List<uint> *theList,int theSize) {
    for(int i=0; i < theSize; i ++) {
        cout << i <<": ";
        while(theList[i].has_next()) {
            cout << theList[i].get_next();
            if(theList[i].has_next()) cout<<", ";
        }
        theList[i].reset_iterator();
        cout << "\n";
    }
}

void GraphColorer::color_graph(string algorithm, Adj_List<uint> adj_list,std::ostream &out) {
    if(algorithm == "least_degree_last") {
        GraphColorer::least_degree_last(adj_list,out);
    } else if(algorithm == "random") {
        GraphColorer::random_order_coloring(adj_list,out);
    } else if(algorithm == "SLV") {
        GraphColorer::smallest_last_vertex(adj_list,out);
    }
}

void GraphColorer::color_vert(size_t vert_to_color, int *colors, Adj_List<uint> &theList) {
    int used_colors[theList.get_curr_length()];
    memset(used_colors, 0, sizeof(used_colors[0]) * theList.get_curr_length());

    while(theList[vert_to_color].has_next()) {
        used_colors[colors[theList[vert_to_color].get_next()]] = 1;
    }

    theList[vert_to_color].reset_iterator();

    for(int i =0; i < theList.get_curr_length(); i ++) {
        if(used_colors[i] == 0) {
            colors[vert_to_color] = i;
            break;
        }
    }


}

void GraphColorer::least_degree_last(Adj_List<uint> &adj_list,std::ostream &out) {
    Linked_List<uint> degrees[adj_list.get_curr_length()];
    auto num_verts = adj_list.get_curr_length();
    for(auto i = 0; i < adj_list.get_curr_length(); i ++) {
        degrees[adj_list[i].get_size()].push_back(i);
    }

    print_degree_array(degrees,adj_list.get_curr_length());

    int colors[num_verts];

    memset(colors, -1, sizeof(colors[0]) * num_verts);

    for(int i= 0; i < num_verts; i ++) {
        while(degrees[i].has_next()) {
            color_vert(degrees[i].get_next(),colors,adj_list);
        }
    }


    for(int i=0; i < num_verts; i ++) {
        out <<i <<", " <<colors[i] <<endl;
    }


}

void GraphColorer::random_order_coloring(Adj_List<uint> &adj_list, ostream &out) {
    auto num_verts = adj_list.get_curr_length();

    int colors[num_verts];
    memset(colors, -1, sizeof(colors[0]) * num_verts);

    int used_verts[num_verts];
    memset(used_verts, -1, sizeof(used_verts[0]) * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<size_t> distribution(0,num_verts - 1);


    for(int i=0; i < num_verts; i ++) {
        auto first = distribution(generator);
        if(used_verts[first] == -1) {
//            cout << "Coloring " <<first <<endl;
            color_vert(first,colors,adj_list);
            used_verts[first] = 1;
        } else {
            i--;
        }

    }

    for(int i=0; i < num_verts; i ++) {
        out <<i <<", " <<colors[i] <<endl;
    }




}

void GraphColorer::smallest_last_vertex(Adj_List<uint> &adj_list, ostream &out) {
    struct Vertex{
        Vertex* ptr_to_degree_list;
        size_t degree;
        size_t value;
    };
    Linked_List<uint> degrees[adj_list.get_curr_length()];



    for(auto i=0; i < adj_list.get_curr_length(); i ++) {
        degrees[adj_list[i].get_size()].push_back(i);
    }


    cout << "============== DEGREE STRUCTURE ==============" <<endl;
    for(int i =0; i < adj_list.get_curr_length(); i ++) {
        cout << i<<": ";
        while(degrees[i].has_next()) {
            cout << degrees[i].get_next();
            if(degrees[i].has_next()) cout <<", ";
        }
        cout << endl;
    }

}

#endif //DATA_STRUCTURES_GRAPHCOLORER_H
