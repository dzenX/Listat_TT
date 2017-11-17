#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#include "descriptive_exception.h"

#define LTAG '<'
#define RTAG '>'

using std::map;
using std::ifstream;
using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

class XMLparser
{
private:
	map<int, int> parsed_interval;
	ifstream xmlfile;
	vector<string*> xml_parsed;
public:
	XMLparser() = default;
	XMLparser(const char* filename);
	void parse();
	void makeIntervals();
	vector<pair<int, int>> giveNums();
	void printParsed();
	void printInervals();
	~XMLparser() = default;
};

