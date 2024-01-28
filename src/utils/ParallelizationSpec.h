//
// Created by rodff on 14.01.24.
//

#ifndef PSEMOLDYN_GROUPD_PARALLELIZATIONSPEC_H
#define PSEMOLDYN_GROUPD_PARALLELIZATIONSPEC_H

#include <stdexcept>

enum ParallelizationType {
    Subdomain,
    Cellwise,
    None
};

enum SchedulerType {
    Static,
    Dynamic,
    Guided
};

class ParallelizationSpec {
private:
    enum ParallelizationType type;
    int numThreads;
    std::array<int,3> subdomain;
    int chunksize;

public:
    ParallelizationSpec(enum ParallelizationType type, int numThreads, int chunksize, std::array<int,3> subdomain) : type(type), numThreads(numThreads), subdomain(subdomain), chunksize(chunksize) {}
    ParallelizationSpec() : type(None), numThreads(1), subdomain({1,1,1}), chunksize(1) {}

    /** Getters **/

    enum ParallelizationType getType() const {
        return type;
    }

    int getNumThreads() const {
        return numThreads;
    }

    std::array<int,3> getSubdomain() const {
        return subdomain;
    }

    int getChunksize() const {
        return chunksize;
    }

    /** Setters **/

    void setType(enum ParallelizationType type_val) {
        this->type = type_val;
    }

    void setNumThreads(int numThreads_val) {
        this->numThreads = numThreads_val;
    }

    void setSubdomain(std::array<int,3> subdomain_val) {
        this->subdomain = subdomain_val;
    }

    void setChunksize(int chunksize_val) {
        this->chunksize = chunksize_val;
    }

    static enum ParallelizationType getParallelizationTypeFromStr(const std::string& str) {
        if (str == "subdomain") {
            return Subdomain;
        } else if (str == "cellwise") {
            return Cellwise;
        } else if (str == "none") {
            return None;
        } else {
            throw std::invalid_argument("Invalid parallelization type. Received " + str + " but expected subdomain, cellwise or none.");
        }
    }

    static enum SchedulerType getSchedulerTypeFromStr(const std::string& str) {
        if (str == "static") {
            return Static;
        } else if (str == "dynamic") {
            return Dynamic;
        } else if (str == "guided") {
            return Guided;
        } else {
            throw std::invalid_argument("Invalid scheduler type. Received " + str + " but expected static, dynamic or guided.");
        }
    }
};

#endif //PSEMOLDYN_GROUPD_PARALLELIZATIONSPEC_H
