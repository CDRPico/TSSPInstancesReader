// Created by CDRPico
// 09/06/2020 22:54

#include"inc/InstanceSFLP.h"


int main (){
    //Read FLP Instance
    const char* fln = "SFLP/cap101.txt";
    ifstream file(fln);

    InstanceSFLP FL;

    FL.read_instance(file);
    return 0;   
}
