#ifndef BRANCH_PREDICTION_SIMULATOR_H
#define BRANCH_PREDICTION_SIMULATOR_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>

#include "predictors/PredictorBase.hpp"


struct Instruction {
    uint32_t programCounter;
    bool taken;
};


class PredictionSimulator {
    private:
        PredictorBase& predictor;
        std::vector<Instruction> branchInstructions;

        int totalBranchesEvaluated = 0;
        int correctBranchPredictions = 0;
    public:
        PredictionSimulator(PredictorBase &predictor);
        void LoadInstructionTrace(std::string instructionTraceFilename);
        void RunSimulation();
        void DisplaySimulationResults();
};

#endif