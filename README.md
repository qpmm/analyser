# analyser

Для реализации задачи выбрана библиотека Boost Wave, призванная решать связанные с препроцессингом задачи. За основу взят официальный пример, демонстрирующий возможности библиотеки:

https://github.com/boostorg/wave/tree/develop/samples/list_includes

Программа состоит из следующих компонентов:
1. Парсер командной строки (command_line_parser.h)
2. Непосредственно анализатор включений (include_analyser.h)
3. Класс, реализующий методы анализатора (trace_include_files.hpp)

На первом этапе парсер командной строки получает путь к исходным файлам и перечисленные через опцию -I пути для поиска заголовных файлов. Затем эти данные передаются в объект анализатора, который начинает рекурсивный обход заданной папки: если встречается .cpp файл, то анализатор приступает к его обработке. Каждое обнаруженное включение сразу же выводится в консоль, в соответствии с иерархией, при этом отсутствующий файл помечается знаком (!), отображаемым после имени файла.

Запуск и вывод результата реализован в соответствии с постановкой задачи. Т.к. непосредственная обработка (препроцессинг) выполняется библиотекой Wave, все указанные в постановке примечания удовлетворены.
