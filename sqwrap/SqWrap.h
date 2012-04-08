/* 
 * File:   SqWrap.h
 * Author: yuryb
 *
 * Created on March 23, 2012, 11:56 PM
 */

#ifndef SQWRAP_H
#define	SQWRAP_H

#include "squirrel.h"

class SqWrap {
public:
    SqWrap();
    virtual ~SqWrap();
    
    HSQUIRRELVM GetVM() {
        return vm;
    }
    
    void DoFile(const SQChar * fn);
    
    struct ScriptClassMemberDecl  {
        const SQChar *name;
        SQFUNCTION func;
        int params;
        const SQChar *typemask;
    };

    struct ScriptClassDecl  {
        const SQChar *name;
        const SQChar *base;
        const ScriptClassMemberDecl *members;
    };
    
    // python-generated code will use it to register class
    void RegisterClass( const SQChar * name,
                        const ScriptClassDecl * decl, 
                        SQRELEASEHOOK hook);
    
    ///////////////////
    
    struct IWrapClassDecl {
        virtual void * NewInstance() = 0;
        virtual void FreeInstance(void * p) = 0;
    };
    
    template <class T> struct WrapClassDecl : IWrapClassDecl {
        virtual void * NewInstance() {
            return (void*)new T();
        }
        virtual void FreeInstance(void * p) {
            T * pc = (T*)p;
            delete pc;
        }
    }; 
    
    
private:
    HSQUIRRELVM vm;

    
    // 1) push new class
    //   a) register class
    //   b) set user data to IWrapClassDecl*
    // 2) push constructor 
    // 3) in constructor native closure: 
    //   a) allocated and set user pointer
    //   b) set release hook

//    void PushNewClass(const SQChar * name, );
    
    struct ClassUserData {
        IWrapClassDecl * classDecl;
        void * classInstance;
    };
    
    // TODO deprecate
    static SQInteger InstanceReleaseHook(SQUserPointer p, SQInteger size);
    static SQInteger Constructor(HSQUIRRELVM v);


};

#endif	/* SQWRAP_H */

