// Created by CDRPico
// 01/10/2020 19:23

#pragma once

#ifndef SMPS_ELECPLAN_H
#define SMPS_ELECPLAN_H

#define _CRT_SECURE_NO_WARNINGS


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
		vector<string> stoch_constr;
		vector<vector<double>> indep_rhs_dist;
		vector<vector<double>> marginal_prob;
		vector<vector<double>> cum_marg_prob;
        vector<vector<double>> stoch_param;
        size_t nScenarios;
        vector<double> probability;
        
        //Solutions
        vector<double> x_bar;
        vector<double> y_bar;

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

		void cummalitve_prob();

		//to compute expected demands
		vector<double> expected_dem;
		void compute_expec_dem();

		//Generate origins and destinations based on the existent arcs
		void GenOrgDest();
		vector<size_t> origins;
		vector<size_t> destinations;
		vector<size_t> terminals;

		//Generate random instances
		//rows stand for random constraints
		//columns stand for the scenarios that will be generated
		vector<vector<double>> rnd_ins;
		void generate_instances(size_t &n_scen);

		//wirte a file with instances generated
		void write_st(string &name);
		void read_st(ifstream &file);
};


#endif // SMPS_ELECPLAN_H