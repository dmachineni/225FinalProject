// clang-format off
// clang-format on
// Framework Set-up //
#include "graph.h"
#include "vertex.h"

#include <stdexcept>

// Helpers/Constants //

// Test Cases //
TEST_CASE("adj__list_size == airport_data_size", "[adj_list]") {
    Graph g;
    REQUIRE( g.getadjacency_lists() == g.getAirports() );
}

TEST_CASE("adj_list_data == airport_data", "[adj_list]") {
    Graph g;
    REQUIRE( g.getAdjList(2810) == "2990, 2979, 1735, 2954, 2983, 1726, 3964, 2960, 4029, 1701, 2948, 2958, 2985, 2975, 6147, 2988, 4374," );
}

TEST_CASE("adj_list_data == airport_data", "[adj_list]") {
    Graph g;
    REQUIRE( g.getAdjList(40) == "132, 147, 5487, 140," );
}
