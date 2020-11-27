// Created by CDRPico
// 10/06/2020 01:07

#include"../inc/UsefulFunctions.h"
#include<algorithm>
#define _CRT_SECURE_NO_WARNINGS

//Takes a vector which contains a string and split it based on char ch definition
//It returns a vector of strings where every position is a segment between two ch
size_t split(const string &txt, vector<string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != string::npos) {
		if (!txt.substr(initialPos, pos - initialPos).empty()) {
			strs.push_back(txt.substr(initialPos, pos - initialPos));
		}
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

//This function generates an standard deviation for a normal distribution, based on a unifor pdf
//lower and upper limits are defined by the user [0,1] with respect to the mean
vector<double> generate_rand_stdev(vector<double> &mean, const double &ll, const double &ul){
    vector<double> stdev(mean.size());
    for (size_t i = 0; i < mean.size(); i++){
        default_random_engine generator;
        uniform_real_distribution<double> pdf(mean[i]*ll, mean[i]*ul);
        stdev[i] = pdf(generator);
    }
    return stdev;
}

//This function generates an standard deviation for a normal distribution, based on a given factor
//regarding the mean of the distribution
vector<double> generate_stdev(vector<double> &mean, double factor){
    vector<double> stdev(mean.size());
    for (size_t i = 0; i < mean.size(); i++){
        stdev[i] = mean[i]*factor;
    }
    return stdev;
}


template <typename T>
string to_string_with_precision(const T a_value, int n)
{
    ostringstream out;
    out.precision(n);
    out << fixed << a_value;
    return out.str();
}
template string to_string_with_precision(const double a_value, int n);


size_t find_elem(vector<string> &lookhere1, vector<string> &lookhere2, string &lookfor) {
    size_t index = 0;

    vector<string>::iterator it = find(lookhere1.begin(), lookhere1.end(), lookfor);

    if (it == lookhere1.end()) {
        // If the element is not found on first stage vector, then it belongs to second stage
        index = lookhere1.size();
        it = find(lookhere2.begin(), lookhere2.end(), lookfor);
        index = index + distance(lookhere2.begin(), it);
    } else {
        index = distance(lookhere1.begin(), it);
    }
    return index;
}