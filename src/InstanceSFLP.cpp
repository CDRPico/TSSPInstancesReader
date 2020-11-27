// Created by CDRPico
// 09/06/2020 22:13

#include"../inc/InstanceSFLP.h"
#include"../inc/UsefulFunctions.h"
#define _CRT_SECURE_NO_WARNINGS

void InstanceSFLP::read_instance(ifstream &file){
    string line;
    
    //First line contains number of facilities and customers
    getline(file, line);
    vector<string> row_values;
    split(line, row_values, ' ');
    //Casting values, %zu stands for size_t
    sscanf(row_values[0].c_str(), "%zu", &nFacilities);
    sscanf(row_values[1].c_str(), "%zu", &nClients);
    row_values.clear();

    //We check correctness by printing number of facilites and clients
    cout << "The number of clientes to be served is " << nClients << " and the number of potential facilities " << nFacilities << endl;

    //Resizing elements
    fixed_costs.resize(nFacilities);
    dist_costs.resize(nFacilities);
    facil_capacities.resize(nFacilities);
    demand.resize(nClients);

    //Fixed costs and facilities capacity
    for (size_t i = 0; i < nFacilities; i++){
        getline(file, line);
        split(line, row_values, ' ');
        facil_capacities[i] = atof(row_values[0].c_str());
        fixed_costs[i] = atof(row_values[1].c_str());
        row_values.clear();
        dist_costs[i].resize(nClients);
    }

    //Demands and distributions costs
    for (size_t j = 0; j <nClients; j++){
        getline(file, line);
        split(line, row_values, ' ');
        demand[j] = atof(row_values[0].c_str());
        row_values.clear();
        size_t i = 0;
        while (i < nFacilities){
            getline(file,line);
            split(line, row_values, ' ');
            for (size_t mv = 0; mv<row_values.size()-1; mv++){
                dist_costs[i][j] = atof(row_values[mv].c_str());
                i++;
            }
        }
    }

}

void InstanceSFLP::compute_varcosts(){
    //The original instance bring the total cost when a client is assigned to a certain facility
    //This function computes the unitary cost
    for (size_t i = 0; i < nFacilities; i++){
        for (size_t j = 0; j < nClients; j++){
            dist_costs[i][j] = dist_costs[i][j]/demand[j];
        }
    }
}

void InstanceSFLP::gen_mean_demand(){
    mean_demand.resize(nClients);
    for (size_t j = 0; j < nClients; j++){
        mean_demand[j] = demand[j];
    }
}

void InstanceSFLP::write_stoch(size_t &scenarios, string &name){
    double prob = 1.0/scenarios;
    string head = to_string(scenarios) + "\n";
    ofstream file;
    file.open (name);
    file << head;
    for (size_t s = 0; s < scenarios; s++){
        string scen = to_string(prob);
        for (size_t j = 0; j < nClients; j++){
            scen = scen + " " + to_string(stoch_param[j][s]);            
        }
        scen = scen + "\n";
        file << scen;
    }
    file.close();
}

//This functions reads stochastic instance already generated (stoch demand)
//The data is stored in stoch_param (it is used either to read or generate instance)
void InstanceSFLP::read_stoch_data(ifstream &file){
    string line;
    stoch_param.clear();

    //The first line contains the number of scenarios
    getline(file, line);
    vector<string> row_values;
    split(line, row_values, ' ');
    //Casting values, %zu stands for size_t
    sscanf(row_values[0].c_str(), "%zu", &nScenarios);
    row_values.clear();

    stoch_param.resize(nClients);
    for (size_t j = 0; j < nClients; j++){
        stoch_param[j].resize(nScenarios);
    }

    probability.resize(nScenarios);
    for (size_t s = 0; s < nScenarios; s++){
        getline(file, line);
        split(line, row_values, ' ');
        probability[s] = atof(row_values[0].c_str());
        for (size_t j = 0; j < nClients; j++){
            stoch_param[j][s] = atof(row_values[j+1].c_str());
        }
        row_values.clear();
    }
}