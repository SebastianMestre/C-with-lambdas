#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

std::string base_16 (auto x) {
	char lookup[] = "abcdefghijklmnop";
	std::string result;
	while(x){
		result.push_back(lookup[x&15]);
		x >>= 4;
	}
	return result;
}

struct lambda_data {
	std::string return_type;
	std::string arglist;
	std::string body;

	std::string name () {
		std::string cat = return_type + arglist + body;
		return base_16(std::hash<std::string>{}(cat));
	}
	std::string definition () {
		return return_type + " " + name() + arglist + "\n{\n\treturn " + body + ";\n}\n";
	}
};

struct parse_result {
	bool success;
	int length;
	lambda_data l;
};

parse_result parse (std::string_view str) {
	std::string_view original_view = str;

	if(str.size() <= 0 || str[0] != '(') return {false, 0, {}};
	if(str.size() <= 1 || str[1] != 'f') return {false, 0, {}};
	if(str.size() <= 2 || str[2] != 'n') return {false, 0, {}};
	str.remove_prefix(3);

	while(str.size() > 0 && str[0] == ' ') str.remove_prefix(1);

	if(str.size() <= 0 || str[0] != '(') return {false, 0, {}};

	std::string arglist;
	{
		int nesting = 0;
		int i = 0;
		while(true){
			if(not(i < str.size())) return {false, 0, {}};
			if(str[i]=='(') nesting++;
			if(str[i]==')') nesting--;
			i++;
			if(nesting == 0) break;
		}

		arglist = std::string{str.substr(0, i)};
		str.remove_prefix(i);
	}

	while(str.size() > 0 && str[0] == ' ') str.remove_prefix(1);

	if(str.size() <= 0 || str[0] != ':') return {false, 0, {}};
	str.remove_prefix(1);

	while(str.size() > 0 && str[0] == ' ') str.remove_prefix(1);

	int return_type_length = 0;
	while(return_type_length < str.size() && str[return_type_length] != '=')
		return_type_length++;
	if(return_type_length == 0) {
		std::cerr << "failed to find return value during lamda parsing\n";
		return {false, 0, {}};
	}
	std::string return_type = std::string{str.substr(0, return_type_length)};
	str.remove_prefix(return_type_length);

	if(str.size() <= 0 || str[0] != '=') return {false, 0, {}};
	if(str.size() <= 1 || str[1] != '>') return {false, 0, {}};
	str.remove_prefix(2);

	while(str.size() > 0 && str[0] == ' ') str.remove_prefix(1);

	std::string body;
	{
		int nesting = 1;
		int i = 0;
		while(true){
			if(not(i < str.size())) {
				return {false, 0, {}};
			}
			if(str[i]=='(') nesting++;
			if(str[i]==')') nesting--;
			i++;
			if(nesting == 0) break;
		}

		body = std::string{str.substr(0, i-1)};
		str.remove_prefix(i);
	}

	int len = original_view.size() - str.size();
	return {true, len, {return_type, arglist, body}};
}

int main (int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "no provided input file\n";
		exit(1);
	}
	std::ifstream inputfile{argv[1]};

	std::stringstream filecontents;
	std::string line;
	while(std::getline(inputfile, line))
		filecontents << line << '\n';

	std::string content_as_string = filecontents.str();
	std::string_view content_view = content_as_string;

	std::unordered_map<std::string, lambda_data> lambdas;

	std::stringstream replaced;

	replaced << "/* this file was generated from " << argv[1] << ", do not modify or your changes might be lost*/\n";

	while (not content_view.empty()) {
		auto pr = parse(content_view);
		if(pr.success) {
			lambdas.insert({pr.l.name(), pr.l});
			content_view.remove_prefix(pr.length);
			replaced << pr.l.name();
		} else {
			replaced << content_view[0];
			content_view.remove_prefix(1);
		}
	}

	std::string replaced_as_string = replaced.str();
	auto pos = replaced_as_string.find("/*__LAMBDA__*/");

	for(auto& [k,l] : lambdas){
		replaced_as_string.insert(pos, l.definition());
	}

	std::cout << replaced_as_string;
}

