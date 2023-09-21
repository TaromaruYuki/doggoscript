#pragma once

#include <string>
#include <map>
#include "position.hpp"

struct Object;

class SymbolTable {
    std::map<std::string, Object *> symbols;
    std::optional<SymbolTable *> parent;

public:
    SymbolTable() {
        this->parent = std::nullopt;
    }

    explicit SymbolTable(SymbolTable *parent) {
        this->parent = parent;
    }

    Object *get(const std::string &name) {
        if (this->symbols.contains(name))
            return this->symbols[name];

        if (this->parent.has_value())
            return this->parent.value()->get(name);

        return nullptr;
    }

    void set(std::string name, Object *value) {
        this->symbols[name] = value;
    }

    void remove(const std::string &name) {
        this->symbols.erase(name);
    }
};


struct Context {
    std::string display_name;
    Context *parent = nullptr;
    Position *entry_pos = nullptr;
    SymbolTable *symbol_table = nullptr;

    Context(std::string display_name)
            : display_name(display_name) {}
};
