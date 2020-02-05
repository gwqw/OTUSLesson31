#include "input_parser.h"

#include <string_view>
#include <sstream>
#include <cassert>

#include "str_utils.h"

using namespace std;

std::vector<sample_type> parseFromStreamForTrain(std::istream& in) {
    // format: longitude;latitude;room_number;price;area;kitchen_area;floor;number_of_flours
    // good_floor = floor == 1 or floor == number_of_floors
    // 7 dimensions
    constexpr int FLOOR = 6;
    constexpr int FLOOR_NUM = 7;
    vector<sample_type> res;
    for (string line; getline(in, line); ) {
        if (line.empty()) break;
        string_view data{line};
        size_t i = 0;
        sample_type m;
        int floor = 0;
        while (!data.empty()) {
            auto word = read_token(data, ";");
            if (i < FLOOR) {
                m(i) = stod(string(word));
            } else if (i == FLOOR) {
                floor = convertToInt(word);
            } else if (i == FLOOR_NUM) {
                int floor_num = convertToInt(word);
                m(FLOOR) = floor == 0 || floor == floor_num ? 0.0 : 1.0;
            } else {
                break;
            }
            i++;
        }
        res.push_back(m);
    }

    return res;
}

std::string serializeSample(const sample_type& sample) {
    stringstream out;
    serializeSample(out, sample);
    return out.str();
}

void serializeSample(std::ostream& out, const sample_type& sample) {
    bool is_first = true;
    for (long int j = 0; j < sample.size(); ++j) {
        if (is_first) {
            is_first = false;
        } else {
            out << ";";
        }
        out << sample(j);
    }
}

sample_type deserializeSample(std::string_view line) {
    // format: longitude;latitude;room_number;price;area;kitchen_area;is_not_first_or_last
    // 7 dimensions
    constexpr int LAST = 7;
    sample_type res;
    size_t i = 0;
    while (!line.empty()) {
        auto word = read_token(line, ";");
        if (i+1 < LAST) {
            res(i++) = stod(string(word));
        } else if (i+1 == LAST) {
            res(i++) = convertToInt(word) == 0 ? 0.0 : 1.0;
        } else {
            break;
        }
    }

    return res;
}

void samplesSerialize(const std::vector<sample_type>& samples,
                      const std::vector<double>& labels, const std::string& filename)
{
    ofstream f(filename);
    samplesSerialize(samples, labels, f);
}

void samplesSerialize(const std::vector<sample_type>& samples,
                      const std::vector<double>& labels, std::ostream& out)
{
    assert(samples.size() == labels.size());
    for (size_t i = 0; i < labels.size(); ++i) {
        out << labels[i] << ';';
        serializeSample(out, samples[i]);
        out << '\n';
    }
}

SampleDataBase samplesDeserialize(const std::string& filename)
{
    ifstream f(filename);
    if (!f) {
        throw invalid_argument("Can't find file " + filename);
    }
    return samplesDeserialize(f);
}

SampleDataBase samplesDeserialize(std::istream& in)
{
    SampleDataBase res;
    for (string line; getline(in, line); ) {
        string_view data{line};
        auto word = read_token(data, ";");
        int i = convertToInt(word);
        res[i].push_back(deserializeSample(data));
    }
    return res;
}