#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include "main_config.h"

class command_line_parser
{
public:
    command_line_parser(std::string& _src_path, std::vector<std::string>& _include_paths);

    int parse(int argc, char *argv[]);

private:
    po::options_description desc; // поддерживаемые опции командной строки
    std::string& src_path; // путь к каталогу с исходниками
    std::vector<std::string>& include_paths; // пути для поиска заголовочных файлов
};

#endif // COMMAND_LINE_PARSER_H
