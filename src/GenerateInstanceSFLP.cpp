// Created by CDRPico
// 09/06/2020 22:13

#include"../inc/GenerateInstanceSFLP.h"
#include"../inc/InstanceSFLP.h"
#include"../inc/UsefulFunctions.h"

template<typename T>
void GenerateRandomInstance::NormalDistribution(T &Instance, vector<double> &mean, const size_t &scenarios, vector<double> stdev){
    // This function takes arguments from normal distribution of certain parameters and 
    // a given number of scenarios to create a sample 
    // Independency is assumed

    Instance.stoch_param.resize(mean.size());
    for (size_t j = 0; j < mean.size(); j++){
        Instance.stoch_param[j].resize(scenarios);
        default_random_engine generator;
        normal_distribution<double> pdf(mean[j],stdev[j]);
        for (size_t s = 0; s < scenarios; s++){
            double rand_param = pdf(generator);
            if (rand_param >= 0.0){
                Instance.stoch_param[j][s] = rand_param;
            } else {
                Instance.stoch_param[j][s] = 0.0;
            }    
        }
    }
}
template void GenerateRandomInstance::NormalDistribution(InstanceSFLP &Instance, vector<double> &mean, const size_t &scenarios, vector<double> stdev);