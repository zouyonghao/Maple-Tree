// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdint>
#include <filesystem>
#include <conio.h>
#include <vector>
#include <regex>
#include <map>
#include <future>

// TODO: reference additional headers your program requires here

typedef unsigned __int64 ulong;
typedef unsigned __int64 u64;
typedef signed __int64 s64;

typedef unsigned int uint;
typedef unsigned int u32;
typedef signed int s32;

typedef unsigned short ushort;
typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

#include "Decrypt.h"
#include "Toolbelt.h"
#include "DownloadClient.h"
#include "TitleInfo.h"

//Third Party libraries
#include "mongoose.h"
#include "frozen.h"
#include "rang.hpp"

using namespace std;