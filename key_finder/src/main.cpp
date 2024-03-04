#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <set>
#include <cctype>
#include "argparse/argparse.hpp"
#include "FileInputStream.h"
#include "mod_math_lib.h"
#include "set_intersection.hpp"

using SetOfChars = std::set<uint8_t>;

SetOfChars ReadSetOfChars(FileInputStream& input);

std::string Hack(std::string& text, SetOfChars& alphabeth);

int main(int argc, char** argv)
try
{
	setlocale(LC_ALL, "");

	argparse::ArgumentParser prog("key_finder", "1.0");

	prog.add_argument("input_file")
		.help("path to encrypted input file");

	try
	{
		prog.parse_args(argc, argv);
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl;
		std::cout << prog;
		return 1;
	}

	std::string inFilePath = prog.get<std::string>("input_file");

	FileInputStream inKeyAlphabetFile("key_alphabet.txt");
	auto keyAlphabet = ReadSetOfChars(inKeyAlphabetFile);
	FileInputStream inMsgAlphabetFile("msg_alphabet.txt");
	auto msgAlphabet = ReadSetOfChars(inMsgAlphabetFile);

	FileInputStream cipherInput(inFilePath);
	std::string text;
	while (!cipherInput.IsEOF()) {
		char symbol = cipherInput.ReadByte();
		if (msgAlphabet.find(toupper(symbol)) == msgAlphabet.end()) continue;
		text.push_back(toupper(symbol));
	}

	std::string key = Hack(text, msgAlphabet);
	std::cout << "Found key: " << key << std::endl;

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
	return 1;
}

SetOfChars ReadSetOfChars(FileInputStream& input)
{
	std::set<uint8_t> res;

	while (!input.IsEOF())
	{
		res.insert(input.ReadByte());
	}

	return res;
}

std::string Hack(std::string& text, SetOfChars& alphabeth_set) {
    // std::string alphabeth = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string alphabeth;
	for (char el : alphabeth_set) alphabeth.push_back(el);

    std::vector<double> symbols_freq = {8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 1.97, 0.07};

    int codeLen = text.length();
    int gamma_len = -1;
    for (int n = 2; n < (codeLen / 2); ++n) {
        // Формируем столбец
        std::vector<char> col = {};
        for (int i = 0; i < codeLen; i += n)
            col.push_back(text[i]);

        // Посчитать индекс Фридмана для каждого нулевого столбика для всех длин,
        // взять за эталонную первую, при которой индекс будет максимально близок к 0.066
        std::array<int, 26> symbols_count = {0};
        for (auto& symb : col)
            ++symbols_count[alphabeth.find(symb) + 1];

        double friedman_index = 0.0;
        for (int i = 0; i < 26; ++i) {
            friedman_index += ((symbols_count[i] * (symbols_count[i] - 1)));
		}
        friedman_index /= (col.size() * (col.size() - 1));

        // Проверить индекс на попадание в диапазон
        if (friedman_index > 0.053) {
            gamma_len = n;
			break;
		}
    }

	// Разбиваем текст на столбцы по этой длине гаммы
    // формируем подстроки
    std::vector<std::string> rows;
    for (int i = 0; i < codeLen - gamma_len; i += gamma_len) {
        std::string row;
        for (int j = 0; j < gamma_len; ++j) {
            row.push_back(text[i + j]);
        }
        rows.push_back(row);
    }

	// формируем столбцы
    std::vector<std::vector<char>> columns(gamma_len);
    for (int k = 0; k < gamma_len; ++k) {
        std::vector<char> column = {};
        for (const auto& row : rows) {
            column.push_back(row[k]);
        }
        columns[k] = column;
    }

    std::vector<int> slides;
    for (int n = 1; n < gamma_len; ++n) {

        // Находим встречаемость каждого символа в первом столбике
        std::array<int, 26> first_symbols_count = {0};
        for (auto& symb : columns[n - 1])
            ++first_symbols_count[alphabeth.find(symb)];

        // Ищем сдвиг для второго столбца такой, чтобы взаимный индекс Фридмана был близок к 0.066
        for (int m = 0; m < 26; ++m) {
            std::vector<char> slide_second_col = {};

            for (auto& symb : columns[n])
                slide_second_col.push_back(alphabeth[(alphabeth.find(symb) + m) % 26]);

            std::array<int, 26> second_symbols_count = {0};
            for (auto& symb : slide_second_col)
                ++second_symbols_count[alphabeth.find(symb)];

            //Находим взаимный индекс Фридмана
            double friedman_index = 0.0;
            for (int i = 0; i < first_symbols_count.size(); ++i)
                friedman_index += (first_symbols_count[i] * second_symbols_count[i]);
			friedman_index /= (pow(columns[n].size(), 2));

            //Проверяем диапазон
            //Если попали, запоминаем это смещение и останавливаем перебор
            if (friedman_index > 0.053) {
                slides.push_back((26 - m) % 26);
                break;
            }
        }
    }

    // У нас есть взаимные сдвиги всех столбцов, теперь нужно найти сдвиг первого
    // искать будем с помощью частотного анализа символов(как в шифре Цезаря)
    std::array<int, 26> current_symbols_freq = {0};

    for (auto& symb : columns[0])
        ++current_symbols_freq[alphabeth.find(symb)];

    for (int i = 0; i < current_symbols_freq.size(); ++i)
        current_symbols_freq[i] = current_symbols_freq[i] * 100 / columns[0].size();

    // Находим все возможные сдвиги для первого столбца
    std::vector<int> first_col_slides;
    for (int i = 0; i < current_symbols_freq.size(); ++i)
        for (int j = 0; j < symbols_freq.size(); ++j)
            if (abs(current_symbols_freq[i] - symbols_freq[j]) < 0.12)
                first_col_slides.push_back(i - j);

    // Берем за эталонное такое смещение, которое встречалось чаще всего
    int final_slide = first_col_slides[0];
    int maximum = std::count(first_col_slides.cbegin(), first_col_slides.cend(), first_col_slides[0]);

    for (auto& slide : first_col_slides) {
        int count = std::count(first_col_slides.cbegin(), first_col_slides.cend(), slide);
        if (count > maximum) {
            maximum = count;
            final_slide = slide;
        }
    }

    // Посчитать сдвиги для столбиков, зная сдвиг первого
    std::vector<int> final_slides;
    final_slides.push_back(final_slide);
    for (auto& slide : slides)
        final_slides.push_back(slide);

    for (size_t i = 1; i < final_slides.size(); ++i)
        final_slides[i] = (final_slides[i-1] + final_slides[i]) % 26;

    std::string gamma;
    for (const auto& slide : final_slides) {
        gamma.push_back(alphabeth[slide]);
    }

    return gamma;
}