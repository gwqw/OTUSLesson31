#pragma once

#include <vector>
#include <iostream>
#include <utility>

#include "realty_types.h"

std::pair<std::vector<sample_type>, std::vector<double>> parseFromStream(std::istream& in = std::cin);