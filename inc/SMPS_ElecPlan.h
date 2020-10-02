// Created by CDRPico
// 01/10/2020 19:23

#pragma once

#ifndef SMPS_ELECPLAN_H
#define SMPS_ELECPLAN_H


using namespace std;
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

class Inst_ElecPlan {
    public:
        
        // Sets size
        size_t nTerminals = 0;
        size_t nClients = 0;
        size_t nResources = 0;

        // Deterministic data
        vector<double> fixed_costs;
        vector<vector<double>> dist_costs;
        vector<double> resources_avail;
        vector<vector<double>> resources_coef;
        vector<double> demand;

        //First stage data
        string ffirst_row;
        string ffirst_col;
        vector<string> first_st_var;
        vector<string> first_st_const;
        vector<string> first_st_constsense;
        vector<double> first_st_rhs;
        vector<vector<double>> first_st_coefs;
        vector<double> first_st_cost;
        
        //First stage data
        string fsecond_row;
        string fsecond_col;
        vector<string> second_st_var;
        vector<string> second_st_const;
        vector<string> second_st_constsense;
        vector<double> second_st_rhs;
        vector<vector<double>> second_st_coefs;
        vector<double> second_st_cost;
        

        //Stochastic entities
        vector<vector<double>> stoch_param;
        size_t nScenarios;
        vector<double> probability;
        
        //Solutions
        vector<double> x_bar;
        vector<vector<double>> y_bar;

        Inst_ElecPlan(){};    

        //Given the file containing the info, we read the data
        void read_core(ifstream &file);

        //Given the temporality we read variables and constraints belonging to each stage
        void read_time(ifstream &file);

        //Read stoch SMPS file and
        //The data is stored in stoch_param (it is used either to read or generate instance)
        void read_stoch(ifstream &file);

        //Generate scenarios after reading independent distributions
        void generate_scenarios();

        //Read name of constraints (rows)
        void read_rows(ifstream &file, string &what_to_read, size_t &cline);

        //Read name of variables and their coefficients in OF and constraints
        void read_cols_coefs(ifstream &file, string &what_to_read, size_t &cline);

        //Read RHS
        void read_rhs(ifstream &file, string &what_to_read, size_t &cline);
};


#endif // SMPS_ELECPLAN_H