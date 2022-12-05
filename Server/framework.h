// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#define MAXPLAYERNUM 3

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>


#include <Vfw.h>

#pragma comment(lib, "Vfw32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")
////////////////////////////사운드
#include <io.h>

#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")
////////
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <array>
using namespace std;
#include "resource.h"
#include "Enum.h"
#include "Define.h"
#include "Struct.h"
#include "Exturn.h"
#include "Funtion.h"

#include "KeyMgr.h"
#include "BitmapMgr.h"
#include "MyScrollMgr.h"

//딜레이용
#include "SoundMgr.h"