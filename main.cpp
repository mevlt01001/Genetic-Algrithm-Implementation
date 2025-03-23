#include <iostream>
#include <random>
#include <bitset>
#include <cmath>

using namespace std;

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
        this->gray_code = gray_code;
        this->x = this->gray2double(gray_code.substr(0,9));
        this->y = this->gray2double(gray_code.substr(9,9));    
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


int main() {
    double org_x = -3.75;
    double org_y = 2.25;

    Individual ind = Individual(org_x, org_y);
    cout << ind.x << " " << ind.y << endl;
    cout << ind.gray_code << endl;

    Individual org = Individual(ind.gray_code);
    cout << org.x << " " << org.y << endl;
}