// Created by CDRPico
// 09/06/2020 22:18

using namespace std;
#include<vector>
#include<iostream>
#include<random>
#include<sstream>

//Takes a vector which contains a string and split it based on char ch definition
//It returns a vector of strings where every position is a segment between two ch
size_t split(const string &txt, vector<string> &strs, char ch);

//This function generates an standard deviation for a normal distribution, based on a unifor pdf
//lower and upper limits are defined by the user [0,1] with respect to the mean
vector<double> generate_rand_stdev(vector<double> &mean, const double &ll, const double &ul);

//This function generates an standard deviation for a normal distribution, based on a given factor
//regarding the mean of the distribution
vector<double> generate_stdev(vector<double> &mean, double = 0.1);

//Round to string
template <typename T>
string to_string_with_precision(const T a_value, int = 2);

//Find the index of a string into a vector
size_t find_elem(vector<string> &lookhere1, vector<string> &lookhere2, string &lookfor);