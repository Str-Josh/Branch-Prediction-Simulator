#include "BranchPredictionSimulator.hpp"

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

PredictionSimulator::PredictionSimulator(PredictorBase &predictor) : predictor(predictor) {}


void PredictionSimulator::LoadInstructionTrace(std::string instructionTraceFilename) {
    // std::ifstream file("instruction_traces/trace1.txt");
    std::ifstream file(instructionTraceFilename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
    }

    std::string content;

    // read from the file
    while (std::getline(file, content)) {
        std::string instruction = content.substr(0, content.find(" "));
        std::string takenStatus = content.substr(content.find(" "), content.length());

        uint32_t instruction_converted = static_cast<uint32_t>(stoul(instruction));
        bool takenStatus_converted = static_cast<bool>(stoi(takenStatus));
        
        Instruction _branchInstruction = { instruction_converted, takenStatus_converted };
        branchInstructions.push_back(_branchInstruction);
    }
    
    file.close();
}


void PredictionSimulator::RunSimulation() {
    for (const auto &[programCounter, actualTakenStatus] : this->branchInstructions) {
        bool prediction = this->predictor.Predict(programCounter);
        if (prediction == actualTakenStatus) {
            this->correctBranchPredictions++;
        }
        this->predictor.Update(programCounter, actualTakenStatus);
        this->totalBranchesEvaluated++;
    }
}

void PredictionSimulator::DisplaySimulationResults() {
    std::cout << "Total Branches Evaluated:  " << this->totalBranchesEvaluated << "\n";
    std::cout << "Correct Branch Predictions:  " << this->correctBranchPredictions << "\n";
    double accuracy = ( static_cast<double>(this->correctBranchPredictions) / static_cast<double>(this->totalBranchesEvaluated) ) * 100.0;
    std::cout << "Overall Accuracy:  " << ( static_cast<double>(this->correctBranchPredictions) / static_cast<double>(this->totalBranchesEvaluated) ) * 100.0 << "%\n";
}