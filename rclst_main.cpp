#include <iostream>
#include <string>

#include "input_parser.h"
#include "trainer.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "rclst -- prog to train on realty data.\n"
                "rclst <cluster_num> <prefix_filename> [<gamma>, <coeff>, <degree>]\n"
                "<cluster_num> -- number of cluster to search\n"
                "<prefix_name> -- prefix name for output files\n"
                "<gamma>, <coeff>, <degree> -- parameters for cluster and training. "
                "Defaults are 0.1, 1, 2\n";
        return 0;
    }
    try {
        auto cluster_num = stol(argv[1]);
        string prefix_filename{argv[2]};
        string train_filename = prefix_filename + ".trn";
        string samples_filename = prefix_filename + ".smp";
        double gamma = 0.1;
        double coeff = 1;
        double degree = 2;
        if (argc > 3) {
            gamma = stod(argv[3]);
            if (argc > 4) {
                coeff = stod(argv[4]);
                if (argc > 5) {
                    degree = stod(argv[5]);
                }
            }
        }

        auto samples = parseFromStreamForTrain();
        RealtyTrainer trainer(gamma, coeff, degree);
        auto labels = trainer.cluster(samples, cluster_num);
        trainer.train(samples, labels, train_filename);
        samplesSerialize(samples, labels, samples_filename);

        return 0;
    } catch (const exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}

