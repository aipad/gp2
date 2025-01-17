/**
  * GreenPois0n Anthrax - utils.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Justin Williams
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef UTILS_H
#define UTILS_H

#include "syscalls.h"

#undef NULL
#define NULL 0

#define FALSE 0
#define TRUE  1

#define FLIPENDIAN(x) flipEndian((unsigned char *)(&(x)), sizeof(x))

#define puts _puts
#define putc _putc
#define strlen _strlen
#define strcmp _strcmp
#define strncat _strncat
#define strncpy _strncpy

extern int console;

typedef enum {
	false = 0, true = 1
} bool;

static inline void flipEndian(unsigned char* x, int length) {
	int i;
	unsigned char tmp;
	for(i = 0; i < (length / 2); i++) {
		tmp = x[i];
		x[i] = x[length - i - 1];
		x[length - i - 1] = tmp;
	}
}

static char* cache_env[] = {
		"DYLD_SHARED_CACHE_DONT_VALIDATE=1",
		"DYLD_SHARED_CACHE_DIR=/System/Library/Caches/com.apple.dyld",
		"DYLD_SHARED_REGION=private"
};

void _putc(const char c);
void _puts(const char* s);
int _strlen(const char* s);
int _strcmp(const char* s1, const char* s2);
char* _strncat(char* s1, const char* s2, int n);
char* _strncpy(char* s1, const char* s2, int n);
void* memset(char* b, int c, int len);
void* memcpy(char* s1, const char* s2, int n);

void puti(unsigned int integer);
void sleep(unsigned int seconds);
int exec(char* argv[], char* env[]);
int cp(const char* src, const char* dest);
int fsexec(char* argv[], char* env[], bool pause);
int hfs_mount(const char* device, const char* mountdir, int options);
int install(const char* src, const char* dst, int uid, int gid, int mode);
int file_exists(const char* path);

#endif
