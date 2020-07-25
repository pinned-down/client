#pragma once

// We want to declare BlueprintCallable functions with delegate parameters. These delegates need to be dynamic.
// Then, we want to add these delegates to multicast delegates, which is not supported by Unreal's built-in dynamic multicast delegates.
// Also, we want to make sure that the invocation order is well-defined.
// So, we're building our own here, essentially as a list of dynamic delegates.

#define PDDeclareDynamicMulticastDelegate(DelegateType, DelegateName) TArray<DelegateType> DelegateName;

#define PDCreateDynamicDelegate(DelegateType, DelegateName, FunctionPointer) \
    DelegateType DelegateName; \
    DelegateName.BindDynamic(this, FunctionPointer);

#define PDBroadcastDynamicMulticastDelegate(DelegateName, Params) \
    for (const auto& __Delegate : DelegateName) \
    { \
        __Delegate.ExecuteIfBound(Params); \
    }
