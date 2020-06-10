// Created by CDRPico
// 09/06/2020 22:54

#include"inc/InstanceSFLP.h"
#include"inc/GenerateInstanceSFLP.h"
#include"inc/UsefulFunctions.h"


int main (){
    //Read FLP Instance
    const char* fln = "SFLP/cap101.txt";
    ifstream file(fln);

    InstanceSFLP FL;

    FL.read_instance(file);
    FL.compute_varcosts();
    cout << "llega aca" << endl;
    FL.gen_mean_demand();

    size_t scenarios = 10;
    GenerateRandomInstance rand_sflp;    
    FL.stdev_demand = generate_stdev(FL.mean_demand, 0.1, 0.3);
    rand_sflp.NormalDistribution(FL, FL.mean_demand, scenarios, FL.stdev_demand);

    for (size_t j = 0; j < FL.nClients; j++){
        for (size_t s = 0; s < scenarios; s++){
            cout << "Demand of client " << (j+1) << " on scenario " << (s+1) << " is " << FL.stoch_param[j][s] << endl;
        }
    }

    return 0;   
}
