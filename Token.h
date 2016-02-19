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
    int _type;

public:
    const int &type;
    const bool &ready;

    //~Token(){};

    Token(bool r = false) : Token(-1, r) { }

    Token(int name, bool r = false) : ready(_ready), type(_type),
                                      _ready(r), _type(name) { }

    Token(const Token &t) : ready(_ready), type(_type),
                            _ready(t._ready), _type(t._type) { }

    void set_id(int id){
        _type = id;
    }

};

template<class T>
class Token_value : public Token {

    Token_value(Token_value &) = delete;

    Token_value &operator=(Token_value const &) = delete;

    T _value;

public:
    // ~Token_value(){};

    Token_value() : Token(), value(_value) { }

    Token_value(int name, T v) : Token(name, true), value(_value), _value(v) { }

    Token_value(T v) : Token(true), value(_value), _value(v) { }

    Token_value(const Token_value &t) : Token(t.type),
                                        value(_value),
                                        _value(t.value) {
        _ready = t.ready;
        _type = t.type;
    }

    const T &value;

    void set(T v) {
        _value = v;
        _ready = true;
    }
};

#endif //SPM_PROJECT_TOKEN_H
