#define BOOST_TEST_MODULE yamr_test_module
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <string_view>

#include "realty_types.h"
#include "input_parser.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(input_parser_test_suite)

    BOOST_AUTO_TEST_CASE(test_deserialize_sample) {
        string sample_line = "86.116781;55.335492;2;4326901.00;54.00;7.00;1";
        auto res_sample = deserializeSample(sample_line);
        sample_type expected{86.116781, 55.335492, 2, 4326901.00, 54.00, 7.00, 1};
        BOOST_CHECK(res_sample == expected);
    }

    BOOST_AUTO_TEST_CASE(test_parseFromStream) {
        stringstream ss;
        ss << "86.116781;55.335492;2;4326901.00;54.00;7.00;5;5\n"
           << "167.13697893951837;426.29494962308837;2.0;66756990.95520226;62.63344600354503;20.62633446003545;2;10\n";
        auto res_samples = parseFromStreamForTrain(ss);
        BOOST_CHECK(res_samples.size() == 2);
        decltype(parseFromStreamForTrain(ss)) expected{
            {86.116781, 55.335492, 2, 4326901.00, 54.00, 7.00, 0},
            {167.13697893951837, 426.29494962308837, 2.0, 66756990.95520226, 62.63344600354503, 20.62633446003545, 1},
        };
        BOOST_CHECK(res_samples == expected);
    }

BOOST_AUTO_TEST_SUITE_END()