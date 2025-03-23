#include <iostream>
#include <random>
#include <bitset>
#include <cmath>

using namespace std;

mt19937 Individual::gen(random_device{}());

class Individual {
public:
    double x,y;
    string gray_code;
    static mt19937 gen;

    Individual(){
        this->x = this->get_random_number(-10,10);
        this->y = this->get_random_number(-10,10);
        this->gray_code = this->double2gray(this->x) + this->double2gray(this->y);
    }
    Individual(double x, double y){
        this->x = x;
        this->y = y;
        this->gray_code = this->double2gray(this->x) + this->double2gray(this->y);
    }
    Individual(string gray_code){
        string gray1 = gray_code.substr(0,9);
        string gray2 = gray_code.substr(9,9);
        }

static double get_random_number(int min, int max){
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
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

static string binary2double(string binary){
    string binary_part1 = binary.substr(0,1);
    string binary_part2 = binary.substr(1,4);
    string binary_part3 = binary.substr(5,9);}

};


int main() {

    return 0;
}