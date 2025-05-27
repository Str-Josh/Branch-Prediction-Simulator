#ifndef BRANCH_PREDICTOR_BASE_H
#define BRANCH_PREDICTOR_BASE_H

#include <cstdint>


class PredictorBase {
    public:
        virtual bool Predict(uint32_t programCounter) = 0;
        virtual void Update(uint32_t programCounter, bool takenStatusActual) = 0;
        virtual ~PredictorBase() = default;
};

#endif