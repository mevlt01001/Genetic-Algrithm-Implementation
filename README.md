# Genetic Algorithm Optimization with Penalty Function

This repository contains a clear, efficient, and fully functional implementation of a **Genetic Algorithm (GA)** designed to optimize a given mathematical function with constraint handling via a **penalty function approach**.

## Problem Description

The goal is to optimize (minimize) the following objective function:

![image](https://github.com/user-attachments/assets/6214fa8b-d41b-479e-9b00-04f80919e505)

\[
f(x,y) = (x + 2y - 7)^2 + (2x + y - 5)^2
\]

### Constraints:

![image](https://github.com/user-attachments/assets/ed8652d7-0550-4940-aee9-72dbf64b221f)

- \(-10 \leq x \leq 10\)
- \(-10 \leq y \leq 10\)

The algorithm converts this constrained problem into an unconstrained one using a penalty function, making it solvable with standard GA techniques.

## Implementation Details

### Main Components:

- **Encoding:** Real values \((x, y)\) are encoded using **Gray codes**.
- **Selection:** Tournament selection.
- **Crossover:** Single-point crossover applied on Gray-coded chromosomes.
- **Mutation:** Bitwise mutation with a predefined probability.
- **Penalty Function:** Ensures solutions remain within the feasible domain by penalizing violations.

### Algorithm Flow:

1. Initialize random population.
2. Evaluate fitness using the penalty function.
3. Select parents via tournament selection.
4. Generate offspring using crossover.
5. Apply mutation on offspring.
6. Repeat steps 2–5 until the **Maximum Function Evaluations (MaxFes)** criterion is reached.

## Results

The implemented genetic algorithm provides results very close to the known analytical solution:

| Method | Solution \((x,y)\) | Fitness Score |
|--------|--------------------|---------------|
| Analytical solution | \((1, 3)\) | \(0\) |
| GA (Example run) | \((1.0599, 2.949)\) | \(0.0065\) |

## How to Use

### Compile:

```
bash
g++ main.cpp -o genetic_algorithm
```
### Run:
```
./genetic_algorithm
```
### Sample Output:
```
Current FES: 500
Best fitness: 0.113086
...
Current FES: 9900
Best fitness: 0.00650724
Algorithm ended! MaxFes reached.
Best solution x: 1.05991, y: 2.949
```
## Project Structure:
```
.
├── main.cpp          # Main algorithm implementation
├── README.md         # Documentation file
```
## Requirements:
- C++ compiler supporting C++11 or newer.
- **No additional libraries needed.**

**Author:** Mevlüt Başaran
