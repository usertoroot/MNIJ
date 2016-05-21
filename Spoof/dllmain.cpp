#include <Windows.h>

#include <stdio.h>
#include <wchar.h>

#include <mscoree.h>
#include <MetaHost.h>
#pragma comment(lib, "mscoree.lib")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

extern "C" _declspec(dllexport) void Initialize()
{
	if (GetModuleHandle(L"mscoree.dll") == NULL)
		LoadLibrary(L"mscoree.dll");

	ICLRMetaHost* pClrMetaHost;
	HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&pClrMetaHost));
	if (hr != S_OK)
		return;

	ICLRRuntimeInfo* pRuntimeInfo;
	hr = pClrMetaHost->GetRuntime(L"v4.0.30319", IID_PPV_ARGS(&pRuntimeInfo));
	if (hr != S_OK)
		return;

	BOOL loadable;
	hr = pRuntimeInfo->IsLoadable(&loadable);
	if (hr != S_OK || !loadable)
		return;

	ICLRRuntimeHost* pClrRuntimeHost;
	hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&pClrRuntimeHost));
	if (hr != S_OK)
		return;

	hr = pClrRuntimeHost->Start();
	if (hr != S_OK)
		return;

	DWORD dwLengthRet;
	hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(L"MNID.dll", L"MNID.Main", L"Initialize", L"", &dwLengthRet);
	if (hr != S_OK)
		return;
}