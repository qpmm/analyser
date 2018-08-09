#include "include_analyser.h"

include_analyser::include_analyser(std::vector<std::string>& _include_paths) :
    error_code(0), include_paths(_include_paths) {}

void include_analyser::analyse_file(fs::path& file_path)
{
    // Открытие и чтение файла
    std::ifstream instream(file_path.c_str());
    std::string buf;

    if (!instream.is_open())
    {
        std::cerr << "Could not open input file: " << file_path << std::endl;
        error_code = 1;
        return;
    }

    instream.unsetf(std::ios::skipws);
    buf.assign(std::istreambuf_iterator<char>(instream.rdbuf()),
               std::istreambuf_iterator<char>());

    // Создание обработчика включений
    trace_include_files trace(include_counter);
	context_type ctx(buf.begin(), buf.end(), file_path.string().c_str(), trace);

    // Передача в обработчик путей для поиска заголовочных файлов
    for (auto path = include_paths.begin(); path != include_paths.end(); ++path)
        ctx.add_sysinclude_path(path->c_str());

    std::cout << file_path.filename().string() << std::endl;

    try
    {
        // Обработка выполняется библиотекой Wave "на лету" при работе с итератором
        for (auto it = ctx.begin(); it != ctx.end(); ++it)
            current_pos = it->get_position();
    }
    catch (wv::cpp_exception& e)
    {
        std::cerr << e.file_name() << "(" << e.line_no() << "): "
                  << e.description() << std::endl;
        error_code = 2;
    }
    catch (std::exception& e)
    {
        std::cerr << current_pos.get_file()
                  << "(" << current_pos.get_line() << "): "
                  << "exception caught: " << e.what() << std::endl;
        error_code = 3;
    }
    catch (...)
    {
        std::cerr << current_pos.get_file()
                  << "(" << current_pos.get_line() << "): "
                  << "unexpected exception caught." << std::endl;
        error_code = 4;
    }
}

void include_analyser::analyse_directory(fs::path& dir_path)
{
    typedef fs::directory_iterator dir_iter;

    // Рекурсивный обход папок
    for (auto entry = dir_iter(dir_path); !error_code && entry != dir_iter(); ++entry)
    {
        fs::path p(entry->path());
        if (fs::is_directory(p))
            analyse_directory(p);
        else if (fs::is_regular_file(p) && p.extension() == ".cpp")
            analyse_file(p);
    }
}

int include_analyser::error()
{
    return error_code;
}
