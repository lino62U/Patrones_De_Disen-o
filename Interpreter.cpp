#include "iostream"
using namespace std;
constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
class Context
{
    private:
        string _nextOp = "";
        int _operator = 0;
        int _result = 0;
    public:
        int getInteger(string input)
        {
            const char *str = input.c_str();
            for (size_t i = 0; i < strlen(str); ++i) {
                printf("%c", tolower((unsigned char) str[i]));
            }
            switch (str2int(str))
            {
                case str2int("cero"):{return 0;}
                case str2int("uno"):{return 1;}
                case str2int("dos"):{return 2;}
                case str2int("tres"):{return 3;}
                case str2int("cuatro"):{return 4;}
                case str2int("cinco"):{return 5;}
                case str2int("seis"):{return 6;}
                case str2int("siete"):{return 7;}
                case str2int("ocho"):{return 8;}
                case str2int("nueve"):{return 9;}
                default:{ return -1;}
            }
        }

        void setOperator(int op)
        {
            _operator = op;
        }

        void setOperation(string operation)
        {
            const char *str = operation.c_str();
            for (size_t i = 0; i < strlen(str); ++i) {
                printf("%c", tolower((unsigned char) str[i]));
            }
            if (str == "mas")
            {
                _nextOp = "+";
            }
            else if (str == "menos")
            {
                _nextOp = "-";
            }
        }

        void calculate()
        {
            if (_nextOp == "+" || _nextOp == "")
            {
                _result += _operator;
            }
            else if (_nextOp == "-")
            {
                _result -= _operator;
            }
        }

        int getResult()
        {
            return _result;
        }
};

class IExpression
{
    virtual void interpret(Context context) = 0;
};

class NumericExpression : IExpression
{
    private:
        string _value;
    public:
        NumericExpression(string token)
        {
            _value = token;
        }
        void interpret(Context context)
        {
            context.setOperator(context.getInteger(_value));
            context.calculate();
        }
};
class OperatorExpression : IExpression
{
    private:
        string _operation;
    public:
        OperatorExpression(string token)
        {
            _operation = token;
        }
        void interpret(Context context)
        {
            context.setOperation(_operation);
        }
};
