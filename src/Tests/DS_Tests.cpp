//
// Created by Alex Shockley on 1/30/2022.
//
#include "../Catch/catch.hpp"
using namespace std;
#include <string>
#include "../Data_Structures/Linked_List.h"
#include "../Data_Structures/Adj_List.h"
#include <iostream>
/*
 * Catch tests to make sure that LinkedList function as intended.
 */
TEST_CASE("Linked List") {
    Linked_List<int> int_list;
    Linked_List<string> string_list;
    Linked_List<int *> int_ptr_list;
    for(int i =0; i < 10; i ++) {
        int_list.push_back(i);
        int_ptr_list.push_back(new int(i));
    }
    string_list.push_back("Hello World");
    string_list.push_back("Hello");
    string_list.push_back("World");
    SECTION("Basic construction") {
        CHECK(int_list.get_size() == 10);
        CHECK(string_list.get_size() == 3);
        CHECK(int_ptr_list.get_size() == 10);
        auto a = int_list.pop_back();
        CHECK(a == 9);
        CHECK(int_list.get_size() == 9);

    }
    SECTION("Copy and Assignment Operators") {
        auto b(int_list);
        auto c = int_list;
        //Copy Constructor
        CHECK(b.get_size() == 10);
        CHECK(b.at(0) == 0);
        b.pop_back();
        CHECK(b.get_size() == 9);
        CHECK(b.at(8) == 8);
        //Assignment Operator
        CHECK(int_list.get_size() == 10);
        CHECK(c.get_size() == 10);
        CHECK(c.at(0) == 0);
        c.pop_back();
        CHECK(c.get_size() == 9);
        CHECK(c.at(8) == 8);
        CHECK(int_list.get_size() == 10);

    }
    SECTION("Push Node") {
        auto a = int_list.push_back_node(10);

        CHECK(a->data == 10);

        Linked_List<int> theList;
        theList.push_back_node(0);
        auto b = theList.push_back_node(1);
        theList.push_back_node(2);
        CHECK(theList.get_size() == 3);
        b->data = 15;
        CHECK(theList.at(1) == 15);
        theList.remove_node(b);
        CHECK(theList.get_size() == 2);
        CHECK(theList.at(0) == 0);
        CHECK(theList.at(1) == 2);

    }
    SECTION("List Traversal") {
        CHECK(int_list.at(0) == 0);
        CHECK(int_list.at(9) == 9);
        CHECK_THROWS(int_list.at(1000));
        CHECK_THROWS(int_list.at(10));
        CHECK(int_list.at(int_list.get_size() -1) == 9);
        int_list.at(0) = 5000;
        CHECK(int_list.at(0) == 5000);

    }

    SECTION("Removing elements") {
        CHECK(int_list.pop_back() == 9);
        CHECK(int_list.get_size() == 9);
        int_list.remove_at(5);
        CHECK(int_list.get_size() == 8);

    }
    SECTION("Custom Iterator") {
        int val = 0;
        while(int_list.has_next()) {
            CHECK(int_list.get_next() == val);
            val++;
        }

    }
}

TEST_CASE("Adj_List") {
    Adj_List<string> str_list;
    Adj_List<string> str_init_list(10);

    str_list.push_root("Root0");
    str_list.push_root("Root1");
    str_list.push_root("Root2");
    str_list.push_root("Root3");
    str_list.push_root("Root4");
    str_list.push_root("Root5");
    str_list.push_root("Root6");
    str_list.push_root("Root7");
    str_list.push_root("Root8");
    str_list.push_root("Root9");
    str_list.push_root("Root10");
    str_list.push_root("Root11");

    str_init_list.push_root("Root0");
    str_init_list.push_root("Root1");
    str_init_list.push_root("Root2");
    str_init_list.push_root("Root3");

    str_list.push_value(0,"Node 0,0");
    str_list.push_value(3,"Node 3,0");
    str_list.push_value(3,"Node 3,1");
    str_list.push_value(3,"Node 3,2");
    str_list.push_value(3,"Node 3,3");

    str_init_list.push_value(0,"Node 0,0");
    str_init_list.push_value(3,"Node 3,0");
    str_init_list.push_value(3,"Node 3,1");
    str_init_list.push_value(3,"Node 3,2");
    str_init_list.push_value(3,"Node 3,3");

    auto cpy_list(str_list);
    auto eq_list = str_list;
    SECTION("Sizing functions") {
        CHECK(str_list.get_max_length() == 20);
        CHECK(str_list.get_curr_length() == 12);

        CHECK(str_init_list.get_max_length() == 10);
        CHECK(str_init_list.get_curr_length() == 4);

        CHECK(cpy_list.get_max_length() == 20);
        CHECK(cpy_list.get_curr_length() == 12);

        CHECK(eq_list.get_max_length() == 20);
        CHECK(eq_list.get_curr_length() == 12);
    } SECTION("Pop Functions") {
        //TODO Add pop tests
    } SECTION("Checking Accessing") {
        CHECK(str_list[0].get_size() == 1);
        CHECK(str_list[3].get_size() == 4);
        CHECK(str_init_list[0].get_size() == 1);
        CHECK(str_init_list[3].get_size() == 4);
        CHECK(cpy_list[0].get_size() == 1);
        CHECK(cpy_list[3].get_size() == 4);
        CHECK(eq_list[0].get_size() == 1);
        CHECK(eq_list[3].get_size() == 4);

        CHECK(str_list[0].at(0) == "Node 0,0");
        CHECK(str_list[3].at(0) == "Node 3,0");
        CHECK(str_init_list[0].at(0) == "Node 0,0");
        CHECK(str_init_list[3].at(0) == "Node 3,0");

        CHECK(cpy_list[0].at(0) == "Node 0,0");
        CHECK(cpy_list[3].at(0) == "Node 3,0");
        CHECK(eq_list[0].at(0) == "Node 0,0");
        CHECK(eq_list[3].at(0) == "Node 3,0");
        CHECK_THROWS(cpy_list[0].at(1));
    }SECTION("Pretty Print"){
        auto int_list = Adj_List<int>();
        for(int i =0; i < 5; i ++) {
            int_list.push_root(i);
        }
        for(int i =0; i <25; i ++) {
            int_list.push_value(std::rand() % 5,i);
        }
        int_list.prettyPrint(std::cout);

    }
}