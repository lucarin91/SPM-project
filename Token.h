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

    bool _ready;
    int _id;

public:
    const int &id;
    const bool &ready;

    //~Token(){};

    Token(int name, bool r = false) : ready(_ready), id(_id),
                                      _ready(r), _id(name) { }

    Token(const Token &t) : ready(_ready), id(_id),
                            _ready(t._ready), _id(t._id) { }

};

template<class T>
class Token_value : public Token {

    Token_value(Token_value &) = delete;

    Token_value &operator=(Token_value const &) = delete;

    T _value;

public:
    // ~Token_value(){};

    Token_value(int name) : Token(name), value(_value) { }

    Token_value(int name, T v) : Token(name, true), value(_value), _value(v) { }

    Token_value(const Token_value &t) : Token(t.id),
                                        value(_value),
                                        _value(t.value) {
        _ready = t.ready;
        _id = t.id;
    }

    const T &value;

    void set(T v) {
        _value = v;
        _ready = true;
    }
};

#endif //SPM_PROJECT_TOKEN_H
