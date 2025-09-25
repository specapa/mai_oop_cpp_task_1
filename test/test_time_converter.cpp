#include <gtest/gtest.h>
#include <string>
#include "TimeConverter.hpp"

// Тесты для функции parse (парсинг PM/AM времени)
TEST(TimeConverterTest, ParsePMTime) {
    EXPECT_EQ(parse("12:00 PM"), 0);     // 12:00 PM = 0 минут
    EXPECT_EQ(parse("12:30 PM"), 30);    // 12:30 PM = 30 минут
    EXPECT_EQ(parse("1:00 PM"), 60);     // 1:00 PM = 60 минут
    EXPECT_EQ(parse("11:45 PM"), 11*60 + 45); // 11:45 PM = 705 минут
}

TEST(TimeConverterTest, ParseAMTime) {
    EXPECT_EQ(parse("12:00 AM"), 12*60);     // 12:00 AM = 720 минут
    EXPECT_EQ(parse("12:30 AM"), 12*60 + 30); // 12:30 AM = 750 минут
    EXPECT_EQ(parse("1:00 AM"), 13*60);      // 1:00 AM = 780 минут
    EXPECT_EQ(parse("11:59 AM"), 23*60 + 59); // 11:59 AM = 1439 минут
}

TEST(TimeConverterTest, ParseEdgeCases) {
    EXPECT_EQ(parse("12:00 PM"), 0);        // Минимальное время
    EXPECT_EQ(parse("11:59 AM"), 23*60 + 59); // Максимальное время
}

// Тесты для функции convert (конвертация минут в 24-часовой формат)
TEST(TimeConverterTest, ConvertTo24Hour) {
    EXPECT_EQ(convert(0), "0000");        // 12:00 PM
    EXPECT_EQ(convert(30), "0030");       // 12:30 PM
    EXPECT_EQ(convert(60), "0100");       // 1:00 PM
    EXPECT_EQ(convert(11*60 + 45), "1145"); // 11:45 PM
    EXPECT_EQ(convert(12*60), "1200");    // 12:00 AM
    EXPECT_EQ(convert(13*60), "1300");    // 1:00 AM
    EXPECT_EQ(convert(23*60 + 59), "2359"); // 11:59 AM
}

TEST(TimeConverterTest, ConvertEdgeCases) {
    EXPECT_EQ(convert(0), "0000");
    EXPECT_EQ(convert(1439), "2359"); // Максимум в сутках
    EXPECT_EQ(convert(1440), "0000"); // Переход через полночь
    EXPECT_EQ(convert(1500), "0100"); // 25 часов = 1:00
}

// Тесты для полного цикла (parse + convert)
TEST(TimeConverterTest, FullConversion) {
    EXPECT_EQ(convert(parse("12:00 PM")), "0000");
    EXPECT_EQ(convert(parse("12:00 AM")), "1200");
    EXPECT_EQ(convert(parse("6:30 PM")), "0630");
    EXPECT_EQ(convert(parse("6:30 AM")), "1830");
    EXPECT_EQ(convert(parse("11:59 AM")), "2359");
}

// Тесты на некорректный ввод
TEST(TimeConverterTest, InvalidInput) {
    // Эти тесты предполагают, что функция parse бросает исключения
    // или возвращает специальное значение для ошибок
    EXPECT_THROW(parse("25:00 PM"), std::invalid_argument);
    EXPECT_THROW(parse("12:60 PM"), std::invalid_argument);
    EXPECT_THROW(parse("12:00PM"), std::invalid_argument); // Нет PM/AM
    EXPECT_THROW(parse("12:00:AM"), std::invalid_argument);
    EXPECT_THROW(parse("9/11 PM"), std::invalid_argument);
}

// Тесты для разных форматов ввода
TEST(TimeConverterTest, DifferentFormats) {
    EXPECT_EQ(convert(parse("1:30 AM")), "1330");
    EXPECT_EQ(convert(parse("01:30 AM")), "1330");
    EXPECT_EQ(convert(parse("1:3 AM")), "1303");
    EXPECT_EQ(convert(parse("01:3 AM")), "1303");
}

// Тесты производительности (опционально)
TEST(TimeConverterTest, Performance) {
    for (int i = 0; i < 1000; ++i) {
        auto result = convert(parse("11:59 AM"));
        EXPECT_EQ(result, "2359");
    }
}