// Created by CDRPico
// 09/06/2020 22:13

#include"../inc/SMPS_ElecPlan.h"
#include"../inc/UsefulFunctions.h"

#define _CRT_SECURE_NO_WARNINGS

void Inst_ElecPlan::read_time(ifstream &file) {
    string line;

    //First two lines contains useless information (when TSSP)
    getline(file, line);
	getline(file, line);
    //Third line contains the beginning of rows and columns for first stage
	getline(file, line);
    vector<string> row_values;
    split(line, row_values, ' ');
    //Casting values, %zu stands for size_t, %s stands for string
	ffirst_col = row_values[0];
	ffirst_row = row_values[1];
    //sscanf(row_values[0].c_str(), "%s", &ffirst_col);
    //sscanf(row_values[1].c_str(), "%s", &ffirst_row);
    row_values.clear();

    //Fourth line to know col and row where second stage starts
    getline(file, line);
    split(line, row_values, ' ');
	fsecond_col = row_values[0];
	fsecond_row = row_values[1];
    //sscanf(row_values[0].c_str(), "%s", &fsecond_col);
    //sscanf(row_values[1].c_str(), "%s", &fsecond_row);
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
	what_to_read = row_values[0];
    //sscanf(row_values[0].c_str(), "%s", &what_to_read);

    if (what_to_read == "ROWS") {
        read_rows(file, what_to_read, current_line);
        //goto continue_reading;
    }
	if (what_to_read == "COLUMNS") {
        read_cols_coefs(file, what_to_read, current_line);
        //goto continue_reading;
    }
	if (what_to_read == "RHS") {
        read_rhs(file, what_to_read, current_line);
        //goto continue_reading;
    }
	if (what_to_read == "BOUNDS") {
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
	second_st_var.push_back(fsecond_col);

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
        } else if (stage == 2 && second_st_var.back() == row_values[0]) {
            size_t const_index = find_elem(first_st_const, second_st_const, row_values[1]);
            second_st_coefs.back()[const_index] = atof(row_values[2].c_str());
        } else if (stage == 2 && second_st_var.back() != row_values[0]) {
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


void Inst_ElecPlan::read_stoch(ifstream &file) {
	//throw away the first two lines
	string line;
	getline(file, line);
	getline(file, line);

	//Resize indep demands
	indep_rhs_dist.resize(1);
	indep_rhs_dist[0].resize(1);
	stoch_constr.resize(1);
	marginal_prob.resize(1);
	marginal_prob[0].resize(1);

	//we start reading at thrid line
	getline(file, line);
	vector<string> row_values;
	split(line, row_values, ' ');
	string what_to_read = row_values[0];

	stoch_constr[0] = row_values[1];
	indep_rhs_dist[0][0] = atof(row_values[2].c_str());
	marginal_prob[0][0] = atof(row_values[3].c_str());

	size_t cont = 0;

	while (what_to_read == "RHS") {
		
		if (stoch_constr.back() == row_values[1] && cont > 0) {
			indep_rhs_dist.back().push_back(atof(row_values[2].c_str()));
			marginal_prob.back().push_back(atof(row_values[3].c_str()));
		}
		else if (stoch_constr.back() != row_values[1] && cont > 0) {
			stoch_constr.push_back(row_values[1]);
			indep_rhs_dist.push_back(vector<double>({ atof(row_values[2].c_str()) }));
			marginal_prob.push_back(vector<double>({ atof(row_values[3].c_str()) }));
		}
		cont += 1;
		row_values.clear();

		getline(file, line);
		split(line, row_values, ' ');
		what_to_read = row_values[0];
	}
}


void Inst_ElecPlan::cummalitve_prob() {
	cum_marg_prob.resize(marginal_prob.size());
	for (size_t i = 0; i < marginal_prob.size(); i++) {
		double co = 0.0;
		for (size_t j = 0; j < marginal_prob[i].size(); j++) {
			cum_marg_prob[i].resize(marginal_prob[i].size());
			co += marginal_prob[i][j];
			cum_marg_prob[i][j] = co;
		}
	}
}

//Generate random instances
//rows stand for random constraints
//columns stand for the scenarios that will be generated
void Inst_ElecPlan::generate_instances(size_t &n_scen) {
	rnd_ins.resize(stoch_constr.size());
	//seed to generate the rand numbers
	default_random_engine generator;
	uniform_real_distribution<double> pdf(0.0, 1.0);

	for (size_t i = 0; i < stoch_constr.size(); i++) {
		rnd_ins[i].resize(n_scen);
		for (size_t j = 0; j < n_scen; j++) {
			double rnd_n = pdf(generator);
			double dem_scen_cl = -1.0;
			if (rnd_n <= cum_marg_prob[i][0]) {
				dem_scen_cl = indep_rhs_dist[i][0];
			}
			else {
				for (size_t k = 1; k < cum_marg_prob[i].size(); k++) {
					if (rnd_n > cum_marg_prob[i][k - 1] && rnd_n <= cum_marg_prob[i][k]) {
						dem_scen_cl = indep_rhs_dist[i][k];
						break;
					}
				}
			}
			rnd_ins[i][j] = dem_scen_cl;
		}
	}
}