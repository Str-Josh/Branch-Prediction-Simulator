# Branch Prediction Simulator
System to simulate branch prediction algorithms

## Developed Using
* __C++__

## Getting Started
### Prerequisites
* C++ Compiler (Clang, G++, etc.)

### Installation
1. Clone the repo: <br> `git clone https://github.com/Str-Josh/Financial-Derivatives-Strategy-Backtester.git`
2. Change git remote url to avoid accidental pushes to main project
<br>`git remote set-url origin github_username/repo_name`
<br>`git remote -v`
3. Compile the following scripts:<br>
`g++ -c BranchPredictionSimulator.cpp`
`g++ -c TestPredictor.cpp`
`g++ -c main.cpp`
4. Link the object files using the following:<br>
`g++ main.o BranchPredictionSimulator.o TestPredictor.o -o BranchPrediction`
5. Execute the program. For example:<br>`BranchPrediction --bpalg 1-bit --trace instruction_traces/trace1.txt`

Lessons Learned:
* Implementation of 1-bit branch prediction algorithm
* CPU Instruction Execution Cycles
* File Management in C++
* Implementing command line arguments in C++
* Usage of smart pointers

Future Additions/Improvements:
* Modify the code to be able to operate on a microcontroller and to take actual instruction traces from the CPU
