# Практическая работа #2
---
### Вариант 2. Поиск максимума.

На вход подается число n &isin; N : n &le; 2147483647, а также n чисел x<sub>i</sub> ∈ Z : |x<sub>i</sub>| &le; 2147483647 для любого целого <i>i</i> от 1 до <i>n</i>. Вывести значение максимального x<sub>i</sub>.

### Вариант 13. Cумма квадратов. 
На вход подается число n &isin; N : n &le; 2147483647, а также n чисел x<sub>i</sub> ∈ Z : |x<sub>i</sub>| &le; 2147483647 для любого целого <i>i</i> от 1 до <i>n</i>. Вывести значение &sum;x<sup>2</sup><sub>i</sub>, где *i* = от *1* до *n*.

### Ход работы
---
1. Для выполнения первого задания в терминал необходимо ввести команды:
```sh
$ cd timp
$ touch 02_max.c
$ subl 02_max.c
```
2. После того, как код был написан:
```sh
$ gcc 02_max.c -o max
$ ./max
```
При выполнении второго задания все происходит аналогично, за исключением имени файла. 

3. Далее необходимо все загрузить на удаленный репозиторий:
```sh
$ git branch pr2
$ git checkout pr2
$ git add .
$ git commit -m "added 2 files and README.md"
$ git push -u origin pr2
```
### Результаты
---
##### Результат работы программы по поиску максимума. 
![](https://cdn1.savepice.ru/uploads/2019/2/23/f0ebcc42b55c020137430cf2e39df143-full.png "max")
 
 Первое число - количество чисел. На последней строке - максимум из введенных числел.
 
 ##### Результат работы программы, суммирующей квадраты введенных чисел. 
![](https://cdn1.savepice.ru/uploads/2019/2/23/c757985c70e1a3d98d5571f91b42933c-full.png "sum")
 
 Первое число - количество чисел. На последней строке - результат.
 
 ### Таблица
 

| Resource | Link |
| ------ | ------ |
| Github | https://github.com/amattterasu/timp |
| Documentation | https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet |
| Google | https://www.google.com |
-----

&copy; 2019 Andrey Gubaydullin 737-2

-----
