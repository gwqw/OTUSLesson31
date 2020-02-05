#include "trainer.h"

#include <iostream>

#include <dlib/clustering.h>
#include <dlib/svm_threaded.h>

using namespace std;
using namespace dlib;

std::vector<double> RealtyTrainer::cluster(const std::vector<sample_type> &samples, size_t cluster_num) {
    dlib::kcentroid<kernel_type> kc{kernel_type{}};
    dlib::kkmeans<kernel_type> test{kc};

    test.set_number_of_centers(cluster_num);
    std::vector<sample_type> initial_centers;
    pick_initial_centers(cluster_num, initial_centers, samples, test.get_kernel());
    test.train(samples, initial_centers);

    std::vector<double> res;
    res.reserve(samples.size());
    for (const auto& sample : samples) {
        res.push_back(test(sample));
    }
    return res;
}

void RealtyTrainer::train(const std::vector<sample_type>& samples, const std::vector<double> &labels,
        const std::string& filename) {
    //make the one_vs_one_trainer.
    ovo_trainer trainer;
    // make the binary trainers and set some parameters
    krr_trainer<rbf_kernel> rbf_trainer;
    svm_nu_trainer<poly_kernel> poly_trainer;
    poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));
    rbf_trainer.set_kernel(rbf_kernel(0.1));
    // Now tell the one_vs_one_trainer that, by default, it should use the rbf_trainer
    // to solve the individual binary classification subproblems.
    trainer.set_trainer(rbf_trainer);
    // We can also get more specific.  Here we tell the one_vs_one_trainer to use the
    // poly_trainer to solve the class 1 vs class 2 subproblem.  All the others will
    // still be solved with the rbf_trainer.
    trainer.set_trainer(poly_trainer, 1, 2);
    // Next, if you wanted to obtain the decision rule learned by a one_vs_one_trainer you
    // would store it into a one_vs_one_decision_function.
    one_vs_one_decision_function<ovo_trainer> df = trainer.train(samples, labels);
    // If you want to save a one_vs_one_decision_function to disk, you can do
    // so.  However, you must declare what kind of decision functions it contains.
    one_vs_one_decision_function<ovo_trainer,
            decision_function<poly_kernel>,  // This is the output of the poly_trainer
            decision_function<rbf_kernel>    // This is the output of the rbf_trainer
    > df2;

    // Put df into df2 and then save df2 to disk.  Note that we could have also said
    // df2 = trainer.train(samples, labels);  But doing it this way avoids retraining.
    df2 = df;
    serialize(filename) << df2;
}
