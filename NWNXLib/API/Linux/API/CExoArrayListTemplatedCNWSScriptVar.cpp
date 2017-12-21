#include "CExoArrayListTemplatedCNWSScriptVar.hpp"
#include "API/Functions.hpp"
#include "Platform/ASLR.hpp"

#include "CNWSScriptVar.hpp"

namespace NWNXLib {

namespace API {

CExoArrayListTemplatedCNWSScriptVar::CExoArrayListTemplatedCNWSScriptVar()
{
     // This is an auto-generated stub. You probably shouldn't use it.
}

CExoArrayListTemplatedCNWSScriptVar::CExoArrayListTemplatedCNWSScriptVar(const CExoArrayListTemplatedCNWSScriptVar&)
{
     // This is an auto-generated stub. You probably shouldn't use it.
}

CExoArrayListTemplatedCNWSScriptVar& CExoArrayListTemplatedCNWSScriptVar::operator=(const CExoArrayListTemplatedCNWSScriptVar&)
{
    return *this; // This is an auto-generated stub. You probably shouldn't use it.
}

CExoArrayListTemplatedCNWSScriptVar::~CExoArrayListTemplatedCNWSScriptVar()
{
    CExoArrayListTemplatedCNWSScriptVar__CExoArrayListTemplatedCNWSScriptVarDtor(this);
}

void CExoArrayListTemplatedCNWSScriptVar::Allocate(int32_t a0)
{
    return CExoArrayListTemplatedCNWSScriptVar__Allocate(this, a0);
}

void CExoArrayListTemplatedCNWSScriptVar__CExoArrayListTemplatedCNWSScriptVarDtor(CExoArrayListTemplatedCNWSScriptVar* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoArrayListTemplatedCNWSScriptVar*, int);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoArrayListTemplatedCNWSScriptVar__CExoArrayListTemplatedCNWSScriptVarDtor);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, 2);
}

void CExoArrayListTemplatedCNWSScriptVar__Allocate(CExoArrayListTemplatedCNWSScriptVar* thisPtr, int32_t a0)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoArrayListTemplatedCNWSScriptVar*, int32_t);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoArrayListTemplatedCNWSScriptVar__Allocate);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    return func(thisPtr, a0);
}

}

}
