/**
 * @file
 */
/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

//#include "Arduino.h"
#include "aj_target.h"
#include "aj_util.h"
#include "aj_debug.h"
#include "main.h"
#include <stdlib.h>
#include <time.h>

typedef struct time_struct {

    //The number of milliseconds in the time.
    uint32_t milliseconds;

} TIME_STRUCT;

void AJ_MemZeroSecure(void* s, size_t n)
{
	volatile unsigned char* p = s;
	while (n--) *p++ = '\0';
	return;
}

static inline uint32_t swap32(uint32_t w)
{
	return ((w & 0xff000000) >> 24) |
	((w & 0x00ff0000) >> 8) |
	((w & 0x0000ff00) << 8) | ((w & 0x000000ff) << 24);
}

uint64_t AJ_DecodeTime(char* der, char* fmt)
{
	struct tm tm;
	if (!strptime(der, fmt, &tm))
	{
		return 0;
	}
	return 0;//(uint64_t)timegm(&tm);
}


uint32_t AJ_ByteSwap32(uint32_t x)
{
	return swap32(x);
}

void AJ_Sleep(uint32_t time)
{
    //delay(time);
}

uint32_t AJ_GetElapsedTime(AJ_Time* timer, uint8_t cumulative)
{
    uint32_t elapsed;
    TIME_STRUCT now;

    now.milliseconds =  millis();
    elapsed = (uint32_t)now.milliseconds - (timer->seconds * 1000 + timer->milliseconds);  // watch for wraparound
    if (!cumulative) 
	{
        timer->seconds = (uint32_t)(now.milliseconds / 1000);
        timer->milliseconds = (uint16_t)(now.milliseconds % 1000);
    }
    return elapsed;
}
void AJ_InitTimer(AJ_Time* timer)
{
    TIME_STRUCT now;
    now.milliseconds = millis();
    timer->seconds = (uint32_t)(now.milliseconds / 1000);
    timer->milliseconds = (uint16_t)(now.milliseconds % 1000);
}

void* AJ_Malloc(size_t sz)
{
    return malloc(sz);
}

void* AJ_Realloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

void AJ_Free(void* mem)
{
    if (mem) 
	{
        free(mem);
    }
}

void ram_diag()
{
    AJ_AlwaysPrintf(("SRAM usage (stack, heap, static): %d, %d, %d\n",
                     stack_used(),
                     heap_used(),
                     static_used()));
}

uint8_t AJ_StartReadFromStdIn()
{
    return FALSE;
}

uint8_t AJ_StopReadFromStdIn()
{
    return FALSE;
}

char* AJ_GetCmdLine(char* buf, size_t num)
{
   // if (Serial.available() > 0) 
  // {
        int countBytesRead;
        // read the incoming bytes until a newline character:
    //    countBytesRead = Serial.readBytesUntil('\n', buf, num);
        buf[countBytesRead] = '\0';
        return buf;
   // } 
 //  else 
 //  {
        return NULL;
   // }
}

#ifndef NDEBUG

uint8_t dbgCONFIGUREME = 0;
uint8_t dbgNET = 0;
uint8_t dbgTARGET_CRYPTO = 0;
uint8_t dbgTARGET_NVRAM = 0;
uint8_t dbgTARGET_UTIL = 0;

int _AJ_DbgEnabled(const char* module)
{
    return FALSE;
}

#endif
