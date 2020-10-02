// Created by CDRPico
// 09/06/2020 22:13

#include"../inc/SMPS_ElecPlan.h"
#include"../inc/UsefulFunctions.h"

#define _CRT_SECURE_NO_WARNINGS

void Inst_ElecPlan::read_time(ifstream &file) {
    string line;

    //First two lines contains useless information (when TSSP)
    getline(file, line);
    //Third line contains the beginning of rows and columns for first stage
    vector<string> row_values;
    split(line, row_values, ' ');
    //Casting values, %zu stands for size_t, %s stands for string
    sscanf(row_values[0].c_str(), "%s", &ffirst_col);
    sscanf(row_values[1].c_str(), "%s", &ffirst_row);
    row_values.clear();

    //Fourth line to know col and row where second stage starts
    getline(file, line);
    split(line, row_values, ' ');
    sscanf(row_values[0].c_str(), "%s", &fsecond_col);
    sscanf(row_values[1].c_str(), "%s", &fsecond_row);
    row_values.clear();
}

void Inst_ElecPlan::read_core(ifstream &file){
    string line;
    size_t current_line = 1;

    //First line does not contain important information
    getline(file, line);
    current_line += 1;
    //Second line to check what will be read
    vector<string> row_values;

//continue_reading:
    row_values.clear();
    getline(file, line);
    current_line += 1;
    split(line, row_values, ' ');
    string what_to_read;
    sscanf(row_values[0].c_str(), "%s", &what_to_read);

    if (what_to_read == "ROWS") {
        read_rows(file, what_to_read, current_line);
        //goto continue_reading;
    } else if (what_to_read == "COLUMNS") {
        read_cols_coefs(file, what_to_read, current_line);
        //goto continue_reading;
    } else if (what_to_read == "RHS") {
        read_rhs(file, what_to_read, current_line);
        //goto continue_reading;
    } else if (what_to_read == "BOUNDS") {
        size_t a = 1;
        //TODO: read_bounds for variables
        //goto continue_reading;
    }


}

void Inst_ElecPlan::read_rows(ifstream &file, string &what_to_read, size_t &cline) {
    string line;
    getline(file, line);
    cline += 1;
    vector<string> row_values;
    split(line, row_values, ' ');

    what_to_read = row_values[0];
    size_t cont1 = 0;
    size_t cont2 = 0;
    size_t stage = 1;

    while (what_to_read != "COLUMNS" && what_to_read != "RHS" && what_to_read != "BOUNDS") {
        if (row_values[1] == fsecond_row) { 
            stage = 2;
        }

        if (stage == 1) {
            first_st_const.push_back(row_values[1]);
            first_st_constsense.push_back(row_values[0]);
            cont1 += 1;
        } else {
            second_st_const.push_back(row_values[1]);
            second_st_constsense.push_back(row_values[0]);
            cont2 += 1;
        }

        row_values.clear();
        getline(file, line);
        cline += 1;
        split(line, row_values, ' ');
        what_to_read = row_values[0];
    }

}

void Inst_ElecPlan::read_cols_coefs(ifstream &file, string &what_to_read, size_t &cline) {
    //Read teh first line after COLUMNS is found
    string prev_line = what_to_read;
    string line;
    getline(file, line);
    cline += 1;
    vector<string> row_values;

    //First variable is added
    split(line, row_values, ' ');
    first_st_var.push_back(row_values[0]);

    what_to_read = row_values[0];

    size_t stage = 1;
    size_t cont1 = 0;
    size_t cont2 = 0;
    size_t constfst = first_st_const.size();
    size_t constsst = second_st_const.size();
    //For the sake of simplicity reading, vars will be in rows and constraints in columns
    first_st_coefs.push_back(vector<double>(constfst + constsst, 0.0));
    second_st_coefs.push_back(vector<double>(constfst + constsst, 0.0));


    while (what_to_read != "ROWS" && what_to_read != "RHS" && what_to_read != "BOUNDS") {
        if (row_values[0] == fsecond_col) { 
            stage = 2;
        }

        if (stage == 1 && first_st_var.back() == row_values[0]) {
            size_t const_index = find_elem(first_st_const, second_st_const, row_values[1]);
            first_st_coefs.back()[const_index] = atof(row_values[2].c_str());
        } else if (stage == 1 && first_st_var.back() != row_values[0]) {
            first_st_var.push_back(row_values[0]);
            first_st_coefs.push_back(vector<double>(constfst + constsst, 0.0));
            size_t const_index = find_elem(first_st_const, second_st_const, row_values[1]);
            first_st_coefs.back()[const_index] = atof(row_values[2].c_str());
        } else if (stage == 2 && first_st_var.back() == row_values[0]) {
            size_t const_index = find_elem(first_st_const, second_st_const, row_values[1]);
            second_st_coefs.back()[const_index] = atof(row_values[2].c_str());
        } else if (stage == 2 && first_st_var.back() != row_values[0]) {
            second_st_var.push_back(row_values[0]);
            second_st_coefs.push_back(vector<double>(constfst + constsst, 0.0));
            size_t const_index = find_elem(first_st_const, second_st_const, row_values[1]);
            second_st_coefs.back()[const_index] = atof(row_values[2].c_str());
        }

        row_values.clear();
        getline(file, line);
        cline += 1;
        split(line, row_values, ' ');
        what_to_read = row_values[0];
    }
}

void Inst_ElecPlan::read_rhs(ifstream &file, string &what_to_read, size_t &cline) {
    //Resize vectors for rhs
    first_st_rhs.resize(first_st_const.size());
    second_st_rhs.resize(second_st_const.size());

    string line;
    getline(file, line);
    cline += 1;
    vector<string> row_values;
    split(line, row_values, ' ');
    what_to_read = row_values[0];
    
    while (what_to_read != "ROWS" && what_to_read != "COLUMNS" && what_to_read != "BOUNDS") {
        
        size_t const_index = find_elem(first_st_const, second_st_const, row_values[1]);
        
        if (const_index < first_st_const.size()) {
            first_st_rhs[const_index] = atof(row_values[2].c_str());
        } else {
            second_st_rhs[const_index - first_st_const.size()] = atof(row_values[2].c_str());
        }

        row_values.clear();
        getline(file, line);
        cline += 1;
        split(line, row_values, ' ');
        what_to_read = row_values[0];
    }
}
