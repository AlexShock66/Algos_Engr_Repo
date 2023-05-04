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
    static void print_degree_structure(Adj_List<uint> &adj_list,Linked_List<uint> * degrees);

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

void GraphColorer::print_degree_structure(Adj_List<uint> &adj_list, Linked_List<uint> *degrees) {
    cout << "============== DEGREE STRUCTURE ==============" <<endl;
    for(int i =0; i < adj_list.get_curr_length(); i ++) {
        cout << i<<": ";
        degrees[i].print();
        cout << endl;
    }
}

#define DEBUG
void GraphColorer::smallest_last_vertex(Adj_List<uint> &adj_list, ostream &out) {
    #ifdef DEBUG
        cout << "Original List Structure" <<endl;
        adj_list.prettyPrint(std::cout);
        cout << endl;
    #endif
    auto num_verts = adj_list.get_curr_length();
    Linked_List<uint> degrees[adj_list.get_curr_length()];

    uint degree_lookup[adj_list.get_curr_length()]; //Degree lookup = what is my current degree for that node

    Linked_List<uint>::list_node* mapper[adj_list.get_curr_length()]; //mapper serves as a lookup from node -> NodePtr in Degree structure

    for(auto i=0; i < adj_list.get_curr_length(); i ++) {
        mapper[i] = degrees[adj_list[i].get_size()].push_back_node(i);
        degree_lookup[i] = adj_list[i].get_size();
    }
    #ifdef DEBUG
        cout << "================= MAPPER STRUCTURE =================" <<endl;
        for(auto i=0; i < adj_list.get_curr_length(); i ++){
            cout << i << " -> " << mapper[i]->data <<endl;
        }

        print_degree_structure(adj_list,degrees);

        cout << "================================================" <<endl;
    #endif
    bool clique_found = false;
    uint terminal_clique_size =2;
    uint ordering[adj_list.get_curr_length()];
    uint current_iteration = 0;
    uint largest_degree_when_deleted = 0;
    for(int i =0; i < adj_list.get_curr_length(); i ++) {
        if(degrees[i].get_size() == i + 1 && !clique_found){
            #ifdef DEBUG
                cout << "\nFound Terminal Clique of size: " <<num_verts <<endl;
            #endif
            clique_found = true;
            terminal_clique_size = i + 1;
        }
        if(degrees[i].has_next()) {
            auto curr = degrees[i].get_next();
            degrees[i].pop_front();
            degrees[i].reset_iterator();
            mapper[curr] = nullptr;
            //curr is the node with the lowest degree
            if(largest_degree_when_deleted < degree_lookup[curr]) largest_degree_when_deleted = degree_lookup[curr];
            #ifdef DEBUG
                cout << "Removing: " <<curr <<" With Degree: " << degree_lookup[curr]<<endl;
            #endif
            ordering[current_iteration] = curr;
            current_iteration++;
            //Now we must iterate through the adj nodes to curr and lower the degree by 1 and
            while(adj_list[curr].has_next()){
                auto adj_node = adj_list[curr].get_next();
                auto node_ptr = mapper[adj_node];
                if(node_ptr == nullptr) continue;
                auto degree_of_adj = degree_lookup[adj_node];
                degrees[degree_of_adj].remove_node(node_ptr); //TODO THIS LINE BREAKS BECAUSE OF POINTERS BEING RESET (PREV IS RESETTING TO DELETED ONE)
                mapper[adj_node] = degrees[degree_of_adj -1 ].push_back_node(adj_node);
                degree_lookup[adj_node] -=1;
                degrees[degree_of_adj].reset_iterator();
            }
            adj_list[curr].reset_iterator();
            degrees[i].reset_iterator();

//            degrees[degree_lookup[curr]].remove_node(mapper[curr]);
//            degrees[i].reset_iterator();
//            auto node_ptr = mapper[curr];
//            auto degree_of_adj = degree_lookup[curr];
//            degrees[degree_of_adj].remove_node(node_ptr);
            i -= 2;
            if(i <-1) i = -1;
            num_verts-=1;
            print_degree_structure(adj_list,degrees);

        }

    }

    int colors[adj_list.get_curr_length()];
    memset(colors, -1, sizeof(colors[0]) * adj_list.get_curr_length());
    for(int i=0;i <current_iteration; i ++) {

        color_vert(ordering[i],colors,adj_list);
    }

    #ifdef DEBUG
        cout << "Largest Degree When Deleted: " << largest_degree_when_deleted <<endl;
        cout << "Terminal Clique Size: " << terminal_clique_size << endl;
    #endif
    for(int i=0; i < adj_list.get_curr_length(); i ++) {
        #ifdef DEBUG
        cout << "Vert " <<i <<" -> Color " <<colors[i] <<endl;
        #endif
        out << i <<"," <<colors[i] <<endl;
    }

}

#endif //DATA_STRUCTURES_GRAPHCOLORER_H
