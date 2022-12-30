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
#define NOKERNEL          1 // All KERNEL defines and routines
#define NONLS             1 // All NLS defines and routines
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
#undef NOKERNEL
#undef NONLS
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
#include "a_win32_gl.h"

void
FatalEngineError(char* format, ...)
{
	char buffer[1024];

	va_list args;
	va_start(args, format);
	wvsprintfA(buffer, format, args);
	va_end(args);

	// NOTE: ensure avoiding buffer overrun when string is too long
	buffer[ARRAY_SIZE(buffer) - 1] = 0;

	MessageBoxA(0, buffer, "Fatal Engine Error", MB_OK | MB_ICONERROR);

}

// TODO: WndProc recieves the WM_CLOSE message when the close button is pressed
//       but the window does not close if it hasn't been dragged after creation
LRESULT
WndProc(HWND window_handle, UINT msg_code, WPARAM wparam, LPARAM lparam)
{
	if (msg_code == WM_QUIT || msg_code == WM_CLOSE)
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
		.style         = CS_OWNDC,
		.lpfnWndProc   = &WndProc,
		.cbClsExtra    = 0,
		.cbWndExtra    = 0,
		.hInstance     = instance,
		.hIcon         = 0,
		.hCursor       = LoadImageW(instance, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE),
		.hbrBackground = 0,
		.lpszMenuName  = 0,
		.lpszClassName = L"CLASS NAME",
	};

	if (!RegisterClassW(&window_class_info)) FatalEngineError("Failed to register window class");
	else
	{		
		HWND window = CreateWindowW(window_class_info.lpszClassName, L"WINDOW NAME", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instance, 0);

		if (window == 0) FatalEngineError("Failed to create window");
		else
		{
			bool setup_failed = false;

			HGLRC gl_context = 0;
			if (!Win32GL_InitGLContextForWindow(instance, window, (bool)A_DEBUG, &gl_context))
			{
				FatalEngineError("Failed to initialize OpenGL");
				setup_failed = true;
			}

			if (!setup_failed)
			{
				ShowWindow(window, SW_SHOW);

				bool is_running = true;
				while (is_running)
				{
					MSG msg;
					while (PeekMessageW(&msg, window, 0, 0, PM_REMOVE))
					{
						if (msg.message == WM_QUIT)
						{
							is_running = false;
							break;
						}
						else DispatchMessageW(&msg);
					}

					HDC dc = GetDC(window);
					SwapBuffers(dc);
					ReleaseDC(window, dc);
				}
			}

			Win32GL_DeinitGLContext(gl_context);
		}
	}

	ExitProcess(0);
}
