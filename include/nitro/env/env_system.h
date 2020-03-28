/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include - ENV
  File:     env_system.h

  Copyright 2005,2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: env_system.h,v $
  Revision 1.5  2006/12/18 01:30:35  kitase_hirotake
  Added cast

  Revision 1.4  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.3  2005/10/13 00:23:11  kitase_hirotake
  add ENV_SetResoruceSetArray

  Revision 1.2  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.1  2005/09/05 01:19:10  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_ENV_SYSTEM_H_
#define NITRO_ENV_SYSTEM_H_

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#include "nitro.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//================================================================================
//---- limitation of name length
#define ENV_CLASS_NAME_MAX		64
#define ENV_MEMBER_NAME_MAX		64

//---- resource type mask
#define ENV_RESTYPE_RES_MASK		0xff
#define ENV_RESTYPE_OFFSET_MASK		0x100

//---- resource type
#define ENV_RESTYPE_NONE		((ENVType)0x0)
#define ENV_RESTYPE_STRING		((ENVType)0x1)
#define ENV_RESTYPE_BINARY		((ENVType)0x2)
#define ENV_RESTYPE_S8			((ENVType)0x3)
#define ENV_RESTYPE_U8			((ENVType)0x4)
#define ENV_RESTYPE_S16			((ENVType)0x5)
#define ENV_RESTYPE_U16			((ENVType)0x6)
#define ENV_RESTYPE_S32			((ENVType)0x7)
#define ENV_RESTYPE_U32			((ENVType)0x8)
#define ENV_RESTYPE_BOOL		((ENVType)0x9)
#define ENV_RESTYPE_S64			((ENVType)0xa)
#define ENV_RESTYPE_U64			((ENVType)0xb)
#define ENV_RESTYPE_OFFSET_STRING	((ENVType)(ENV_RESTYPE_OFFSET_MASK | ENV_RESTYPE_STRING))       // 0x101
#define ENV_RESTYPE_OFFSET_BINARY	((ENV_RESTYPE_OFFSET_MASK | ENV_RESTYPE_BINARY))        // 0x102
#define ENV_RESTYPE_OFFSET_S64		((ENVType)(ENV_RESTYPE_OFFSET_MASK | ENV_RESTYPE_S64))  // 0x10a
#define ENV_RESTYPE_OFFSET_U64		((ENVType)(ENV_RESTYPE_OFFSET_MASK | ENV_RESTYPE_U64))  // 0x10b

#define ENVi_RESTYPE_U64HALF	100    // For system. Don't use this.
#define ENVi_RESTYPE_LINK		255     // For resource array link. Don't use this.


#define ENVi_DUMMY_FOR_U64	"@DUMMY@"

//---- for description resource value
#define ENV_STRING(X) sizeof(X),    ENV_RESTYPE_STRING, (void*)(X)
#define ENV_BINARY(X) sizeof(X)-1,  ENV_RESTYPE_BINARY, (void*)(X)
#define ENV_S8(X)     sizeof(s8),   ENV_RESTYPE_S8, 	(void*)(X)
#define ENV_U8(X)     sizeof(u8),   ENV_RESTYPE_U8, 	(void*)(X)
#define ENV_S16(X)    sizeof(s16),  ENV_RESTYPE_S16, 	(void*)(X)
#define ENV_U16(X)    sizeof(u16),  ENV_RESTYPE_U16, 	(void*)(X)
#define ENV_S32(X)    sizeof(s32),  ENV_RESTYPE_S32, 	(void*)(X)
#define ENV_U32(X)    sizeof(u32),  ENV_RESTYPE_U32, 	(void*)(X)
#define ENV_BOOL(X)   sizeof(BOOL), ENV_RESTYPE_BOOL, 	(void*)(X)

#define ENV_S64(X)    sizeof(u32),  ENV_RESTYPE_S64, 	(void*)((X)&0xffffffff), \
			ENVi_DUMMY_FOR_U64, sizeof(u32),	ENVi_RESTYPE_U64HALF, (void*)((X)>>32)

#define ENV_U64(X)    sizeof(u32),  ENV_RESTYPE_U64, 	(void*)((X)&0xffffffff), \
			ENVi_DUMMY_FOR_U64, sizeof(u32),	ENVi_RESTYPE_U64HALF, (void*)((X)>>32)

//---- start / end mark of resource set
#define ENV_RESOURCE_START { NULL, 0, ENVi_RESTYPE_LINK, NULL }
#define ENV_RESOURCE_END   { NULL, 0, ENV_RESTYPE_NONE, NULL }

//---- max resource set to register
#define ENV_RESOURCE_SET_MAX	8

//---- typedef
typedef u16 ENVType;

//---- resource struct
typedef struct ENVResource ENVResource;
struct ENVResource
{
    char   *name;
    u16     len;
    ENVType type;
    void   *ptr;
};

//---- resource set
typedef struct ENVResourceSetLink ENVResourceSetLink;
struct ENVResourceSetLink
{
    ENVResourceSetLink *next;
    ENVResource *array;
};

//---- resource iterator
typedef struct ENVResourceIter ENVResourceIter;
struct ENVResourceIter
{
    ENVResourceSetLink *link;
    ENVResource *ptr;
    int     count;

    void   *supData;
};

//================================================================================
//      Convenience functions
//================================================================================
static inline char *ENV_GetResourceName(ENVResource * res)
{
    return res->name;
}
static inline u16 ENV_GetResourceLen(ENVResource * res)
{
    return res->len;
}
static inline ENVType ENV_GetResourceType(ENVResource * res)
{
    return res->type;
}
static inline void *ENV_GetResourcePtr(ENVResource * res)
{
    return res->ptr;
}

//================================================================================
//      Initialize and Setting
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         ENV_Init

  Description:  Initialize EnvSystem

  Arguments:    resSet : pointer to resource array

  Returns:      None.
 *---------------------------------------------------------------------------*/
//extern void ENV_Init( ENVResource* resSet );
extern void ENV_Init(void);

/*---------------------------------------------------------------------------*
  Name:         ENV_AppendResourceSet

  Description:  append resource set

  Arguments:    resSet : pointer to resource array

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_AppendResourceSet(ENVResource * resSet);

/*---------------------------------------------------------------------------*
  Name:         ENV_PrependResourceSet

  Description:  prepend resource set

  Arguments:    resSet : pointer to resource array

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_PrependResourceSet(ENVResource * resSet);

/*---------------------------------------------------------------------------*
  Name:         ENV_InsertResourceSet

  Description:  insert resource set

  Arguments:    standardResSet : pointer to standard resource array
                resSet         : pointer to resource array

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_InsertResourceSet(ENVResource * standardResSet, ENVResource * resSet);

/*---------------------------------------------------------------------------*
  Name:         ENV_SetResourceSet

  Description:  set new resource array

  Arguments:    resSet : pointer to resource set

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_SetResourceSet(ENVResource * resSet);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetResourceSetLinkHead

  Description:  get pointer to first resource set

  Arguments:    None.

  Returns:      pointer to first resource set link
 *---------------------------------------------------------------------------*/
extern ENVResourceSetLink *ENV_GetResourceSetLinkHead(void);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetNextResourceSet

  Description:  get next link resource link of specified resource link

  Arguments:    link: resource set link.

  Returns:      next resource set link
 *---------------------------------------------------------------------------*/
extern ENVResourceSetLink *ENV_GetNextResourceSet(ENVResourceSetLink * link);

//================================================================================
//      Class
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         ENV_SetClass

  Description:  set current class.
                this value is used to omit the class name
                in getting the resource value.

  Arguments:    className : pointer to resource set

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_SetClass(const char *className);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetClass

  Description:  get current class.

  Arguments:    None.

  Returns:      pointer to current class name
 *---------------------------------------------------------------------------*/
extern char *ENV_GetClass(void);

//================================================================================
//      Search
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         ENVi_SearchByMemberName

  Description:  search a resource by specifying member name.
  				use current class name.
				get pointer to resource set.

  Arguments:    memberName : member name
                resSetPtr  : pointer to resource set

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENVi_SearchByMemberName(const char *memberName, ENVResource ** resSetPtr);

/*---------------------------------------------------------------------------*
  Name:         ENV_SearchByMemberName

  Description:  search a resource by specifying member name.
  				use current class name.

  Arguments:    memberName : member name

  Returns:      pointer to specified resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
static inline ENVResource *ENV_SearchByMemberName(const char *memberName)
{
    return ENVi_SearchByMemberName(memberName, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         ENVi_SearchByFullName

  Description:  search a resource by specifying full name.
				get pointer to resource set.

  Arguments:    fullName : name (full name)
                resSetPtr  : pointer to resource set

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENVi_SearchByFullName(const char *fullName, ENVResource ** resSetPtr);

/*---------------------------------------------------------------------------*
  Name:         ENV_SearchByFullName

  Description:  search a resource by specifying full name.

  Arguments:    fullName : name (full name)

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
static inline ENVResource *ENV_SearchByFullName(const char *fullName)
{
    return ENVi_SearchByFullName(fullName, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         ENVi_Search

  Description:  search a resource by specifying name.
                if name begins by ".", it will be added to current class
				get pointer to resource set.

  Arguments:    name       : full name or member name of class
                resSetPtr  : pointer to resource set

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENVi_Search(const char *name, ENVResource ** resSetPtr);

/*---------------------------------------------------------------------------*
  Name:         ENV_Search

  Description:  search a resource by specifying name from all resoruce set.
                if name begins by ".", it will be added to current class

  Arguments:    name (full name or member name of class)

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
static inline ENVResource *ENV_Search(const char *name)
{
    return ENVi_Search(name, NULL);
}


//================================================================================
//      Get value
//================================================================================
//---- internal function
extern void *ENVi_GetPtrAndLength(const char *name, int *len);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetPtr

  Description:  get resource pointer
                data length is stored to len.

  Arguments:    name : full name or member name of class
                len  : pointer to length

  Returns:      pointer
 *---------------------------------------------------------------------------*/
static inline void *ENV_GetPtr(const char *name)
{
    return ENVi_GetPtrAndLength(name, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         ENV_GetType

  Description:  get resource type

  Arguments:    name : full name or member name of class

  Returns:      resource type. ENV_RESTYPE_xxx.
 *---------------------------------------------------------------------------*/
extern ENVType ENV_GetType(const char *name);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetSize

  Description:  get resource size

  Arguments:    name : full name or member name of class

  Returns:      resource size
 *---------------------------------------------------------------------------*/
extern int ENV_GetSize(const char *name);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetBelogingResourceSet

  Description:  get resource set which res is belong to

  Arguments:    res : pointer to resource

  Returns:      pointer to resoruce set
 *---------------------------------------------------------------------------*/
extern ENVResource *ENV_GetBelongingResourceSet(ENVResource * res);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetString / GetStringAndLength

  Description:  get pointer of specified member name.

  Arguments:    name   : full name or member name of class
  				retPtr : pointer to pointer to resource string data
                len    : length of string data

  Returns:      TRUE if got. FALSE if never exist.
 *---------------------------------------------------------------------------*/
static inline BOOL ENV_GetString(const char *name, char **retPtr)
{
    char   *strPtr = (char *)ENV_GetPtr(name);
    *retPtr = strPtr;
    return (strPtr != NULL);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetStringAndLength(const char *name, char **retPtr, int *len)
{
    char   *strPtr = (char *)ENVi_GetPtrAndLength(name, len);
    *retPtr = strPtr;
    return (strPtr != NULL);
}

/*---------------------------------------------------------------------------*
  Name:         ENV_GetBinary / GetBinaryAndSize

  Description:  get pointer of specified member name.

  Arguments:    name   : full name or member name of class
  				retPtr : pointer to pointer to resource binary data
                size   : length of binary data

  Returns:      TRUE if got. FALSE if never exist.
 *---------------------------------------------------------------------------*/
static inline BOOL ENV_GetBinary(const char *name, void **retPtr)
{
    void   *binPtr = (void *)ENV_GetPtr(name);
    *retPtr = binPtr;
    return (binPtr != NULL);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetBinaryAndSize(const char *name, void **retPtr, int *size)
{
    void   *binPtr = (void *)ENVi_GetPtrAndLength(name, size);
    *retPtr = binPtr;
    return (binPtr != NULL);
}

/*---------------------------------------------------------------------------*
  Name:         ENV_GetU8 / S8 / U16 / S16 / U32 / S32 / BOOL

  Description:  get value of the specified resource

  Arguments:    name   : full name or member name of class
                retVal : pointer to store resource value

  Returns:      TRUE if got. FALSE if never exist.
 *---------------------------------------------------------------------------*/
static inline BOOL ENV_GetU8(const char *name, u8 *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (u8)val;
        return TRUE;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetS8(const char *name, s8 *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (s8)val;
        return TRUE;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetU16(const char *name, u16 *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (u16)val;
        return TRUE;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetS16(const char *name, s16 *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (s16)val;
        return TRUE;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetU32(const char *name, u32 *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (u32)val;
        return TRUE;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetS32(const char *name, s32 *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (s32)val;
        return TRUE;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetBOOL(const char *name, BOOL *retVal)
{
    int     len;
    u32     val = (u32)ENVi_GetPtrAndLength(name, &len);
    if (!len)
    {
        return FALSE;
    }
    else
    {
        *retVal = (BOOL)(val ? TRUE : FALSE);
        return TRUE;
    }
}

/*---------------------------------------------------------------------------*
  Name:         ENV_GetU64 / S64

  Description:  get value of the specified resource

  Arguments:    name   : full name or member name of class
                retVal : pointer to store resource value

  Returns:      resource value
 *---------------------------------------------------------------------------*/
extern BOOL ENV_GetU64(const char *name, u64 *retVal);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline BOOL ENV_GetS64(const char *name, s64 *retVal)
{
    return ENV_GetU64(name, (u64 *)retVal);
}

//================================================================================
//    search by using iterator
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         ENV_InitIter

  Description:  Initialize iterator

  Arguments:    iter : pointer to iterator

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_InitIter(ENVResourceIter * iter);

/*---------------------------------------------------------------------------*
  Name:         ENV_SearchByClass

  Description:  search resource which has specified class

  Arguments:    iter      : pointer to iterator
                className : class name

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENV_SearchByClass(ENVResourceIter * iter, const char *className);

/*---------------------------------------------------------------------------*
  Name:         ENV_SearchByMember

  Description:  search resource which has specified member

  Arguments:    iter       : pointer to iterator
                memberName : member name

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENV_SearchByMember(ENVResourceIter * iter, const char *memberName);

/*---------------------------------------------------------------------------*
  Name:         ENV_SearchByType

  Description:  search resource which is specified type

  Arguments:    iter : pointer to iterator
                type : resource type

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENV_SearchByType(ENVResourceIter * iter, ENVType type);

/*---------------------------------------------------------------------------*
  Name:         ENV_SearchByPartialName

  Description:  search resource whose name contains specified string

  Arguments:    iter        : pointer to iterator
                partialName : string to search in resource name

  Returns:      pointer to resource.
                NULL if not found.
 *---------------------------------------------------------------------------*/
extern ENVResource *ENV_SearchByPartialName(ENVResourceIter * iter, const char *partialName);

/*---------------------------------------------------------------------------*
  Name:         ENV_SetResoruceSetArray

  Description:  insert all resoruce set

  Arguments:    array : pointer to resource array array

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void ENV_SetResoruceSetArray(ENVResource * array[]);

/*---------------------------------------------------------------------------*
  Name:         ENV_GetLastResourceSetFromIter

  Description:  get last resource set from iter

  Arguments:    iter : pointer to iterator

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline ENVResource *ENV_GetLastResourceSetFromIter(ENVResourceIter * iter)
{
    SDK_ASSERT(iter);
    return (iter->link) ? iter->link->array : NULL;
}


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_ENV_SYSTEM_H_ */
#endif
