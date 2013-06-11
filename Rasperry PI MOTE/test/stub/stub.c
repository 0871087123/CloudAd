#ifdef __cplusplus
extern "C" {
#endif

#include <sys/mman.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include "stub.h"
#include <string.h>
#ifndef PAGESIZE
#define PAGESIZE 4096UL
#endif


void stub_set(fun_stub *tmp, void *func, void * func_stub)
{
	int ret;
	memcpy(tmp->data, func, 10);
	tmp->function = func;
	ret = mprotect((void *)((unsigned long)func & (~(PAGESIZE-1))), PAGESIZE * 2, PROT_READ | PROT_WRITE | PROT_EXEC );
	if (ret < 0)
	{
		perror("MM1");
		exit(0);
	}

	*(char *)func = (char)0xE9;
	*(int *)((char *)func + 1) = (int)((unsigned long)func_stub - (unsigned long)func - 5);
	ret = mprotect((void *)((unsigned long)func & (~(PAGESIZE-1))), PAGESIZE * 2, PROT_READ | PROT_WRITE | PROT_EXEC);
	if (ret < 0)
	{
		perror("MM2");
		exit(0);
	}
	return;
}

void stub_reset(fun_stub * target)
{
	int ret;
	ret = mprotect((void *)((unsigned long)target->function & (~(PAGESIZE-1))), PAGESIZE * 2, PROT_READ | PROT_WRITE | PROT_EXEC );
	if (ret < 0)
	{
		perror("resetMM1");
		exit(0);
	}
	memcpy(target->function, target->data, 10);
	ret = mprotect((void *)((unsigned long)target->function & (~(PAGESIZE-1))), PAGESIZE * 2, PROT_READ | PROT_WRITE | PROT_EXEC);
	if (ret < 0)
	{
		perror("resetMM2");
		exit(0);
	}
	return;
}


#ifdef __cplusplus
}
#endif
