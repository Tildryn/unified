#include "CExoLinkedListTemplatedCResRef.hpp"
#include "API/Functions.hpp"
#include "Platform/ASLR.hpp"

#include "CExoLinkedListInternal.hpp"

namespace NWNXLib {

namespace API {

CExoLinkedListTemplatedCResRef::CExoLinkedListTemplatedCResRef()
{
     // This is an auto-generated stub. You probably shouldn't use it.
}

CExoLinkedListTemplatedCResRef::CExoLinkedListTemplatedCResRef(const CExoLinkedListTemplatedCResRef&)
{
     // This is an auto-generated stub. You probably shouldn't use it.
}

CExoLinkedListTemplatedCResRef& CExoLinkedListTemplatedCResRef::operator=(const CExoLinkedListTemplatedCResRef&)
{
    return *this; // This is an auto-generated stub. You probably shouldn't use it.
}

CExoLinkedListTemplatedCResRef::~CExoLinkedListTemplatedCResRef()
{
    CExoLinkedListTemplatedCResRef__CExoLinkedListTemplatedCResRefDtor(this);
}

void CExoLinkedListTemplatedCResRef__CExoLinkedListTemplatedCResRefDtor(CExoLinkedListTemplatedCResRef* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoLinkedListTemplatedCResRef*, int);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoLinkedListTemplatedCResRef__CExoLinkedListTemplatedCResRefDtor);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, 2);
}

}

}
