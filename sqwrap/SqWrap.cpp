/* 
 * File:   SqWrap.cpp
 * Author: yuryb
 * 
 * Created on March 23, 2012, 11:56 PM
 */

#include "SqWrap.h"

#include <stdarg.h>
#include <stdio.h>

#include "sqstdaux.h"
#include "sqstdio.h"

#ifdef SQUNICODE 
#define scvprintf vfwprintf
#else 
#define scvprintf vfprintf
#endif 

static void printfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	scvprintf(stdout, s, vl);
	va_end(vl);
}

static void errorfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	scvprintf(stderr, s, vl);
	va_end(vl);
}

SqWrap::SqWrap() {
    vm = sq_open(1024);
    sqstd_seterrorhandlers(vm);
    sq_setprintfunc(vm, printfunc, errorfunc);
}


SqWrap::~SqWrap() {
    sq_close(vm);
}

void SqWrap::DoFile(const SQChar * fn) {
    sq_pushroottable(vm);
    sqstd_dofile(vm, fn, SQFalse, SQTrue);
}


SQInteger SqWrap::InstanceReleaseHook(SQUserPointer p, SQInteger size)
{
    ClassUserData * pData = (ClassUserData*)p;
    IWrapClassDecl * clsDecl = pData->classDecl;
    
    clsDecl->FreeInstance(pData->classInstance);
    return 1;
}

SQInteger SqWrap::Constructor(HSQUIRRELVM v) {
    // TODO get class user pointer
    IWrapClassDecl * clsDecl = NULL;
    
    void * p = clsDecl->NewInstance();
    
    // TODO store user pointer
            
    return 0;
}
