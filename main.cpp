#include <iostream>
#include <random>
#include <bitset>
#include <cmath>
#include <vector>
using namespace std;

class Individual {
    public:
        double x, y, penalty_fitness_score;
        string gray_code;
        static const uint bits = 15;
        static mt19937 gen;
    
        Individual() {
            string binary_code = "";
            uniform_int_distribution<> dis(0, pow(2, bits)-1);
            int range1 = dis(gen);
            int range2 = dis(gen);
            binary_code = bitset<bits>(range1).to_string() + bitset<bits>(range2).to_string();
            this->gray_code = binary2gray(binary_code);
            gray2double(this->gray_code, this->x, this->y);
            penalty_fitness_score = calc_penalty_fitness(x, y);
        }
    
        Individual(string gray_code){
            this->gray_code = gray_code;
            gray2double(this->gray_code, this->x, this->y);
            penalty_fitness_score = calc_penalty_fitness(x, y);  
        }

        static void gray2double(string gray, double &x, double &y){
            string binary = gray2binary(gray);
            x = binary2double(binary.substr(0,15));
            y = binary2double(binary.substr(15,15));
        }

        static double calc_fitness(double x, double y){
            return pow((x + 2*y - 7), 2) + pow((2* x + y - 5), 2);
        }

        static double calc_penalty_fitness(double x, double y){
            double penalty = 0;
            double r = 1000;
        
            if(x > 10) penalty += pow(x - 10,2);
            if(x < -10) penalty += pow(-10 - x,2);
            if(y > 10) penalty += pow(y - 10,2);
            if(y < -10) penalty += pow(-10 - y,2);
        
            return calc_fitness(x,y) + r*penalty;
        }
        
        static string binary2gray(string binary){
            bitset<30> binary_bits(binary);
            bitset<30> gray_bits = binary_bits ^ (binary_bits >> 1);
            return gray_bits.to_string();
        }
    
        static string gray2binary(string gray){
            string binary = gray;
            binary[0] = gray[0];
    
            for (int i = 1; i < gray.length(); i++)
                binary[i] = ((binary[i-1]-'0')^(gray[i]-'0'))+'0';
    
            return binary;
        }
    
        static double binary2double(string binary){    
            bitset<15> binary_bits(binary);
            int val = binary_bits.to_ulong();
            double x = -10 + ((double)val/(pow(2,15)-1))*20;
            return x;
        }
    
    };

mt19937 Individual::gen(random_device{}());

class Population {
public:
    vector<Individual> population;
    double min_fitness_score_index;

    static int max_fes;  
    static int current_fes; 

    
    Population(int population_size){
        for (int i = 0; i < population_size; i++) {
            population.push_back(Individual());
            current_fes++; 
        }
        min_fitness_score_index = get_min_fitness_score_index(this->population);
    }

    Population(vector<Individual> population){
        this->population = population;
        min_fitness_score_index = get_min_fitness_score_index(this->population);
        current_fes += population.size();
    }

    static Population create_next_generation(vector<Individual> population, int tournament_size, int population_size, double mutation_rate){
        vector<Individual> next_gen = generate_next_generation(population, tournament_size, population_size, mutation_rate);
        return Population(next_gen);
    }

    static vector<Individual> generate_next_generation(vector<Individual> population, int tournament_size, int population_size, double mutation_rate){
        vector<Individual> next_generation;
        for (int i = 0; i < population_size/2; i++) {
            vector<Individual> children = generate_children(population, tournament_size);
            
            next_generation.push_back(children[0]);
            next_generation.push_back(children[1]);
    
            current_fes += 2;

            if (current_fes >= max_fes){
                next_generation.resize(population_size); 
                break;
            }
        }
    
        for (auto &individual : next_generation){
            for (char &bit : individual.gray_code){
                bool mutation = (rand() % 100) < mutation_rate*100;
                if(mutation)
                    bit = (bit == '0') ? '1' : '0';
            }
        }
    
        return next_generation;
    }

    static vector<Individual> generate_children(vector<Individual> population, int tournament_size){
        Individual parent1 = tournament_selection(population, tournament_size);
        Individual parent2 = tournament_selection(population, tournament_size);
        
        int split_point = parent1.gray_code.length() / 2;

        string child1 = parent1.gray_code.substr(0, split_point) + parent2.gray_code.substr(split_point);
        string child2 = parent2.gray_code.substr(0, split_point) + parent1.gray_code.substr(split_point);

        return {Individual(child1), Individual(child2)};
    }

    static Individual tournament_selection(vector<Individual> population, int tournament_size){
        uniform_int_distribution<> dis(0, population.size()-1);
        vector<Individual> tournament;
    
        for (int i = 0; i < tournament_size; i++) {
            int random_index = dis(Individual::gen);
            tournament.push_back(population[random_index]);
        }
    
        int min_fitness_score_index = get_min_fitness_score_index(tournament);
        return tournament[min_fitness_score_index];
    }

    static int get_min_fitness_score_index(vector<Individual> population){
        int min_fitness_score_index = 0;
        double min_fitness_score = population[0].penalty_fitness_score;
        for (int i = 1; i < population.size(); i++) {
            if (population[i].penalty_fitness_score < min_fitness_score) {
                min_fitness_score_index = i;
                min_fitness_score = population[i].penalty_fitness_score;
            }
        }
        return min_fitness_score_index;
    }
};

int Population::max_fes = 10000;
int Population::current_fes = 0;

int main() {
    int population_size = 100;
    int tournament_size = 5;
    double mutation_rate = 0.01;


    Population current_population(population_size);
    Population::current_fes = population_size;

    while (Population::current_fes < Population::max_fes) {
        current_population = Population::create_next_generation(
            current_population.population, 
            tournament_size, 
            population_size, 
            mutation_rate
        );
        cout << "Current FES: " << Population::current_fes << endl;
        cout << "Best fitness: " 
             << current_population.population[current_population.min_fitness_score_index].penalty_fitness_score << endl;
    }

    cout << "Algorithm ended! MaxFes reached." << endl;
    cout << "Best solution x: " << current_population.population[current_population.min_fitness_score_index].x 
         << ", y: " << current_population.population[current_population.min_fitness_score_index].y << endl;

    return 0;
}
