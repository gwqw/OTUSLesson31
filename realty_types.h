#pragma once

#include <dlib/svm_threaded.h>
#include <dlib/rand.h>

using sample_type = dlib::matrix<double,7,1>;

using kernel_type = dlib::polynomial_kernel<sample_type>;
using ovo_trainer = dlib::one_vs_one_trainer<dlib::any_trainer<sample_type>>;
using poly_kernel = dlib::polynomial_kernel<sample_type>;
using rbf_kernel = dlib::radial_basis_kernel<sample_type>;

using SampleDataBase = std::map<int, std::vector<sample_type>>;