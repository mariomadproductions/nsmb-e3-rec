#pragma once

// Included by exactly one source file of each runtime module that holds
// objects. It brings in the table nsmbtool generated for the module, which is
// what Glue reads when the module is loaded.
//
// NCPatcher defines NCP_RUNTIME_MODULE to the module's name when compiling its
// code, and only then.

#ifndef NCP_RUNTIME_MODULE
#error "glue/runtime_module.hpp is only for code in a runtime module (an arm9(rt:<name>) target)."
#endif

#define GLUE_RUNTIME_STR_(x) #x
#define GLUE_RUNTIME_STR(x) GLUE_RUNTIME_STR_(x)

#include GLUE_RUNTIME_STR(generated/glue/runtime/NCP_RUNTIME_MODULE.hpp)

#undef GLUE_RUNTIME_STR
#undef GLUE_RUNTIME_STR_
