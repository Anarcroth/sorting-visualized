#include <algorithm>

#include "command_parser.hpp"

command_parser::command_parser(int &argc, char **argv)
{
    for (int i=1; i < argc; ++i)
	this->tokens.push_back(std::string(argv[i]));
}

const std::string& command_parser::get_cmd_option(const std::string &option) const
{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(tokens.begin(), tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end())
	return *itr;

    static const std::string empty_string("");
    return empty_string;
}

bool command_parser::cmd_option_exists(const std::string &option) const
{
    return std::find(this->tokens.begin(), this->tokens.end(), option)
	!= this->tokens.end();
}
