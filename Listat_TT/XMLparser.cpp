#include "XMLparser.h"

XMLparser::XMLparser(const char* filename)
{
	xmlfile.open(filename);
	if (!xmlfile.is_open()) {
		throw descriptive_exception("Load of file failed\n");
	}
}

void XMLparser::parse()
{
	string current_line, curr_tag, curr_info;
	while (!xmlfile.eof()) {
		std::getline(xmlfile, current_line);
		if (current_line.empty())
			continue;
		bool in_tag = false;
		for (size_t i = 0; i < current_line.length(); i++) {
			if ((current_line[i] == '\t') || (current_line[i] == '\n') || (current_line[i] == ' '))
				continue;
			if (current_line[i] == LTAG) {
				in_tag = true;
				curr_tag += current_line[i];
				if (!curr_info.empty())
					xml_parsed.push_back(new string(curr_info));
				curr_info.clear();
				continue;
			}
			else if (current_line[i] == RTAG) {
				in_tag = false;
				curr_tag += current_line[i];
				if (!curr_tag.empty())
					xml_parsed.push_back(new string(curr_tag));
				curr_tag.clear();
				continue;
			}

			if (in_tag)
				curr_tag += current_line[i];
			else
				curr_info += current_line[i];
		}
	}
}

void XMLparser::makeIntervals()
{
	//bool success = false;
	auto beg_it = xml_parsed.begin();
	auto end_it = xml_parsed.end();
	for (auto it = xml_parsed.begin(); it != xml_parsed.end(); it++) {
		if (**it == "<intervals>")
			beg_it = it;
		else if (**it == "</intervals>") {
			end_it = it;
			continue;
		}
	}
	auto it = beg_it;
	bool low = false, high = false, curr_int = false;
	pair<int, int> curr_lh;
	curr_lh.first = -1;
	curr_lh.second = -1;
	string buff;
	while (it != end_it) {
		if (curr_int) {
			if (low) {
				buff = **it;
				try {
					curr_lh.first = std::atoi(buff.c_str());
				}
				catch (std::exception e) {
					throw descriptive_exception("Invalid element");
				}
				low = false;
			}
			else if (high) {
				buff = **it;
				try {
					curr_lh.second = std::atoi(buff.c_str());
				}
				catch (std::exception e) {
					throw descriptive_exception("Invalid element");
				}
				high = false;
			}
			if (**it == "<low>")
				low = true;
			else if (**it == "<high>")
				high = true;
			else if (**it == "</low>")
				low = false;
			else if (**it == "</high>")
				high = false;
		}
		if (**it == "<interval>")
			curr_int = true;
		else if (**it == "</interval>") {
			curr_int = false;
			if ((curr_lh.first == -1)||(curr_lh.second == -1)) 
				throw descriptive_exception("Invalid interval");
			else {
				parsed_interval.insert(curr_lh);
				curr_lh.first = -1;
				curr_lh.second = -1;
			}
		}
		it++;
	}
}

vector<pair<int, int>> XMLparser::giveNums()
{
	return vector<pair<int, int>>();
}

void XMLparser::printParsed()
{
	for each (string* curr in xml_parsed)
	{
		cout << curr->c_str() << endl;
	}
}

void XMLparser::printInervals()
{
	for (auto it = parsed_interval.begin(); it != parsed_interval.end(); it++)
	{
		cout << it->first << endl;
		cout << it->second << endl << endl;
	}
}

