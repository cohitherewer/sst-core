// Copyright 2009-2019 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2019, NTESS
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef _H_SST_CORE_RNG_EXP
#define _H_SST_CORE_RNG_EXP

#include "math.h"

#include "distrib.h"
#include "mersenne.h"

using namespace SST::RNG;

namespace SST {
namespace RNG {

/**
    \class SSTExponentialDistribution expon.h "sst/core/rng/expon.h"

    Creates an exponential distribution for use within SST. This distribution is the same across
    platforms and compilers.
*/
class SSTExponentialDistribution : public SSTRandomDistribution {

    public:
        /**
            Creates an exponential distribution with a specific lambda
            \param mn The lambda of the exponential distribution
        */
    SSTExponentialDistribution(const double mn)  :
    SSTRandomDistribution() {
        
        lambda = mn;
        baseDistrib = new MersenneRNG();
        deleteDistrib = true;
    }

        /**
            Creates an exponential distribution with a specific lambda and a base random number generator
            \param mn The lambda of the exponential distribution
            \param baseDist The base random number generator to take the distribution from.
        */
    SSTExponentialDistribution(const double mn, SSTRandom* baseDist)  :
    SSTRandomDistribution() {
        
        lambda = mn;
        baseDistrib = baseDist;
        deleteDistrib = false;
    }

        /**
            Destroys the exponential distribution
        */
    ~SSTExponentialDistribution() {
        if(deleteDistrib) {
            delete baseDistrib;
        }
    }

        /**
            Gets the next (random) double value in the distribution
            \return The next random double from the distribution
        */
    double getNextDouble()  {
        const double next = baseDistrib->nextUniform();
        return log(1 - next) / ( -1 * lambda );
    }

        /**
            Gets the lambda with which the distribution was created
            \return The lambda which the user created the distribution with
        */
    double getLambda()  {
        return lambda;
    }
    

    protected:
        /**
            Sets the lambda of the exponential distribution.
        */
        double lambda;
        /**
            Sets the base random number generator for the distribution.
        */
        SSTRandom* baseDistrib;

        /**
            Controls whether the base distribution should be deleted when this class is destructed.
        */
        bool deleteDistrib;

};

}
}

#endif
