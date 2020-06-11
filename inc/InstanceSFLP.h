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
        vector<vector<double>> stoch_param;
        size_t nScenarios;
        vector<double> probability;
        
        //Solutions
        vector<double> x_bar;
        vector<vector<double>> y_bar;

        InstanceSFLP(){};    

        //Given the file containing the info, we read the data
        void read_instance(ifstream &file);

        //Since the instance gives the total cost to assign demand to a certain facility
        //We recompute the values in such a way that we get variable costs per unit of demand assigned
        void compute_varcosts();

        //Set mean demand, we assume it is equal to the original instance demand
        void gen_mean_demand();

        //Useful to generate a file containing data of a new stochastic instanc generated
        void write_stoch(size_t &scenarios, string &name);

        //This functions reads stochastic instance already generated (stoch demand)
        //The data is stored in stoch_param (it is used either to read or generate instance)
        void read_stoch_data(ifstream &file);
};

#endif // INSTANCESFLP_H