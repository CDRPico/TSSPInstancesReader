// Created by CDRPico
// 09/06/2020 21:30

#include<random>
#include<vector>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

#pragma once

#ifndef GENERATEINSTANCESSFLP_H
#define GENERATEINSTANCESSFLP_H

class GenerateRandomInstance {

    public:
        GenerateRandomInstance(){};

        template<typename T>
        void NormalDistribution(T &Instance, vector<double> &mean, const size_t &scenarios, vector<double> stdev);

};

#endif // GENERATEINSTANCESSFLP_H