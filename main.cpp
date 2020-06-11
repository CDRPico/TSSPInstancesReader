// Created by CDRPico
// 09/06/2020 22:54

#include"inc/InstanceSFLP.h"
#include"inc/GenerateInstanceSFLP.h"
#include"inc/UsefulFunctions.h"
#include<math.h>


int main (){
    //Read FLP Instance
    string init_instances[] = {"SFLP/cap101.txt",
                            "SFLP/cap102.txt",
                            "SFLP/cap103.txt",
                            "SFLP/cap104.txt",
                            "SFLP/cap111.txt",
                            "SFLP/cap112.txt",
                            "SFLP/cap113.txt",
                            "SFLP/cap114.txt",
                            "SFLP/cap121.txt",
                            "SFLP/cap122.txt",
                            "SFLP/cap123.txt",
                            "SFLP/cap124.txt",
                            "SFLP/cap131.txt",
                            "SFLP/cap132.txt",
                            "SFLP/cap133.txt",
                            "SFLP/cap134.txt"};
    vector<string> instances (init_instances, init_instances + sizeof(init_instances) / sizeof(string));
    for (size_t m = 0; m < instances.size(); m++){
        const char* fln = instances[m].c_str();
        ifstream file(fln);

        InstanceSFLP FL;

        FL.read_instance(file);
        FL.compute_varcosts();
        FL.gen_mean_demand();

        //size_t scenarios = 10;

        vector<double> devs;
        for(size_t i = 0; i < 3; i++){
            devs.push_back((i+1)*0.1);
        }

        size_t ss[] = {250, 500, 1500, 10000};
        vector<size_t> scenarios (ss, ss + sizeof(ss) / sizeof(size_t));

        for (size_t i = 0; i < devs.size(); i++){
            for (size_t k = 0; k < scenarios.size(); k++){
                GenerateRandomInstance rand_sflp;    
                FL.stdev_demand = generate_stdev(FL.mean_demand, 0.3);
                rand_sflp.NormalDistribution(FL, FL.mean_demand, scenarios[k], FL.stdev_demand);
                string st = to_string_with_precision(devs[i], 2);
                string name = instances[m] + "_" + to_string(FL.nFacilities) + "_" + to_string(FL.nClients) + "_" 
                                + st + "_" + to_string(scenarios[k]) + ".txt";
                FL.write_stoch(scenarios[k], name);
            }
        }
    }                            
    
    /*for (size_t j = 0; j < FL.nClients; j++){
        for (size_t s = 0; s < scenarios; s++){
            cout << "Demand of client " << (j+1) << " on scenario " << (s+1) << " is " << FL.stoch_param[j][s] << endl;
        }
    }*/
    

    return 0;   
}
