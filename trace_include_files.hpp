#ifndef TRACE_INCLUDE_FILES_HPP
#define TRACE_INCLUDE_FILES_HPP

#include "main_config.h"
#include <boost/wave/preprocessing_hooks.hpp>

class trace_include_files : public wv::context_policies::default_preprocessing_hooks
{
public:
    trace_include_files(std::map<std::string, int>& _include_counter)
        : include_depth(1), include_counter(_include_counter) {}

    // Выводит имя включаемого файла в соответствии с иерархией
    void handle_include_file(std::string const& filename)
    {
        std::string real_filename = fs::path(filename).filename().string();

        if (include_counter.find(real_filename) == include_counter.end())
            include_counter[real_filename] = 0;

        ++include_counter[real_filename];

        for (std::size_t i = 0; i < include_depth; ++i)
            std::cout << "..";
        std::cout << real_filename;
    }

    // Обработка при обнаружении #include
    // Проверка на существование файла
    template <typename ContextT>
    bool found_include_directive(ContextT const& ctx, std::string const& filename, bool include_next)
    {
        bool is_system = (filename[0] == '<');
        std::string file_path = filename.substr(1, filename.length() - 2);
        std::string dir_path;

        handle_include_file(file_path);

        if (ctx.find_include_file(file_path, dir_path, is_system, nullptr))
        {
            std::cout << std::endl;
            return false;
        }

        std::cout << " (!)" << std::endl;
        return true;
    }

    // Обработка открытия включаемого файла
    template <typename ContextT>
    void opened_include_file(ContextT const& ctx, std::string const& relname,
        std::string const& filename, bool is_system_include)
    {
        ++include_depth;
    }

    // Обработка закрытия включаемого файла
    template <typename ContextT>
    void returning_from_include_file(ContextT const& ctx)
    {
        --include_depth;
    }

    std::size_t include_depth; // глубина
    std::map<std::string, int>& include_counter; // счётчик
};

#endif // TRACE_INCLUDE_FILES_HPP
