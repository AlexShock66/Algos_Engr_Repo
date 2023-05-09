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
#include "GraphGenerator.h"
class GraphColorer {

private:
    static void least_degree_last(Adj_List<uint> &adj_list,std::ostream &out);
    static void print_degree_array( Linked_List<uint> *theList,int theSize);
    static void color_vert(size_t vert_to_color, int *colors, Adj_List<uint> &theList);
    static void random_order_coloring(Adj_List<uint> &adj_list,std::ostream &out);
    static void smallest_last_vertex(Adj_List<uint> &adj_list,std::ostream &out);
    static void print_degree_structure(Adj_List<uint> &adj_list,Linked_List<uint> * degrees);
    static void depth_first_coloring(Adj_List<uint> &adj_list,std::ostream &out);

public:
    static void generate_stats(std::ofstream &out, std::string distro, string algorithm, size_t start_verts, size_t end_verts,size_t start_edge, size_t end_edge, size_t vert_increment, size_t edge_increment);
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
    auto start = high_resolution_clock::now();
    if(algorithm == "least_degree_last") {
        GraphColorer::least_degree_last(adj_list,out);
    } else if(algorithm == "random") {
        GraphColorer::random_order_coloring(adj_list,out);
    } else if(algorithm == "SLV") {
        GraphColorer::smallest_last_vertex(adj_list,out);
    } else if (algorithm == "DFS") {
        GraphColorer::depth_first_coloring(adj_list,out);
    } else {
        cerr << "UNKNOWN ALGORITHM: " << algorithm << endl;
        return;
    }
    auto stop = high_resolution_clock::now();
    auto duration_ordering = duration_cast<microseconds>(stop - start);
    out << "\n\n\nTimimg:," << duration_ordering.count();
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

    for(int i= num_verts-1; i > 0; i --) {
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

//#define DEBUG
/*
 * Generates a file with the following format:
 *      Largest Degree when deleted
 *      Terminal Clique Size
 *      Ordering time
 *      Coloring time
 *
 *      <Vert 1>,<Color of Vert 1>
 *      <Vert 2>,<Color of Vert 2>
 *      ...
 *      <Vert n>,<Color of Vert n>
 */
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
    uint degree_when_del[num_verts];
    bool clique_found = false;
    uint terminal_clique_size =2;
    uint ordering[adj_list.get_curr_length()];
    uint current_iteration = 0;
    uint largest_degree_when_deleted = 0;
    auto start = high_resolution_clock::now();
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
            degree_when_del[curr] = i;
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
                degrees[degree_of_adj].remove_node(node_ptr);
                mapper[adj_node] = degrees[degree_of_adj -1 ].push_back_node(adj_node);
                degree_lookup[adj_node] -=1;
                degrees[degree_of_adj].reset_iterator();
            }
            adj_list[curr].reset_iterator();
            degrees[i].reset_iterator();

            i -= 2;
            if(i <-1) i = -1;
            num_verts-=1;
            #ifdef DEBUG
            print_degree_structure(adj_list,degrees);
            #endif
        }

    }
    auto stop = high_resolution_clock::now();
    auto duration_ordering = duration_cast<microseconds>(stop - start);
    int colors[adj_list.get_curr_length()];
    start = high_resolution_clock::now();
    memset(colors, -1, sizeof(colors[0]) * adj_list.get_curr_length());
    for(int i=current_iteration;i >=0; i --) {

        color_vert(ordering[i],colors,adj_list);
    }
    stop = high_resolution_clock::now();
    auto duration_coloring = duration_cast<microseconds>(stop - start);

    #ifdef DEBUG
        cout << "Largest Degree When Deleted: " << largest_degree_when_deleted <<endl;
        cout << "Terminal Clique Size: " << terminal_clique_size << endl;
        cout << "Ordering Time: " << duration_ordering.count() <<endl;
        cout << "Coloring Time: " << duration_coloring.count() << endl;
    #endif
    out << "Largest Degree when deleted:," << largest_degree_when_deleted <<endl;
    out << "Terminal Clique Size:," << terminal_clique_size << endl;
    out << "Time to order( microseconds ):,"<< duration_ordering.count() <<endl;
    out << "Time to color( microseconds ):,"<<duration_coloring.count() <<endl;

    out << "vert,color" <<endl;
    for(int i=0; i < adj_list.get_curr_length(); i ++) {
        #ifdef DEBUG
        cout << "Vert " <<i <<" -> Color " <<colors[i] <<endl;
        #endif
        out << i <<"," <<colors[i] <<endl;
    }

    out << "Color Order, Degree when Deleted" <<endl;
        for(int i=0; i < adj_list.get_curr_length(); i ++) {
//            out << i << ","<<degree_when_del[i] <<endl;
            out << i <<"," << degree_when_del[ordering[i]] <<endl;
        }


}

void GraphColorer::depth_first_coloring(Adj_List<uint> &adj_list, ostream &out) {
    auto num_verts = adj_list.get_curr_length();

    int colors[num_verts];
    memset(colors, -1, sizeof(colors[0]) * num_verts);

    int visited[num_verts];
    memset(visited, -1, sizeof(visited[0]) * num_verts);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<size_t> distribution(0,num_verts -1);

    Linked_List<size_t> queue;
    Linked_List<size_t> coloring_order;

    for(auto i=0; i < num_verts; i ++) {

        auto start_vert = i;
        if(visited[start_vert] != -1) continue;
//        cout << "Start Vert: " <<start_vert <<endl;
        queue.push_back(start_vert);

        while(queue.get_size() != 0) {
            auto curr = queue.pop_front();
            if(visited[curr] == -1) {
                coloring_order.push_back(curr);
                while(adj_list[curr].has_next()) {
                    queue.push_back(adj_list[curr].get_next());

                }
                adj_list[curr].reset_iterator();
                visited[curr] = 1;
            }

        }
    }

//    cout << "Coloring Ordering:\n";
    while(coloring_order.has_next()) {
        auto curr = coloring_order.get_next();
//        cout << curr <<", ";
        GraphColorer::color_vert(curr,colors,adj_list);
    }

    for(auto i=0; i < num_verts; i ++) {
        out << i <<"," <<colors[i] <<endl;
    }
//    cout << endl;
//    cout << "Visited Structure" <<endl;
//    for(int i=0; i < num_verts; i ++) {
//        cout << visited[i] <<", ";
//    }


}

void GraphColorer::generate_stats(std::ofstream &out, std::string distro,string algorithm, size_t start_verts, size_t end_verts,
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
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(distro == "cycle") {

                auto theGraph = GraphGenerator::generate_cycle(verts);
                start = high_resolution_clock::now();
                GraphColorer::color_graph(algorithm,theGraph);
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);

            } else if(distro == "complete") {
                auto theGraph = GraphGenerator::generate_complete(verts);
                start = high_resolution_clock::now();
                GraphColorer::color_graph(algorithm,theGraph);
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
            } else {
                auto theGraph = GraphGenerator::generate_distro(distro,verts,edges);
                start = high_resolution_clock::now();
                GraphColorer::color_graph(algorithm,theGraph);
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
            }


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




}
#endif //DATA_STRUCTURES_GRAPHCOLORER_H
