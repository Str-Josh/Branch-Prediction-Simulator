#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cstdint>

#include "BranchPredictionSimulator.hpp"
#include "predictors/PredictorBase.hpp"
#include "predictors/TestPredictor.hpp"


using PredictorFactory = std::unique_ptr<PredictorBase>(*)();

// mapping of the available predictors
std::unordered_map<std::string, PredictorFactory> predictorRegistry = {
    { "test", []() -> std::unique_ptr<PredictorBase> { return std::make_unique<TestPredictor>(); } },
    { "1-bit", []() -> std::unique_ptr<PredictorBase> { return std::make_unique<TestPredictor>(); } },
};


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Expected 2 arguments, [bpalg] and [predsize]. Using single argument as [bpalg] and defaulting [predsize] to 2.\n";
        return 0;
    }

    std::string bpalg;
    int predsize = 0;
    std::string instructionTraceFile;
    for (int argIdx = 1; argIdx < argc; ++argIdx) {
        std::string arg = argv[argIdx];

        if (arg == "--bpalg" && argIdx + 1 < argc) { bpalg = argv[++argIdx]; }
        else if (arg == "--size" && argIdx + 1 < argc) {
            predsize = std::stoi(argv[++argIdx]);
            if (predsize <= 0 || (predsize & (predsize - 1)) != 0) {
                std::cerr << "Unexpected [predsize] value. Using default [predsize] as 2.\n";
                return 0;
            }
        }
        else if (arg == "--trace" && argIdx + 1 < argc) { instructionTraceFile = argv[++argIdx]; }
        else { std::cerr << "An unexpected error has occurred.\n"; }
    }
    // std::cout << bpalg << "\n" << predsize << "\n" << instructionTraceFile << "\n";

    auto _iterator = predictorRegistry.find(bpalg);
    if (_iterator == predictorRegistry.end()) {
        std::cerr << "The listed branch prediction algorithm was not recognized.\n";
        return 0;
    }
    std::unique_ptr<PredictorBase> bpAlgorithm = _iterator->second();
    PredictorBase* predictorStrategy = bpAlgorithm.get();
    PredictionSimulator simulator = PredictionSimulator(*predictorStrategy);

    simulator.LoadInstructionTrace(instructionTraceFile);
    simulator.RunSimulation();
    simulator.DisplaySimulationResults();


    std::cout << "Program completed successfully.\n>>  ";
    std::cin.get();
    return 1;
}