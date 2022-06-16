# Sokoban Solver 

Solution by Manish Khilari 

Date: May 2021 

--- 

## Introduction 

Welcome to the Sokoban Solver. 

The solver can be found in the following folder. 

> ai/ai.c 

Solution details and setup instructions can be found below. 

## Solution 

A C solution can be found at the following location. 

> ai/ai.c 

The C language was chosen for time efficiency and performance. 

Developed with Visual Studio Code `1.55.0`. 

## Setup Instructions 

Setup instructions can be found below. 

1. Ensure that the following input files are within the same folder as the solution. These input files are required by both the Scala and Java solutions. 

- > test_maps/test_map1 
- > test_maps/test_map2 
- > test_maps/test_map3 

## Play Map 

Instructions to play a given Sokoban map are below. 

1. Run the following command. 

./sokoban <map> 
./sokoban test_maps/test_map2 

## Solve Map 

Instructions to solve a given Sokoban map are below. 

1. Run the following command. 

./sokoban -s <map> play_solution 
./sokoban -s test_maps/test_map3 play_solution 

2. Wait for the state tree to be generated and searched. 

3. Confirm that the solution is played on the given map. 

4. Confirm that the solution is output to the following location. 

> solution.txt 

## Deadlock and Optimisations 

Deadlock and optimisation details can be found at the following location. 

> Report.md 