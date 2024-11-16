#include <windows.h>
#include <stdio.h>
#include "..\..\include\distormx.h"

typedef int(WINAPI* tMessageBoxA)(
    HWND hWnd,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType
);

tMessageBoxA pMessageBoxA;

unsigned int(*g_orig_f1)(unsigned int, unsigned int) = NULL;

int WINAPI dMessageBoxA(
    HWND hWnd, 
    LPCSTR lpText, 
    LPCSTR lpCaption, 
    UINT uType) {

    return pMessageBoxA(hWnd, "Hooked MessageBoxA", "Hooked", uType);

}

__declspec(noinline) unsigned int f1(unsigned int a, unsigned int b)
{
	return printf("Orig: %d + %x: %d\n", a, b, a + b);
}

__declspec(noinline) unsigned int f2(unsigned int a, unsigned int b)
{
	printf("\nhook start\n");
	unsigned int ret = g_orig_f1(a, b);
	printf("hook end\n\n");
	return ret;
}

int main()
{

	/* Original Example */
	f1(1, 1);

	g_orig_f1 = f1;
	if (!distormx_hook((void **)&g_orig_f1, reinterpret_cast<void*>(f2))) {
		printf("failed hooking");
		return 1;
	}
	f1(2, 2);
	distormx_unhook((void *)&g_orig_f1);
	f1(3, 3);
	distormx_destroy();

	/* MessageBox Example */
	HMODULE hModule = LoadLibraryA("user32.dll");
    if (hModule != nullptr) {

        // Hook for MessageBoxA
        pMessageBoxA = (tMessageBoxA)GetProcAddress(hModule, "MessageBoxA");
        if (pMessageBoxA != nullptr) {
            distormx_hook(
                &(PVOID&)pMessageBoxA,
                reinterpret_cast<void*>(dMessageBoxA));
        } else {
            printf("Failed to get address of MessageBoxA!");
        }
        
    } else {
        printf("Failed to load user32.dll!");
    }
    
    MessageBoxA(NULL, "Original MessageBoxA", "Original", MB_OK);

	return 0;
}