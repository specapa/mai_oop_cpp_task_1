#include <gtest/gtest.h>
#include <string>
#include "TimeConverter.hpp"

// Тесты для функции parse (парсинг AM/PM времени)
TEST(TimeConverterTest, ParseAMTime) {
    EXPECT_EQ(parse("12:00 AM"), 0);     // 12:00 AM = 0 минут
    EXPECT_EQ(parse("12:30 AM"), 30);    // 12:30 AM = 30 минут
    EXPECT_EQ(parse("1:00 AM"), 60);     // 1:00 AM = 60 минут
    EXPECT_EQ(parse("11:45 AM"), 11*60 + 45); // 11:45 AM = 705 минут
}

TEST(TimeConverterTest, ParsePMTime) {
    EXPECT_EQ(parse("12:00 PM"), 12*60);     // 12:00 PM = 720 минут
    EXPECT_EQ(parse("12:30 PM"), 12*60 + 30); // 12:30 PM = 750 минут
    EXPECT_EQ(parse("1:00 PM"), 13*60);      // 1:00 PM = 780 минут
    EXPECT_EQ(parse("11:59 PM"), 23*60 + 59); // 11:59 PM = 1439 минут
}

TEST(TimeConverterTest, ParseEdgeCases) {
    EXPECT_EQ(parse("12:00 AM"), 0);        // Минимальное время
    EXPECT_EQ(parse("11:59 PM"), 23*60 + 59); // Максимальное время
}

// Тесты для функции convert (конвертация минут в 24-часовой формат)
TEST(TimeConverterTest, ConvertTo24Hour) {
    EXPECT_EQ(convert(0), "00:00");        // 12:00 AM
    EXPECT_EQ(convert(30), "00:30");       // 12:30 AM
    EXPECT_EQ(convert(60), "01:00");       // 1:00 AM
    EXPECT_EQ(convert(11*60 + 45), "11:45"); // 11:45 AM
    EXPECT_EQ(convert(12*60), "12:00");    // 12:00 PM
    EXPECT_EQ(convert(13*60), "13:00");    // 1:00 PM
    EXPECT_EQ(convert(23*60 + 59), "23:59"); // 11:59 PM
}

TEST(TimeConverterTest, ConvertEdgeCases) {
    EXPECT_EQ(convert(0), "00:00");
    EXPECT_EQ(convert(1439), "23:59"); // Максимум в сутках
    EXPECT_EQ(convert(1440), "00:00"); // Переход через полночь
    EXPECT_EQ(convert(1500), "01:00"); // 25 часов = 1:00
}

// Тесты для полного цикла (parse + convert)
TEST(TimeConverterTest, FullConversion) {
    EXPECT_EQ(convert(parse("12:00 AM")), "00:00");
    EXPECT_EQ(convert(parse("12:00 PM")), "12:00");
    EXPECT_EQ(convert(parse("6:30 AM")), "06:30");
    EXPECT_EQ(convert(parse("6:30 PM")), "18:30");
    EXPECT_EQ(convert(parse("11:59 PM")), "23:59");
}

// Тесты на некорректный ввод
TEST(TimeConverterTest, InvalidInput) {
    // Эти тесты предполагают, что функция parse бросает исключения
    // или возвращает специальное значение для ошибок
    EXPECT_THROW(parse("25:00 AM"), std::invalid_argument);
    EXPECT_THROW(parse("12:60 AM"), std::invalid_argument);
    EXPECT_THROW(parse("12:00AM"), std::invalid_argument); // Нет AM/PM
    EXPECT_THROW(parse("12:00:PM"), std::invalid_argument);
    EXPECT_THROW(parse("9/11 AM"), std::invalid_argument);
}

// Тесты для разных форматов ввода
TEST(TimeConverterTest, DifferentFormats) {
    EXPECT_EQ(convert(parse("1:30 PM")), "13:30");
    EXPECT_EQ(convert(parse("01:30 PM")), "13:30");
    EXPECT_EQ(convert(parse("1:3 PM")), "13:03");
    EXPECT_EQ(convert(parse("01:3 PM")), "13:03");
}

// Тесты производительности (опционально)
TEST(TimeConverterTest, Performance) {
    for (int i = 0; i < 1000; ++i) {
        auto result = convert(parse("11:59 PM"));
        EXPECT_EQ(result, "23:59");
    }
}