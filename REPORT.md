% SPM Project: Micro Macro Data Flow
% Luca Rinaldi
% 12 January 2016

# Introduction
The project is a micro-MDF library to execute MDF graph with a defined number of threads.

# Main Structure
The project is constituted of three principal parts:

- `Graph Repository`, where the MDF graph are stored
- `InterpreterFactory`, able to start and management the evaluation of the MDF graphs
- `ThreadPool`, the actual core of the parallel computation, whitch manage the task on a fixed number of threads

## Graph Repository
The MDF graphs are organized inside the GraphRepository class inside an `unordered_map` by a name and added by the method `add(string name, shared_ptr<Graph> g)`. The graph class inside have a 

## Interpreter


## ThreadPool


# User Guide


# Experiments