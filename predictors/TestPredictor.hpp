#ifndef TEST_PREDICTOR_H
#define TEST_PREDICTOR_H

#include "PredictorBase.hpp"
#include <unordered_map>


class TestPredictor : public PredictorBase {
    private:
        std::unordered_map<uint32_t, bool> table;
        size_t tableSize;

    public:
        TestPredictor(size_t size = 1024);  // 2^10
        bool Predict(uint32_t programCounter) override;
        void Update(uint32_t programCounter, bool takenStatusActual) override;
};

#endif