#pragma once

#include <string>
#include <sstream>
#include <format>
#include <utility>
#include <optional>
#include <unordered_map>

#include "position.hpp"

enum class TokenType {
    FileEnd = -1,
    Int,
    Float,
    Plus,
    Minus,
    Multiply,
    Divide,
    LParen,
    RParen,
    Power,
    Variable,
    Identifier,
    Keyword,
    EqualsTo,
    NotEquals,
    GreaterThan,
    LessThan,
    GreaterThanEquals,
    LessThanEquals,
    LogicalAnd,
    LogicalOr,
    LogicalNot,
    LCurly,
    RCurly,
    Through,
    Comma,
    String,
    LSquare,
    RSquare,
    NewLine,
    Colon,
};

const std::unordered_map<TokenType, std::string> type_to_str = {
        {TokenType::FileEnd,           "EOF"},
        {TokenType::Int,               "Int"},
        {TokenType::Float,             "Float"},
        {TokenType::Plus,              "Plus"},
        {TokenType::Minus,             "Minus"},
        {TokenType::Multiply,          "Multiply"},
        {TokenType::Divide,            "Divide"},
        {TokenType::LParen,            "LParen"},
        {TokenType::RParen,            "RParen"},
        {TokenType::Power,             "Power"},
        {TokenType::Variable,          "Variable"},
        {TokenType::Identifier,        "Identifier"},
        {TokenType::Keyword,           "Keyword"},
        {TokenType::EqualsTo,          "EqualsTo"},
        {TokenType::NotEquals,         "NotEquals"},
        {TokenType::GreaterThan,       "GreaterThan"},
        {TokenType::LessThan,          "LessThan"},
        {TokenType::GreaterThanEquals, "GreaterThanEquals"},
        {TokenType::LessThanEquals,    "LessThanEquals"},
        {TokenType::LogicalAnd,        "LogicalAnd"},
        {TokenType::LogicalOr,         "LogicalOr"},
        {TokenType::LogicalNot,        "LogicalNot"},
        {TokenType::LCurly,            "LCurly"},
        {TokenType::RCurly,            "RCurly"},
        {TokenType::Through,           "Through"},
        {TokenType::Comma,             "Comma"},
        {TokenType::String,            "String"},
        {TokenType::LSquare,           "LSquare"},
        {TokenType::RSquare,           "RSquare"},
        {TokenType::NewLine,           "NewLine"},
        {TokenType::Colon, "Colon"},
};

const std::vector<std::string> keywords = {
        "val",
        "is",
        "true",
        "false",
        "if",
        "else",
        "for",
        "while",
        "in",
        "fn",
        "return",
        "continue",
        "break",
};

struct Token {
    TokenType type;
    std::string value;
    std::optional<Position> start_pos;
    std::optional<Position> end_pos;

    Token(TokenType type, std::optional<std::string> value, std::optional<Position> start_pos,
          std::optional<Position> end_pos);

    [[nodiscard]] bool is_keyword(const std::string &keyword);

    [[nodiscard]] std::string str() const;
};
