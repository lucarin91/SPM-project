//
// Created by luca on 22/12/15.
//

#ifndef SPM_PROJECT_TOKEN_H
#define SPM_PROJECT_TOKEN_H

class Token {

    Token(Token const &) = delete;

    Token &operator=(Token const &) = delete;

    static int ID = 0;

protected:

    bool _ready;
    int _id;

public:
    const int &id;
    const bool &ready;

    Token(bool r = false) : ready(_ready), id(_id),
                            _ready(r), _id(Token::ID++) { }

    Token(Token &t) : ready(_ready), id(_id),
                      _ready(t._ready), _id(t._id) { }
};

template<class T>
class Token_value : Token {

    Token_value(Token_value const &) = delete;

    Token_value &operator=(Token_value const &) = delete;

    T _value;

public:

    Token_value() : Token(), value(_value) { }

    Token_value(T v) : Token(false), value(_value), _value(v) { }

    Token_value(Token_value &t) : Token(), value(_value), _ready(t._ready), _id(t._id), _value(t._value) { }

    const T &value;

    void set(T v) { _value = v; }
};

//Token::ID = 0;

#endif //SPM_PROJECT_TOKEN_H
