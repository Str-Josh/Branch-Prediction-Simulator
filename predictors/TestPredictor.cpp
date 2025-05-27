#include "TestPredictor.hpp"
#include "PredictorBase.hpp"

TestPredictor::TestPredictor(size_t size) : tableSize(size) { }

bool TestPredictor::Predict(uint32_t programCounter) {
    return table[programCounter % tableSize];  // Defaults to false if not present.
}

void TestPredictor::Update(uint32_t programCounter, bool takenStatusActual) {
    table[programCounter % tableSize] = takenStatusActual;
}
