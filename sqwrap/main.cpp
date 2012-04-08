/* 
 * File:   main.cpp
 * Author: yuryb
 *
 * Created on March 23, 2012, 11:48 PM
 */

#include "SqWrap.h"

#include <cstdlib>
#include <cstdio>

using namespace std;

class MyClsA {
public:
    MyClsA() : number(-123) {
        printf("Created MyClsA\n");
    }
    
    ~MyClsA() {
        printf("Destructed MyClsA\n");
    }
    
    int GetNumber() {
        return number;
    }
    
    void SetNumber(int i) {
        number = i;
    }
    
protected:
    int number;
};


static SQInteger InstanceReleaseHook(SQUserPointer p, SQInteger size) {
    MyClsA * inst = (MyClsA*)p;
    delete inst;
    return 1;
}
static SQInteger Constructor(HSQUIRRELVM v) {
    MyClsA * inst = new MyClsA;
    
    sq_setinstanceup(v, -1, (SQUserPointer)inst);
    sq_setreleasehook(v, -1, &InstanceReleaseHook);
    return 0;
}

static SQInteger MyClsA_GetNumber(HSQUIRRELVM v) {
    SQUserPointer p;
    sq_getinstanceup(v, -1, &p, 0);
    
    MyClsA * inst = (MyClsA*)p;
    
    sq_pushinteger(v, inst->GetNumber());
    return 1;
}

static SQInteger MyClsA_SetNumber(HSQUIRRELVM v) {
    SQUserPointer p;
    sq_getinstanceup(v, 1, &p, 0);
    
    MyClsA * inst = (MyClsA*)p;
    
    SQInteger i;
    sq_getinteger(v, 2, &i);
    
    inst->SetNumber(i);
    return 0;
}

void AddMethod(HSQUIRRELVM vm, SQChar * name, SQChar * nativeName, 
        SQFUNCTION func, bool isStatic, int params, SQChar * typemask)
{
    sq_pushstring(vm, name, -1);
    sq_newclosure(vm, func, 0);
    sq_setparamscheck(vm, params, typemask);
    sq_setnativeclosurename(vm, -1, nativeName);
    sq_newslot(vm, -3, isStatic);
}

void CreateClass(HSQUIRRELVM vm) {
    sq_pushroottable(vm);
    sq_pushstring(vm, "MyClsA", -1);
    sq_newclass(vm, SQFalse);
    
    // declare default constructor
    sq_pushstring(vm, "constructor", -1);
    sq_newclosure(vm, &Constructor, 0);
    sq_newslot(vm, -3, SQFalse);

    // declare members
    sq_pushstring(vm, "GetNumber", -1);
    sq_newclosure(vm, &MyClsA_GetNumber, 0);
    sq_newslot(vm, -3, SQFalse);
    
    sq_pushstring(vm, "SetNumber", -1);
    sq_newclosure(vm, &MyClsA_SetNumber, 0);
    sq_newslot(vm, -3, SQFalse);

    
    // now finally add the class to the table
    sq_newslot(vm, -3, SQFalse); // root table stack index
    
    
    // pop root table
    sq_pop(vm, 1);
}

/*
 * 
 */
int main(int argc, char** argv) {
    SqWrap w;
    
    CreateClass(w.GetVM());
    
    w.DoFile("test1.nut");

    return 0;
}

