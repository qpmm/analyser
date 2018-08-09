#ifndef INCLUDE_ANALYSER_H
#define INCLUDE_ANALYSER_H

#include "main_config.h"
#include "trace_include_files.hpp"
#include "lexertl_iterator.hpp"

class include_analyser
{
public:
    include_analyser(std::vector<std::string>& _include_paths);

    void analyse_file(fs::path &file_path);
    void analyse_directory(fs::path& dir_path);
    int error();

    typedef wv::iteration_context_policies::load_file_to_string
        wv_policy;
    typedef wv::context<std::string::iterator, lex_iterator_type, wv_policy, trace_include_files>
        context_type;

    std::map<std::string, int> include_counter; // счётчик включений файлов
    std::vector<std::string>& include_paths; // пути для поиска заголовочных файлов

private:
    int error_code; // последняя ошибка
    wv::util::file_position_type current_pos; // для обработки исключений
};

#endif // INCLUDE_ANALYSER_H
