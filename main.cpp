#include <iostream>
#include <random>
#include <bitset>
#include <cmath>
#include <vector>

using namespace std;

class Individual {
public:
    double x,y,fitness_score;
    string binary_code;
    string gray_code;

    static mt19937 gen;

    Individual(){
        this->x = this->get_random_number(-10,10,3, &binary_code);
        this->y = this->get_random_number(-10,10,3);
        this->fitness_score = this->calc_fitness(this->x, this->y);
        this->gray_code = this->double2gray(this->x) + this->double2gray(this->y);
    }
    Individual(double x, double y){
        this->x = x;
        this->y = y;
        this->fitness_score = this->calc_fitness(this->x, this->y);
        this->gray_code = this->double2gray(this->x) + this->double2gray(this->y);
    }
    Individual(string gray_code){
        this->gray_code = gray_code;
        this->x = this->gray2double(gray_code.substr(0,9));
        this->y = this->gray2double(gray_code.substr(9,9));  
        this->fitness_score = this->calc_fitness(this->x, this->y);  
    }

static double calc_fitness(double x, double y){
    return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
}
static int find_presentable_bits_count(int range){
    int bit = 0;
    while((pow(2,bit)-1)<range){
        bit++;
    }
    return bit
}
double get_random_number(int min, int max, int precision){
    int range = (max - min)*pow(10,precision);
    int bits = find_presentable_bits_count(range);

    uniform_int_distribution<> dis(0, range);
    int range = dis(gen);
    this->binary_code = bitset<bits>(range).to_string();
    
    double x = min + (range/(pow(2,bits)-1)*(max-min));
}

static string double2binary(double x, int precision=4){
    string pozitive = (x >= 0) ? "0" : "1";
    int integral_part = int(abs(x));
    double fractional_part = abs(x) - abs(integral_part);

    string binary = ""; // 1 bit + 4 bit + 4 bit
    string binary_part1 = pozitive;
    string binary_part2 = bitset<4>(integral_part).to_string();
    string binary_part3 = "";
    while (precision--) {
        fractional_part *= 2;
        if (fractional_part >= 1.0) {
            binary_part3 += "1";
            fractional_part -= 1.0;
        } else {
            binary_part3 += "0";
        }
    }

    binary = binary_part1 + binary_part2 + binary_part3;
    return binary;
}

static string binary2gray(string binary){
    bitset<9> binary_bits(binary);
    bitset<9> gray_bits = binary_bits ^ (binary_bits >> 1);
    return gray_bits.to_string();
}

static string double2gray(double x, int precision=4){
    string binary = double2binary(x, precision);
    string gray = binary2gray(binary);
    return gray;
}

static string gray2binary(string gray){
    string binary = gray;
    binary[0] = gray[0];

    for (int i = 1; i < gray.length(); i++) {
        binary[i] = ((binary[i-1] - '0') ^ (gray[i] - '0')) + '0';
    }

    return binary;
}

static double binary2double(string binary, int precision=4){    
    int sign = (binary[0] == '0') ? 1 : -1;
    
    string integral_binary = binary.substr(1,4);
    string fractional_binary = binary.substr(5,precision);
    int integral_part = stoi(integral_binary, nullptr, 2);
    double fractional_part = 0.0;
    for (int i = 0; i < fractional_binary.length(); i++) {
        if (fractional_binary[i] == '1') {
            fractional_part += pow(2, -(i + 1));
        }
    }
    return sign * (integral_part + fractional_part);
}

static double gray2double(string gray){
    string binary = gray2binary(gray);
    double x = binary2double(binary);
    return x;
}

};

mt19937 Individual::gen(random_device{}());

class Population {
    public:
    vector<Individual> population;
    double min_fitness_score_index;

    Population(int population_size){
        for (int i = 0; i < population_size; i++) {
            population.push_back(Individual());
        }
        min_fitness_score_index = get_min_fitness_score_index(this->population);
    }

    static vector<Individual> next_generation(vector<Individual> population, double elitist_ratio, int tournament_size){
        /*
        1- find elitist popülation(%5)
        2- tournament selection
            1- random select tournament_size individual
            2- select the best 2 parent
            3- generate child


        */
    }

    static int get_min_fitness_score_index(vector<Individual> population){
        int min_fitness_score_index = 0;
        double min_fitness_score = population[0].fitness_score;
        for (int i = 1; i < population.size(); i++) {
            if (population[i].fitness_score < min_fitness_score) {
                min_fitness_score_index = i;
                min_fitness_score = population[i].fitness_score;
            }
        }
        return min_fitness_score_index;
    }
};

vector<Individual> elit_population(vector<Individual> population, double elitist_ratio){
    int elitist_count = int(population.size() * elitist_ratio);
    vector<Individual> elitist;

    int min_fitness = population[0].fitness_score;

    for (int i = 0; i < elitist_count; i++) {
        elitist.push_back(population[i]);
    }
    return elitist;
}

vector<Individual> selection(vector<Individual> population, double elitist_ratio, int tournament_size){
}


int main() {

}