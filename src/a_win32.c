#define NOGDICAPMASKS     1 // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES 1 // VK_*
#define NOSYSMETRICS      1 // SM_*
#define NOMENUS           1 // MF_*
#define NOICONS           1 // IDI_*
#define NOKEYSTATES       1 // MK_*
#define NOSYSCOMMANDS     1 // SC_*
#define NORASTEROPS       1 // Binary and Tertiary raster ops
#define OEMRESOURCE       1 // OEM Resource values
#define NOATOM            1 // Atom Manager routines
#define NOCLIPBOARD       1 // Clipboard routines
#define NOCTLMGR          1 // Control and Dialog routines
#define NODRAWTEXT        1 // DrawText() and DT_*
#define NOGDI             1 // All GDI defines and routines
#define NOKERNEL          1 // All KERNEL defines and routines
#define NONLS             1 // All NLS defines and routines
#define NOMB              1 // MB_* and MessageBox()
#define NOMEMMGR          1 // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        1 // typedef METAFILEPICT
#define NOMINMAX          1 // Macros min(a,b) and max(a,b)
#define NOOPENFILE        1 // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          1 // SB_* and scrolling routines
#define NOSERVICE         1 // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           1 // Sound driver routines
#define NOTEXTMETRIC      1 // typedef TEXTMETRIC and associated routines
#define NOWH              1 // SetWindowsHook and WH_*
#define NOWINOFFSETS      1 // GWL_*, GCL_*, associated routines
#define NOCOMM            1 // COMM driver routines
#define NOKANJI           1 // Kanji support stuff.
#define NOHELP            1 // Help engine interface.
#define NOPROFILER        1 // Profiler interface.
#define NODEFERWINDOWPOS  1 // DeferWindowPos routines
#define NOMCX             1 // Modem Configuration Extensions

#define STRICT
#define UNICODE
#define WIN32_LEAN_AND_MEAN 1

#include <windows.h>

#undef STRICT
#undef UNICODE
#undef WIN32_LEAN_AND_MEAN

#undef NOGDICAPMASKS
#undef NOVIRTUALKEYCODES
#undef NOSYSMETRICS
#undef NOMENUS
#undef NOICONS
#undef NOKEYSTATES
#undef NOSYSCOMMANDS
#undef NORASTEROPS
#undef OEMRESOURCE
#undef NOATOM
#undef NOCLIPBOARD
#undef NOCTLMGR
#undef NODRAWTEXT
#undef NOGDI
#undef NOKERNEL
#undef NONLS
#undef NOMB
#undef NOMEMMGR
#undef NOMETAFILE
#undef NOMINMAX
#undef NOOPENFILE
#undef NOSCROLL
#undef NOSERVICE
#undef NOSOUND
#undef NOTEXTMETRIC
#undef NOWH
#undef NOWINOFFSETS
#undef NOCOMM
#undef NOKANJI
#undef NOHELP
#undef NOPROFILER
#undef NODEFERWINDOWPOS
#undef NOMCX

#undef far
#undef near

#include "a.h"

LRESULT
WndProc(HWND window_handle, UINT msg_code, WPARAM wparam, LPARAM lparam)
{
	if (msg_code == WM_QUIT || msg_code == WM_CLOSE || msg_code == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else return DefWindowProc(window_handle, msg_code, wparam, lparam);
}

void __stdcall
WinMainCRTStartup()
{
	HINSTANCE instance = GetModuleHandle(0);

	WNDCLASSW window_class_info = {
		.style         = 0, // TODO:
		.lpfnWndProc   = &WndProc,
		.cbClsExtra    = 0,
		.cbWndExtra    = 0,
		.hInstance     = instance,
		.hIcon         = 0,
		.hCursor       = 0, // TODO:
		.hbrBackground = 0,
		.lpszMenuName  = 0,
		.lpszClassName = L"CLASS NAME",
	};

	if (!RegisterClassW(&window_class_info))
	{
		NOT_IMPLEMENTED;
	}
	else
	{
		HWND window_handle = CreateWindowW(window_class_info.lpszClassName, L"WINDOW NAME", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instance, 0);
		if (window_handle == 0)
		{
			NOT_IMPLEMENTED;
		}
		else
		{
			ShowWindow(window_handle, SW_SHOW);

			bool is_running = true;
			while (is_running)
			{
				MSG msg;
				while (PeekMessageW(&msg, window_handle, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT)
					{
						is_running = false;
						break;
					}
					else DispatchMessageW(&msg);
				}
			}
		}
	}

	ExitProcess(0);
}
