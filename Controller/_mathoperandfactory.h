#ifndef _MATHOPERANDFACTORY_H
#define _MATHOPERANDFACTORY_H
#include "mathoperand.h"
#include <map>
#include "mathfinaloperands.h"
#include "mathbinaryoperands.h"
#include "mathunaryoperands.h"


template<typename idType, typename creatorFunction>
class _MathOperandFactory
{
public:
    bool registerElement(idType id, creatorFunction function){
        fMap[id] = function;
        return isRegistred(id);
    }
    bool unregisterElement(idType id){
        return fMap.erase(id);
    }

    template<class... args>
    MathOperand &createOperand(idType id, args... arg){
        typename factoryMap::const_iterator i = fMap.find(id);
        if (i != fMap.end())
        {
            return (i->second)(arg...);
        }
    }

    bool isRegistred(idType id){
        typename factoryMap::const_iterator i = fMap.find(id);
        if (i != fMap.end())
        {
            return true;
        }
        return false;
    }

    static _MathOperandFactory<idType, creatorFunction> *getInstance(){
        if (instance == nullptr){
            new _MathOperandFactory<idType, creatorFunction>();
        }
        return instance;
    }
private:
    static _MathOperandFactory<idType, creatorFunction> *instance;
    typedef std::map<idType, creatorFunction> factoryMap;
    factoryMap fMap;

    _MathOperandFactory<idType, creatorFunction>()
    {
        _MathOperandFactory<idType, creatorFunction>::instance = this;
    }

    ~_MathOperandFactory<idType, creatorFunction>()
    {
        _MathOperandFactory<idType, creatorFunction>::instance = nullptr;
    }
};

template<typename idType, typename creatorFunction>
_MathOperandFactory<idType, creatorFunction> *(_MathOperandFactory<idType, creatorFunction>::instance) = nullptr;

class _MathArg_{
public:
    union {
        struct{
            MathOperand *arg0;
            MathOperand *arg1;
        };
        unsigned int id;
        MathOperand *arg;
        double value;
    };
    std::string _sym;

    explicit _MathArg_(std::tuple<MathOperand *, MathOperand *> tArgs){std::tie(this->arg0, this->arg1) = tArgs;}
    explicit _MathArg_(MathOperand * _arg0, MathOperand * _arg1){
        arg0 = _arg0;
        arg1 = _arg1;
    }
    template<typename... T>
    static _MathArg_ *getArgs(T... t){
        _MathArg_ *toRet = new _MathArg_(t...);
        return toRet;
    }
private:
    explicit _MathArg_(MathOperand * _arg){arg = _arg;}
    explicit _MathArg_(std::tuple<MathOperand *>_arg){std::tie(arg) = _arg;}
    explicit _MathArg_(int _id, std::string _s = ""){id = static_cast<unsigned int>(_id); _sym = _s;}
    explicit _MathArg_(std::tuple<int, std::string> _id){std::tie(id, _sym) = _id;}
    explicit _MathArg_(double _value){value = _value;}
    explicit _MathArg_(std::tuple<double> _value){std::tie(value) = _value;}
    explicit _MathArg_(std::vector<MathOperand *> _vector){
        if(_vector.size() == 1) arg = _vector[0];
        else {
            arg0 = _vector[0];
            arg1 = _vector[1];
        }
    }


};



#endif // _MATHOPERANDFACTORY_H
