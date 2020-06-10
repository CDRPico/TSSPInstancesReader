// Created by CDRPico
// 09/06/2020 21:38

#pragma once

#ifndef INSTANCESFLP_H
#define INSTANCESFLP_H

using namespace std;
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

class InstanceSFLP {
    public:
        
        // Sets size
        size_t nFacilities = 0;
        size_t nClients = 0;

        // Deterministic data
        vector<double> fixed_costs;
        vector<vector<double>> dist_costs;
        vector<double> facil_capacities;
        vector<double> demand;

        //Stochastic entities
        vector<double> mean_demand;
        vector<double> stdev_demand;
        vector<vector<double>> stoch_demand;
        
        //Solutions
        vector<double> x_bar;
        vector<vector<double>> y_bar;

        InstanceSFLP(){};    

        //Given the file containing the info, we read the data
        void read_instance(ifstream &file);

        //Since the instance gives the total cost to assign demand to a certain facility
        //We recompute the values in such a way that we get variable costs per unit of demand assigned
        void compute_varcosts();
};

#endif // INSTANCESFLP_H