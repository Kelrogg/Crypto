## Лабораторные курса Методы и средства защиты компьютерной информации

### Лаб. раб. № 1. Часть I.
**Тема:** Использование архитектурных особенностей процессора при реализации криптографических процедур на примере простейшей симметричной криптографической системы
**Цель:** Изучение возможности использования архитектурных особенностей процессора при реализации арифметических операций в одномодульной системе вычетов.
**Задание:** Разработка библиотеки примитивов, реализующих арифметические операции в одномодульной системе вычетов. Разработать контрольные примеры.

### Лаб. раб. № 1. Часть II.
**Тема:** Реализация простейшей симметричной криптографической системы. Изучение роли секретного канала
**Цель:** Изучение роли секретного канала.
**Задание:** Реализовать примитивы прямого и обратного преобразования простейшей симметричной криптографической системы. Разработать контрольные примеры.

### Лаб. раб. № 1. Часть III.
**Тема:** Криптоанализ простейшей симметричной криптографической системы с короткопериодическим ключом. Изучение понятия практической стойкости
**Цель:** Изучение понятия практической стойкости шифров.
**Задание:** Реализовать атаку на простейшую симметричную криптосистему методом сужения.

## Сборка

### С помощью CMake

```bash
mkdir build && cd build
cmake ..         # Для сборки тестов добавить параметр -DBUILD_TESTS=on
cmake --build .
```