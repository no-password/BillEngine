#include "common.h"

std::vector<std::string> tokenize(std::string text, std::string delim) {
	std::vector<std::string> tokens;
	char *c_text = strdup(text.c_str());
	char *c_delim = strdup(delim.c_str());
	char *c_tok = strtok(c_text, c_delim);

	while (c_tok != NULL) {
		std::string tok(c_tok);
		tokens.push_back(tok);
		c_tok = strtok(NULL, c_delim);
	}

	return tokens;
}

bool stringIsInteger(std::string s) {
	return !s.empty() && s.find_first_not_of("0123456789-") == std::string::npos;
}

bool stringIsNumber(std::string s) {
	return !s.empty() && s.find_first_not_of("0123456789.-") == std::string::npos;
}
