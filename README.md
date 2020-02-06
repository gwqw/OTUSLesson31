# realty (OTUSLesson31)
solution to otus c++ homework 16 (lesson 31)

## Условие

Цель задания кластеризация, классификация и поиск результата.
В качестве исходных данных будут использоваться предложения по продаже жилья. Данные состоят из разделенных точкой с запятой следующих полей

```
долгота;широта;комнат;цена;метраж;кухня;этаж;этажность\n
```
На основе этих данных необходимо разработать приложение, принимающее на вход строки вида
```
86.116781;55.335492;2;4326901.00;54.00;7.00;5;5\n
```
Последние два параметра превратить в флаг 0 - если этаж первый или последний, в остальных случаях - 1
Строки читаются через стандартный ввод. Приложение при запуске получает два обязательных параметра:

```
$ rclst 100 modelfname
```
где первый параметр - количество кластеров, а второй параметр - имя файла (без суффикса) для хранения необходимых данных. Сохраненные данные modelfname.XXX будут использоваться для классификации.
Для сохранения модели может пригодиться пример http://dlib.net/multiclass_classification_ex.cpp.html
Следует обратить внимание, что исходные данные для классификатора доступны не будут, все что необходимо для работы должно быть сохранено в файлах modelfname.XXX
Для классификации и поиска результата будет запускаться второе приложение:

```
$ rclss modelfname
```
где первый параметр - имя файла (без префикса) для загрузки необходимых данных из одного или нескольких файлов созданных на этапе кластеризации.
На стандартный ввод классификатора будут подаваться строки вида

```
86.116781;55.335492;2;4326901.00;54.00;7.00;1\n
```
В ответ на каждую строку необходимо вывести все предложения из ближайшего кластера отсортированные по расстоянию (сначала ближайшие).

## Самоконтроль

- пакет realty содержащий исполняемые файлы rclst и rclss опубликован на bintray
- отправлена на проверку ссылка на страницу репозитория

## Проверка

Задание считается выполненным успешно, если после установки пакета, подготовки модели и поиска удастся решить квартирный вопрос.



## Запуск программы

**points_generator.py** -- генератор город и продаваемые квартир как набор точек `долгота;широта;комнат;цена;метраж;кухня;этаж;этажность` в стандартный output. Параметр командной строки -- число городов.

**rclst** -- проводит кластеризацию предложений, поступающих в стандартный ввод, проводит обучение и сохраняет результаты обучения и предложения в файлы. В стандартный вывод выводит результат кросс валидации. Производит обучение и сохранение в файлы результатов независимо от качества кросс валидации.
Параметры командной строки:
```sh
rclst <cluster_num> <prefix_filename> [<gamma>, <coeff>, <degree>]
```
`cluster_num` -- число кластеров,
`prefix_filename` -- префикс для сохраняемых файлов. Для результатов обучения суффикс `.trn`, для предложений -- `.smp`
`gamma`, `coeff`, `degree` -- параметры для кластеризации и обучения. По умолчанию: 0.1, 1, 2.

**rclss** -- производит предсказывание группы для запроса, поступающего на стандартный ввод, и выводит подходящие предложения для запроса на стандартный вывод.
Параметры коммандной строки:
```sh
rclss <prefix_filename>
```

**plot_results.py** -- позволяет визуализировать результаты, поступающие на стандартный ввод, в виде диаграммы (цветных точек)
```sh
plot_results.py color_idx x_idx y_idx
```
`color_idx` -- номер колонки, которая будет использоваться как цвет (default: 0),
`x_idx`, `y_idx` -- номера колонок, которые будут использоваться как x и y диаграммы, соответственно (default: 1, 2).

**Example:**
```sh
./points_generator.py 10 | ./rclst 5 model 0.1 1 2
./rclss model < some_input_data
./plot_results.py model.smp 0 1 2
```