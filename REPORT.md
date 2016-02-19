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
The MDF graphs are organized inside the GraphRepository class inside an `unordered_map` by a name and added by the method `add(string name, shared_ptr<Graph> g)`. The repository is access by the library in read only and it doent include any runtime structure. The graph class have an id and all the data structure to manage a MDF graph such as:

- `std::vector<Statement> _ist`, vector of istruction
- `std::unordered_map<int, std::vector<int>> _token_to_ist`, used to map a token to the istruction that use it as input

The Statement class rapprensent a MDF intruction and define a set of new type:
- t_in, aka. std::vector<std::shared_ptr<Token>>, rappresent a vector of input token
- t_out, aka. std::shared_ptr<Token>, it is an output token
- t_type_in std::unordered_set<int>, a set of input token type
- t_type_out, aka. aka. `int`, an ouput type
- fun, aka. `std::function<t_out(t_in)>`, which is a function to be executed

More in detail in the staament struct the followiinf member are present:
- fun f, which is the function to be executed
- t_type_in in, the input type token required to the statement
- t_type_out out, the output type of the function



## Interpreter


## ThreadPool


# User Guide


# Experiments