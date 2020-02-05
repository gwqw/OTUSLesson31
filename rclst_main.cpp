#include <iostream>
#include <string>

#include "input_parser.h"
#include "trainer.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "rclst -- prog to train on realty data.\n"
                "rclst <cluster_num> <prefix_filename>\n";
        return 0;
    }
    try {
        auto cluster_num = stol(argv[1]);
        string prefix_filename{argv[2]};
        string train_filename = prefix_filename + ".trn";
        string samples_filename = prefix_filename + ".smp";

        auto samples = parseFromStreamForTrain();
        auto labels = RealtyTrainer::cluster(samples, cluster_num);
        RealtyTrainer::train(samples, labels, train_filename);
        samplesSerialize(samples, labels, samples_filename);

        return 0;
    } catch (const exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}

