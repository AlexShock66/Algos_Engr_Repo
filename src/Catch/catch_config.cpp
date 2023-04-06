//
// Created by Alex Shockley on 1/30/2022.
//
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
/*
 * Build target so that we dont have to recompile catch every time we wanted to edit the main program
 */
int main() {
    Catch::Session().run();

    return 0;
}

