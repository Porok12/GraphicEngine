// stdafx.h : Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

// �ndern Sie folgende Definitionen f�r Plattformen, die �lter als die unten angegebenen sind.
// In MSDN finden Sie die neuesten Informationen �ber die entsprechenden Werte f�r die unterschiedlichen Plattformen.
#ifndef WINVER              // Lassen Sie die Verwendung spezifischer Features von Windows XP oder sp�ter zu.
#   define WINVER 0x0501        // �ndern Sie dies in den geeigneten Wert f�r andere Versionen von Windows.
#endif

#ifndef _WIN32_WINNT        // Lassen Sie die Verwendung spezifischer Features von Windows XP oder sp�ter zu.
#   define _WIN32_WINNT 0x0501  // �ndern Sie dies in den geeigneten Wert f�r andere Versionen von Windows.
#endif

#ifndef _WIN32_WINDOWS      // Lassen Sie die Verwendung spezifischer Features von Windows 98 oder sp�ter zu.
#   define _WIN32_WINDOWS 0x0410 // �ndern Sie dies in den geeigneten Wert f�r Windows Me oder h�her.
#endif

#ifndef _WIN32_IE           // Lassen Sie die Verwendung spezifischer Features von IE 6.0 oder sp�ter zu.
#define _WIN32_IE 0x0600    // �ndern Sie dies in den geeigneten Wert f�r andere Versionen von IE.
#endif

#define WIN32_LEAN_AND_MEAN     // Selten verwendete Teile der Windows-Header nicht einbinden.
// Windows-Headerdateien:
#include <windows.h>

// C RunTime-Headerdateien
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

// D3D9 includes

#if (defined _DEBUG)
#   define D3D_DEBUG_INFO
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9mesh.h>

// ShellExecute()
#include <shellapi.h>
#include <commctrl.h>

// GetOpenFileName()
#include <commdlg.h>
#include <algorithm>
#include <mmsystem.h>

#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>

#if defined _MSC_VER
// Windows CommonControls 6.0 Manifest Extensions
#   if defined _M_IX86
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   elif defined _M_IA64
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   elif defined _M_X64
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   else
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   endif
#endif
