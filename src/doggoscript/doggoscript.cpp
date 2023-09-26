#include "../../includes/doggoscript/doggoscript.hpp"

DoggoscriptResult run(std::string src, SymbolTable *symbol_table) {
    Lexer lexer("stdin", src);
    LexerResult lex_result = lexer.tokenize();

    if (lex_result.error.has_value()) {
        return {.error = lex_result.error.value()};
    }

    if (lex_result.tokens.has_value() && lex_result.tokens.value().size() == 1 &&
        lex_result.tokens.value()[0].type == TokenType::FileEnd)
        return {};

    Parser parser(lex_result.tokens.value());
    ParseResult parse_result = parser.parse();

    if (parse_result.error.has_value()) {
        return {.error = parse_result.error.value()};
    }

    Interpreter interpreter;
    Context context("<prog>");
    context.symbol_table = symbol_table;
    RuntimeResult result = interpreter.visit(parse_result.node, context);

    if (result.error.has_value()) {
        return {.error = result.error.value()};
    }

    if (result.value.has_value() && result.value.value() != nullptr)
        return {.result = result.value.value()};

    return {};
}

void populate_symbol_table(SymbolTable *symbol_table) {
    symbol_table->set("print", new PrintFunction());
    symbol_table->set("input", new InputFunction());
    symbol_table->set("append", new AppendFunction());
    symbol_table->set("pop", new PopFunction());
    symbol_table->set("extend", new ExtendFunction());
    symbol_table->set("get", new GetFunction());
    symbol_table->set("len", new LenFunction());
    symbol_table->set("str", new StrFunction());
    symbol_table->set("dict_get", new DictGetFunction());
    symbol_table->set("dict_set", new DictSetFunction());
    symbol_table->set("load_file", new LoadFileFunction());
    symbol_table->set("save_file", new SaveFileFunction());
}
