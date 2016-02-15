//
// Created by luca on 22/12/15.
//

#ifndef SPM_PROJECT_TOKEN_H
#define SPM_PROJECT_TOKEN_H

#include <memory>

using namespace std;
class Token {

//    Token(const Token &) = delete;

   // Token &operator=(Token const &) = delete;


    //static int _ID;

protected:

    bool _ready;
    int _id;

public:
    const int &id;
    const bool &ready;

    Token() : ready(_ready), id(_id), _id(-1){};

    Token(int name, bool r = false) : ready(_ready), id(_id),
                                      _ready(r), _id(name) { }

    Token(Token &t) : ready(_ready), id(_id),
                            _ready(t._ready), _id(t._id) { }

    Token(const Token &t) : ready(_ready), id(_id),
                            _ready(t._ready), _id(t._id) { }

    Token(Token &&t) : ready(_ready), id(_id),
                      _ready(move(t._ready)), _id(move(t._id)) { }

    Token &operator=(Token const &t){
        Token res(t);
        return res;
    }

};

template<class T>
class Token_value : public Token {

   // Token_value(const Token_value &) = delete;

    Token_value &operator=(Token_value const &) = delete;

    T _value;

public:
    // ~Token_value(){};

    Token_value(int name) : Token(name), value(_value) { }

    Token_value(int name, T v) : Token(name, true), value(_value), _value(v) { }

    Token_value(Token_value &t) : Token(t.id),
                                        value(_value),
                                        _value(t.value) {
        _ready = t.ready;
        _id = t.id;
    }

    Token_value(Token_value &&t) : Token(move(t.id)),
                                  value(_value),
                                  _value(move(t.value)) {
        _ready = move(t.ready);
        _id = move(t.id);
    }

    const T &value;

    void set(T v) {
        _value = v;
        _ready = true;
    }
};

#endif //SPM_PROJECT_TOKEN_H
