#include "CPathfindInfoIntraTileSuccessors.hpp"
#include "API/Functions.hpp"
#include "Platform/ASLR.hpp"

namespace NWNXLib {

namespace API {

CPathfindInfoIntraTileSuccessors::CPathfindInfoIntraTileSuccessors(const CPathfindInfoIntraTileSuccessors&)
{
     // This is an auto-generated stub. You probably shouldn't use it.
}

CPathfindInfoIntraTileSuccessors& CPathfindInfoIntraTileSuccessors::operator=(const CPathfindInfoIntraTileSuccessors&)
{
    return *this; // This is an auto-generated stub. You probably shouldn't use it.
}

CPathfindInfoIntraTileSuccessors::CPathfindInfoIntraTileSuccessors()
{
    CPathfindInfoIntraTileSuccessors__CPathfindInfoIntraTileSuccessorsCtor(this);
}

void CPathfindInfoIntraTileSuccessors__CPathfindInfoIntraTileSuccessorsCtor(CPathfindInfoIntraTileSuccessors* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CPathfindInfoIntraTileSuccessors*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CPathfindInfoIntraTileSuccessors__CPathfindInfoIntraTileSuccessorsCtor);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr);
}

}

}
