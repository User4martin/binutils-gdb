
#pragma once

#ifndef WTOU_H
#define WTOU_H

#ifdef _WIN32

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

extern char*    wtou(const wchar_t* w);
extern wchar_t* utow(const char* v);
extern int      uopen2(const char *filename,int oflag);
extern int      uopen3(const char *filename,int oflag,int pmode);
extern FILE*    ufopen(const char * _Filename,const char * _Mode);
extern int      uaccess(const char *path,int mode);
extern int      ustat (const char *filename, struct _stat *buf);
extern char*    ugetenv(const char *varname);
extern char**   getwargv(int* argc);
extern int      uchdir (const char *dir);
extern _WDIR*   uopendir (const char *dir_name);
extern int      uchmod( const char *filename, int pmode );
extern int      uunlink(const char *filename);
extern int      uremove(const char *path);
extern int      urename(const char *oldname,const char *newname);
extern int      _ufgetc(FILE * _file,char* ubuf);
extern int      _utf8_char_len (const char *linebuf);

#define fopen(f,m) ufopen(f,m)
#define fopen64(f,m) ufopen(f,m)
#undef  access
#define access(path,mode) uaccess(path,mode)
#define getenv(varname) ugetenv(varname)
#define chdir(Dir) uchdir(Dir)
#define unlink(Dir) uunlink(Dir)
#endif

#ifdef __cplusplus
}
#endif

#endif
