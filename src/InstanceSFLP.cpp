// Created by CDRPico
// 09/06/2020 22:13

#include"../inc/InstanceSFLP.h"
#include"../inc/UsefulFunctions.h"

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
        cout << "the demand of client " << (j+1) << " is " << demand[j] << endl << endl;
        row_values.clear();
        size_t i = 0;
        while (i < nFacilities){
            getline(file,line);
            split(line, row_values, ' ');
            for (size_t mv = 0; mv<row_values.size()-1; mv++){
                dist_costs[i][j] = atof(row_values[mv].c_str());
                cout << "Distribution cost from facility " << (i+1) << " to client " << (j+1) << " is " << dist_costs[i][j] << endl;
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