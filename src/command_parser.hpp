#ifndef __INPUT_PARSER_H_INCLUDED__
#define __INPUT_PARSER_H_INCLUDED__

#include <string>
#include <vector>

class command_parser
{
public:
    command_parser(int &argc, char **argv);

    const std::string& get_cmd_option(const std::string &option) const;
    bool cmd_option_exists(const std::string &option) const;

private:
    std::vector<std::string> tokens;
};

#endif
