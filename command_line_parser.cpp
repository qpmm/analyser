#include "command_line_parser.h"

command_line_parser::command_line_parser(std::string& _src_path, std::vector<std::string>& _include_paths)
    : desc("Usage: analyser directory [options]"), src_path(_src_path), include_paths(_include_paths)
{
    desc.add_options()
        ("help,h", "print out program usage (this message)")
        ("include,I", po::value<std::vector<std::string>>(),
            "specify additional include directory")
    ;
}

int command_line_parser::parse(int argc, char *argv[])
{
	// Отключаем ксенофобию парсера относительно неизвестных опций
	po::parsed_options opts = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();

    for (auto opt = opts.options.begin(); opt != opts.options.end(); ++opt)
    {
		// Неизвестная опция
		if (opt->unregistered)
		{
			std::cerr << "analyser: Unknown option: " << opt->string_key << std::endl;
			return 1;
		}

		// Опция -h/--help
        if (opt->string_key == "help")
        {
            std::cout << desc << std::endl;
            return 2;
        }
		
		// Аргумент без опции - ожидаем путь к папке
        if (opt->position_key != -1 && src_path.empty())
        {
            src_path = opt->value[0];
            continue;
        }

        // Опция -I
        if (opt->string_key == "include")
            include_paths.push_back(opt->value[0]);
    }

    if (src_path.empty())
    {
        std::cerr << "analyser: No input directory given.\nUse --help to get a hint." << std::endl;
        return 3;
    }

    if (!fs::is_directory(src_path))
    {
        std::cerr << "analyser: " << src_path << " is not a directory." << std::endl;
        return 4;
    }

    return 0;
}
