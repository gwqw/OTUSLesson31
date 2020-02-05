#pragma once

#include <vector>
#include <string>

#include "realty_types.h"

namespace RealtyTrainer {
    std::vector<double> cluster(const std::vector<sample_type>& samples, size_t cluster_num);
    void train(const std::vector<sample_type>& samples, const std::vector<double>& labels,
            const std::string& filename);
};