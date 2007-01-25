/**
 * ===============================================================
 * SourceMod (C)2004-2007 AlliedModders LLC.  All rights reserved.
 * ===============================================================
 *
 * This file is not open source and may not be copied without explicit
 * written permission of AlliedModders LLC.  This file may not be redistributed 
 * in whole or significant part.
 * For information, see LICENSE.txt or http://www.sourcemod.net/license.php
 *
 * Version: $Id$
 */

#include <sp_vm_api.h>
#include <malloc.h>
#include "jit_x86.h"
#include "dll_exports.h"

SourcePawn::ISourcePawnEngine *engine = NULL;
JITX86 jit;

EXPORTFUNC int GiveEnginePointer(SourcePawn::ISourcePawnEngine *engine_p)
{
	engine = engine_p;

	return 0;
}

EXPORTFUNC unsigned int GetExportCount()
{
	return 1;
}

EXPORTFUNC SourcePawn::IVirtualMachine *GetExport(unsigned int exportnum)
{
	/* Don't return anything if we're not initialized yet */
	if (!engine)
	{
		return NULL;
	}

	/* We only have one export - 0 */
	if (exportnum)
	{
		return NULL;
	}

	return &jit;
}

#if defined __linux__
extern "C" void __cxa_pure_virtual(void)
{
}

void *operator new(size_t size)
{
	return malloc(size);
}

void *operator new[](size_t size) 
{
	return malloc(size);
}

void operator delete(void *ptr) 
{
	free(ptr);
}

void operator delete[](void * ptr)
{
	free(ptr);
}
#endif

