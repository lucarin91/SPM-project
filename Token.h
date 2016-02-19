//
// Created by luca on 22/12/15.
//

#ifndef SPM_PROJECT_TOKEN_H
#define SPM_PROJECT_TOKEN_H

class Token {

    Token(Token &) = delete;

    Token &operator=(Token const &) = delete;

    //static int _ID;

protected:

    int _type;

public:
    const int &type;

    //~Token(){};

    Token() : Token(-1) { }

    Token(int t) : type(_type), _type(t) { }

    Token(const Token &t) : type(_type), _type(t._type) { }

    void set_type(int t) {
        _type = t;
    }

};

template<class T>
class T_value : public Token {

    T_value(T_value &) = delete;

    T_value &operator=(T_value const &) = delete;

    T _value;

public:
    // ~T_value(){};

    T_value() : Token(), value(_value) { }

    T_value(int t, T v) : Token(t), value(_value), _value(v) { }

    T_value(T v) : Token(true), value(_value), _value(v) { }

    T_value(const T_value &t) : Token(t.type),
                                value(_value),
                                _value(t.value) {
        _type = t.type;
    }

    const T &value;

    void set(T v) {
        _value = v;
    }
};

#endif //SPM_PROJECT_TOKEN_H
