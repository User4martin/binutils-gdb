
#ifdef _WIN32
#include "defs.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <windows.h>
using namespace std;

char* wtou(const wchar_t* w)
{
 int size;
 char* r = NULL;
 size = WideCharToMultiByte(CP_UTF8,0,w,-1,NULL,0,NULL,NULL);
 if (!size) return NULL;
 r = (char *) calloc(size,sizeof(char));
 WideCharToMultiByte(CP_UTF8,0,w,-1,r,size,NULL,NULL);
 return r;
}

wchar_t* utow(const char* v)
{
 int size;
 size = MultiByteToWideChar(CP_UTF8,0,v,-1,NULL,0);
 if (!size) return NULL;
 wchar_t* r = (wchar_t *) calloc(size,sizeof(wchar_t));
 MultiByteToWideChar(CP_UTF8,0,v,-1,r,size);
 return r;
}

int uopen2(const char *filename,int oflag)
{
 wchar_t* wf = utow (filename);
 int fd = _wopen (wf, oflag);
 free (wf);
 return fd;
}

int uopen3(const char *filename,int oflag,int pmode)
{
 wchar_t* wf = utow (filename);
 int fd = _wopen (wf, oflag, pmode);
 free (wf);
 return fd;
}

FILE * ufopen(const char * _Filename,const char * _Mode)
{
 wchar_t* wf = utow (_Filename);
 wchar_t* wm = utow (_Mode);
 FILE * f = _wfopen (wf, wm);
 free (wf);
 free (wm);
 return f;
}

int uaccess(const char *path,int mode)
{
 wchar_t* wp = utow(path);
 int r = _waccess(wp,mode);
 free((void*)wp);
 return r;
}

int ustat (const char *filename, struct _stat *buf)
{
 wchar_t* wf = utow (filename);
 int r = _wstat(wf,buf);
 free ((void*)wf);
 return r;
}

char* ugetenv(const char *varname)
{
 wchar_t* wv = utow (varname);
 char* r = wtou (_wgetenv(wv));
 free (wv);
 return r;
}

char** getwargv(int* argc)
{
 char** argv = NULL;
 LPWSTR *szArglist;
 szArglist = CommandLineToArgvW(GetCommandLineW(), argc);
 if (szArglist != NULL)
 {
  argv = (char **) calloc(*argc+1,sizeof(void*));
  int i;
  for( i=0; i<*argc; i++)
  {
   argv[i] = wtou(szArglist[i]);
  }
  LocalFree(szArglist);
 }
 return argv;
}

int uchdir (const char *dir)
{
 wchar_t* wname = utow (dir);
 int r = _wchdir (wname);
 free((void*)wname);
 return r;
}

_WDIR* uopendir (const char *dir_name)
{
 _WDIR *dirp;
 wchar_t* wf = utow (dir_name);
 dirp = _wopendir (wf);
 free ((void*)wf);
 return dirp;
}

int uchmod( const char *filename, int pmode )
{
 int r;
 wchar_t* wf = utow (filename);
 r = _wchmod (wf,pmode);
 free ((void*)wf);
 return r;
}

int uunlink(const char *filename)
{
 int r;
 wchar_t* wf = utow (filename);
 r = _wunlink (wf);
 free ((void*)wf);
 return r;
}

int uremove(const char *path)
{
 int r;
 wchar_t* wf = utow (path);
 r = _wremove (wf);
 free ((void*)wf);
 return r;
}

int urename(const char *oldname,const char *newname)
{
 int r;
 wchar_t* wo = utow (oldname);
 wchar_t* wn = utow (newname);
 r = _wrename (wo,wn);
 free ((void*)wo);
 free ((void*)wn);
 return r;
}

int _ufgetc(FILE * _file,char* ubuf)
{
 int fd = fileno (_file);
 if (!isatty (fd)) 
 {
  DWORD L = 0;
  ReadFile( (HANDLE) _get_osfhandle(fd),ubuf,1,&L,NULL);
  if (!L) return (EOF);
  return L;
 }

 HANDLE HI = (HANDLE) _get_osfhandle(fd);
 HANDLE HO = GetStdHandle (STD_OUTPUT_HANDLE);
 INPUT_RECORD wi;
 DWORD L = 0;
 while (1) {
  ReadConsoleInputW(HI,&wi,1,&L);   
  if (L == 0) return (WEOF);
  if ((wi.EventType == KEY_EVENT) && (wi.Event.KeyEvent.bKeyDown))
  {
   if (wi.Event.KeyEvent.uChar.UnicodeChar == 0) {

			switch (wi.Event.KeyEvent.wVirtualKeyCode) {
                case VK_NUMPAD0: //1B 5B 32 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x32;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_NUMPAD1: //1B 5B 46 
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x46;
                  return 3;
                case VK_NUMPAD2: //1B 5B 42
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x42;
                  return 3;
                case VK_NUMPAD3: //1B 5B 36 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x36;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_NUMPAD4: //1B 5B 44
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x44;
                  return 3;
                case VK_NUMPAD5: //1B 5B 45
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x45;
                  return 3;
                case VK_NUMPAD6: //1B 5B 43
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x43;
                  return 3;
                case VK_NUMPAD7: //1B 5B 48
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x48;
                  return 3;
                case VK_NUMPAD8: //1B 5B 41
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x41;
                  return 3;
                case VK_NUMPAD9: //1B 5B 35 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x35;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_DECIMAL: //1B 5B 33 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x33;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_HOME  : //1B 5B 48
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x48;
                  return 3;
                case VK_END   : //1B 5B 46
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x46;
                  return 3;
                case VK_UP    : //1B 5B 41
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x41;
                  return 3;
                case VK_LEFT  : //1B 5B 44
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x44;
                  return 3;
                case VK_RIGHT : //1B 5B 43
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x43;
                  return 3;
                case VK_DOWN  : //1B 5B 42
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x42;
                  return 3;
                case VK_PRIOR : //1B 5B 36 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x36;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_NEXT  : //1B 5B 35 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x35;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_INSERT: //1B 5B 32 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x32;
                  ubuf[3]=0x7E;
                  return 4;
                case VK_DELETE: //1B 5B 33 7E
                  ubuf[0]=0x1B;
                  ubuf[1]=0x5B;
                  ubuf[2]=0x33;
                  ubuf[3]=0x7E;
                  return 4;
			}

   } else {
    WriteConsoleW(HO,&wi.Event.KeyEvent.uChar.UnicodeChar,1,&L,NULL);
    switch (wi.Event.KeyEvent.uChar.UnicodeChar) {
     case 4:
      return EOF;
     case 10:
      wi.Event.KeyEvent.uChar.UnicodeChar = 13;
      WriteConsoleW(HO,&wi.Event.KeyEvent.uChar.UnicodeChar,1,&L,NULL);
      return 10;
     case 13:
      wi.Event.KeyEvent.uChar.UnicodeChar = 10;
      WriteConsoleW(HO,&wi.Event.KeyEvent.uChar.UnicodeChar,1,&L,NULL);
      break;
     case 8:
      wi.Event.KeyEvent.uChar.UnicodeChar = 32;
      WriteConsoleW(HO,&wi.Event.KeyEvent.uChar.UnicodeChar,1,&L,NULL);
      wi.Event.KeyEvent.uChar.UnicodeChar = 8;
      WriteConsoleW(HO,&wi.Event.KeyEvent.uChar.UnicodeChar,1,&L,NULL);
      break;
    }
    int L = WideCharToMultiByte(CP_UTF8,0,&wi.Event.KeyEvent.uChar.UnicodeChar,1,NULL,0,NULL,NULL);
    if (!L) return (EOF);
    WideCharToMultiByte(CP_UTF8,0,&wi.Event.KeyEvent.uChar.UnicodeChar,1,(LPSTR) (ubuf),L,NULL,NULL);
    return L;
   }
  }
 }
}

int _utf8_char_len (const char *linebuf)
{
 switch (linebuf[0]) {

  case 0x00 ... 0x7F:
   return 1;

  case 0xC2 ... 0xDF:
   switch (linebuf[1]) {
    case 0x80 ... 0xBF:
     return 2;
    default:
     return 1;
   }

  case 0xE0:
   switch (linebuf[1]) {
    case 0xA0 ... 0xBF:
     switch (linebuf[2]) {
      case 0x80 ... 0xBF:
       return 3;
     default:
      return 2;
     }
    default:
     return 1;
   }

  case 0xE1 ... 0xEF:
   switch (linebuf[1]) {
    case 0x80 ... 0xBF:
     switch (linebuf[2]) {
      case 0x80 ... 0xBF:
       return 3;
     default:
      return 2;
     }
    default:
     return 1;
   }

  case 0xF0:
   switch (linebuf[1]) {
    case 0x90 ... 0xBF:
     switch (linebuf[2]) {
      case 0x80 ... 0xBF:
       switch (linebuf[3]) {
        case 0x80 ... 0xBF:
         return 4;
        default:
         return 3;
       }
     default:
      return 2;
     }
    default:
     return 1;
   }

  case 0xF1 ... 0xF4:
   switch (linebuf[1]) {
    case 0x80 ... 0xBF:
     switch (linebuf[2]) {
      case 0x80 ... 0xBF:
       switch (linebuf[3]) {
        case 0x80 ... 0xBF:
         return 4;
        default:
         return 3;
       }
     default:
      return 2;
     }
    default:
     return 1;
   }

  default:
   return 1;
 }
} 

#endif
