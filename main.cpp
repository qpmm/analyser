#include "main_config.h"
#include "command_line_parser.h"
#include "include_analyser.h"

using namespace std;

int main(int argc, char* argv[])
{
    string src_path; // путь к каталогу с исходниками
    vector<string> include_paths; // пути для поиска заголовочных файлов

    command_line_parser parser(src_path, include_paths);
    if (parser.parse(argc, argv))
        return 1;

    fs::path p(src_path);
    include_analyser analyser(include_paths);
    analyser.analyse_directory(p); // запуск обработки
    cout << endl;

    if (analyser.error())
    {
        cerr << "Ошибка анализа файлов, работа программы будет прекращена." << endl;
        return 1;
    }

    vector<pair<string, int>> counter(analyser.include_counter.begin(), analyser.include_counter.end());
    sort(counter.begin(), counter.end(),
        [](pair<string, int>& p1, pair<string, int>& p2) {
            return ((p1.second == p2.second) ?
                        (p1.first < p2.first) : // по алфавиту
                        (p1.second > p2.second) // по убыванию частоты включений
            );
        }
    );

    for (auto item = counter.begin(); item != counter.end(); ++item)
        cout << item->first << " " << item->second << endl;

	return 0;
}

