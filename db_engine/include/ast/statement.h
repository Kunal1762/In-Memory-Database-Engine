#pragma once

enum class StatementType{
    CREATE_TABLE,
    INSERT,
    SELECT,
    DELETE
};
class Statement{
    public:
    StatementType type;
    virtual ~Statement()=default;
};