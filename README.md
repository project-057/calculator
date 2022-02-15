![1 + 1 = 10](https://see.fontimg.com/api/renderfont4/1Gngj/eyJyIjoiZnMiLCJoIjoxMjYsInciOjE1MDAsImZzIjo4NCwiZmdjIjoiIzAwMDAwMCIsImJnYyI6IiNFOEJDODYiLCJ0IjoxfQ/MSArIDE9MTA/arush-shiny.png)

# Калькулятор команды "Леша бросает курить"

## 📋 Описание

Это калькулятор, сделанный для проектов по курсу "Программирование на C" в ВШЭ.
Калькулятор принимает математическое выражение в инфиксной записи, вычисляет
ответ и выводит его на экран.

Плюшки:

 * поддерживает переменные
 * оттестирован до нитки
 * написан с любовью ❤️

## 🏗 Компиляция

```sh
make
```

## 🧪 Тестирование

#### Запустить unit-тесты

```sh
make test
```

#### Запустить интеграционные тесты (требуется Python)

```sh
make integrationtest
```

## 🧑‍🏭 Принцип работы

```mermaid
  flowchart TD;
    id1([строка пользователя]) --> |Разделить строку пользователя на токены|split_to_tokens;
    split_to_tokens --> |Заменить токены с переменными на численные значения|variables_to_values;
    variables_to_values --> |Преобразовать токены в ОП запись|to_rpn;
    to_rpn --> |Посчитать ответ|eval;
    eval --> id2([экран пользователя]);
    style id1 fill:#bbf;
    style id2 fill:#bbf;
```

## 🧑‍🎓 Чему научились

Мы хотели написать проект не только для того, чтобы улучшить понимание C, а для
того, чтобы потрогать хорошие практики программирования. Может показаться
абсурдным использование сложных технологий для такой простой задачи, но в их
изучении и была главная цель.

Мы

 * писали код в git-репозитории укротили Github Actions и Docker для
 автоматической компиляции и проверки качества кода
 * изучили библиотеку greatest для написания юнит-тестов
 * наклепали интеграционных тестов и скрипт на Python для проверки цельной программы
 * использовали Kanban доску и Pull Requests для управлениями задачами

Итогом мы получили проект, в котором автоматически прогонялась компиляция,
проверялся стиль кода. Каждое новое изменение читалось не только автором
кода, но 1 &ndash; 2 ревьюверами. Таким образом, внутри команды поддерживалось
общее понимание внутренностей проекта, баги отлавливались до вливания в
основную кодовую базу, а более сообразительные участники делились знаниями с
остальными.

#### Доска с задачами
<img width="1675" alt="изображение" src="https://user-images.githubusercontent.com/28492051/153965579-ee317d54-d82c-4edd-a98c-1a8820ba0c88.png">

#### Общение внутри Pull Request
<img width="1022" alt="изображение" src="https://user-images.githubusercontent.com/28492051/153965746-b09a5e43-2e3c-4532-a8ab-d296078d5e39.png">

#### Логи пройденных тестов
<img width="1652" alt="изображение" src="https://user-images.githubusercontent.com/28492051/153965984-0ba22001-914d-4226-98fd-0748c3b5b64d.png">

<img width="1792" alt="Screenshot 2022-02-15 at 11 54 46 AM" src="https://user-images.githubusercontent.com/28492051/154027032-f6314199-7589-4fbb-8f17-1d2bc5ff32f8.png">

<img width="1792" alt="Screenshot 2022-02-15 at 11 54 46 AM" src="https://user-images.githubusercontent.com/28492051/154027062-81c33dd5-8bb5-496d-9b14-c95b3f9123bc.png">


## 📺 Дополнительная активность

Мы даже устроили онлайн-трансляции для нашего потока!

Каждую субботу Оскар подключался и 2 &ndash; 3 часа транслировал, как он
программирует или настраивает окружение. Суммарно на данный момент стримы
набрали более 280 просмотров, и это не конец.

<img width="774" alt="изображение" src="https://user-images.githubusercontent.com/28492051/153965488-fb98b87a-b199-4474-b6f7-73d36eb8d907.png">
