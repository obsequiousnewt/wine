/*
 * Copyright 2007 Jacek Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>

#define COBJMACROS

#include "windef.h"
#include "winbase.h"
#include "winuser.h"
#include "ole2.h"
#include "urlmon.h"
#include "urlmon_main.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(urlmon);

typedef struct {
    const IInternetProtocolVtbl *lpInternetProtocolVtbl;
    const IInternetBindInfoVtbl *lpInternetBindInfoVtbl;
    const IInternetPriorityVtbl *lpInternetPriorityVtbl;
    const IInternetProtocolSinkVtbl *lpInternetProtocolSinkVtbl;

    LONG ref;
} BindProtocol;

#define PROTOCOL(x)  ((IInternetProtocol*) &(x)->lpInternetProtocolVtbl)
#define BINDINFO(x)  ((IInternetBindInfo*) &(x)->lpInternetBindInfoVtbl)
#define PRIORITY(x)  ((IInternetPriority*) &(x)->lpInternetPriorityVtbl)
#define PROTSINK(x)  ((IInternetProtocolSink*) &(x)->lpInternetProtocolSinkVtbl)

#define PROTOCOL_THIS(iface) DEFINE_THIS(BindProtocol, InternetProtocol, iface)

static HRESULT WINAPI BindProtocol_QueryInterface(IInternetProtocol *iface, REFIID riid, void **ppv)
{
    BindProtocol *This = PROTOCOL_THIS(iface);

    *ppv = NULL;
    if(IsEqualGUID(&IID_IUnknown, riid)) {
        TRACE("(%p)->(IID_IUnknown %p)\n", This, ppv);
        *ppv = PROTOCOL(This);
    }else if(IsEqualGUID(&IID_IInternetProtocolRoot, riid)) {
        TRACE("(%p)->(IID_IInternetProtocolRoot %p)\n", This, ppv);
        *ppv = PROTOCOL(This);
    }else if(IsEqualGUID(&IID_IInternetProtocol, riid)) {
        TRACE("(%p)->(IID_IInternetProtocol %p)\n", This, ppv);
        *ppv = PROTOCOL(This);
    }else if(IsEqualGUID(&IID_IInternetBindInfo, riid)) {
        TRACE("(%p)->(IID_IInternetBindInfo %p)\n", This, ppv);
        *ppv = BINDINFO(This);
    }else if(IsEqualGUID(&IID_IInternetPriority, riid)) {
        TRACE("(%p)->(IID_IInternetPriority %p)\n", This, ppv);
        *ppv = PRIORITY(This);
    }else if(IsEqualGUID(&IID_IAuthenticate, riid)) {
        FIXME("(%p)->(IID_IAuthenticate %p)\n", This, ppv);
    }else if(IsEqualGUID(&IID_IServiceProvider, riid)) {
        FIXME("(%p)->(IID_IServiceProvider %p)\n", This, ppv);
    }else if(IsEqualGUID(&IID_IInternetProtocolSink, riid)) {
        TRACE("(%p)->(IID_IInternetProtocolSink %p)\n", This, ppv);
        *ppv = PROTSINK(This);
    }

    if(*ppv) {
        IInternetProtocol_AddRef(iface);
        return S_OK;
    }

    WARN("not supported interface %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}

static ULONG WINAPI BindProtocol_AddRef(IInternetProtocol *iface)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    LONG ref = InterlockedIncrement(&This->ref);
    TRACE("(%p) ref=%d\n", This, ref);
    return ref;
}

static ULONG WINAPI BindProtocol_Release(IInternetProtocol *iface)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    LONG ref = InterlockedDecrement(&This->ref);

    TRACE("(%p) ref=%d\n", This, ref);

    if(!ref) {
        HeapFree(GetProcessHeap(), 0, This);

        URLMON_UnlockModule();
    }

    return ref;
}

static HRESULT WINAPI BindProtocol_Start(IInternetProtocol *iface, LPCWSTR szUrl,
        IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo,
        DWORD grfPI, DWORD dwReserved)
{
    BindProtocol *This = PROTOCOL_THIS(iface);

    FIXME("(%p)->(%s %p %p %08x %d)\n", This, debugstr_w(szUrl), pOIProtSink,
            pOIBindInfo, grfPI, dwReserved);

    if(!szUrl || !pOIProtSink || !pOIBindInfo)
        return E_INVALIDARG;

    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Continue(IInternetProtocol *iface, PROTOCOLDATA *pProtocolData)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)->(%p)\n", This, pProtocolData);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Abort(IInternetProtocol *iface, HRESULT hrReason,
        DWORD dwOptions)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)->(%08x %08x)\n", This, hrReason, dwOptions);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Terminate(IInternetProtocol *iface, DWORD dwOptions)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)->(%08x)\n", This, dwOptions);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Suspend(IInternetProtocol *iface)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Resume(IInternetProtocol *iface)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Read(IInternetProtocol *iface, void *pv,
        ULONG cb, ULONG *pcbRead)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)->(%p %u %p)\n", This, pv, cb, pcbRead);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_Seek(IInternetProtocol *iface, LARGE_INTEGER dlibMove,
        DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)->(%d %d %p)\n", This, dlibMove.u.LowPart, dwOrigin, plibNewPosition);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_LockRequest(IInternetProtocol *iface, DWORD dwOptions)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)->(%08x)\n", This, dwOptions);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindProtocol_UnlockRequest(IInternetProtocol *iface)
{
    BindProtocol *This = PROTOCOL_THIS(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

#undef PROTOCOL_THIS

static const IInternetProtocolVtbl BindProtocolVtbl = {
    BindProtocol_QueryInterface,
    BindProtocol_AddRef,
    BindProtocol_Release,
    BindProtocol_Start,
    BindProtocol_Continue,
    BindProtocol_Abort,
    BindProtocol_Terminate,
    BindProtocol_Suspend,
    BindProtocol_Resume,
    BindProtocol_Read,
    BindProtocol_Seek,
    BindProtocol_LockRequest,
    BindProtocol_UnlockRequest
};

#define BINDINFO_THIS(iface) DEFINE_THIS(BindProtocol, InternetBindInfo, iface)

static HRESULT WINAPI BindInfo_QueryInterface(IInternetBindInfo *iface,
        REFIID riid, void **ppv)
{
    BindProtocol *This = BINDINFO_THIS(iface);
    return IInternetProtocol_QueryInterface(PROTOCOL(This), riid, ppv);
}

static ULONG WINAPI BindInfo_AddRef(IInternetBindInfo *iface)
{
    BindProtocol *This = BINDINFO_THIS(iface);
    return IBinding_AddRef(PROTOCOL(This));
}

static ULONG WINAPI BindInfo_Release(IInternetBindInfo *iface)
{
    BindProtocol *This = BINDINFO_THIS(iface);
    return IBinding_Release(PROTOCOL(This));
}

static HRESULT WINAPI BindInfo_GetBindInfo(IInternetBindInfo *iface,
        DWORD *grfBINDF, BINDINFO *pbindinfo)
{
    BindProtocol *This = BINDINFO_THIS(iface);
    FIXME("(%p)->(%p %p)\n", This, grfBINDF, pbindinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI BindInfo_GetBindString(IInternetBindInfo *iface,
        ULONG ulStringType, LPOLESTR *ppwzStr, ULONG cEl, ULONG *pcElFetched)
{
    BindProtocol *This = BINDINFO_THIS(iface);
    FIXME("(%p)->(%d %p %d %p)\n", This, ulStringType, ppwzStr, cEl, pcElFetched);
    return E_NOTIMPL;
}

#undef BINDFO_THIS

static const IInternetBindInfoVtbl InternetBindInfoVtbl = {
    BindInfo_QueryInterface,
    BindInfo_AddRef,
    BindInfo_Release,
    BindInfo_GetBindInfo,
    BindInfo_GetBindString
};

#define PRIORITY_THIS(iface) DEFINE_THIS(BindProtocol, InternetPriority, iface)

static HRESULT WINAPI InternetPriority_QueryInterface(IInternetPriority *iface,
        REFIID riid, void **ppv)
{
    BindProtocol *This = PRIORITY_THIS(iface);
    return IInternetProtocol_QueryInterface(PROTOCOL(This), riid, ppv);
}

static ULONG WINAPI InternetPriority_AddRef(IInternetPriority *iface)
{
    BindProtocol *This = PRIORITY_THIS(iface);
    return IInternetProtocol_AddRef(PROTOCOL(This));
}

static ULONG WINAPI InternetPriority_Release(IInternetPriority *iface)
{
    BindProtocol *This = PRIORITY_THIS(iface);
    return IInternetProtocol_Release(PROTOCOL(This));
}

static HRESULT WINAPI InternetPriority_SetPriority(IInternetPriority *iface, LONG nPriority)
{
    BindProtocol *This = PRIORITY_THIS(iface);
    FIXME("(%p)->(%d)\n", This, nPriority);
    return E_NOTIMPL;
}

static HRESULT WINAPI InternetPriority_GetPriority(IInternetPriority *iface, LONG *pnPriority)
{
    BindProtocol *This = PRIORITY_THIS(iface);
    FIXME("(%p)->(%p)\n", This, pnPriority);
    return E_NOTIMPL;
}

#undef PRIORITY_THIS

static const IInternetPriorityVtbl InternetPriorityVtbl = {
    InternetPriority_QueryInterface,
    InternetPriority_AddRef,
    InternetPriority_Release,
    InternetPriority_SetPriority,
    InternetPriority_GetPriority

};

#define PROTSINK_THIS(iface) DEFINE_THIS(BindProtocol, InternetProtocolSink, iface)

static HRESULT WINAPI InternetProtocolSink_QueryInterface(IInternetProtocolSink *iface,
        REFIID riid, void **ppv)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    return IInternetProtocol_QueryInterface(PROTOCOL(This), riid, ppv);
}

static ULONG WINAPI InternetProtocolSink_AddRef(IInternetProtocolSink *iface)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    return IInternetProtocol_AddRef(PROTOCOL(This));
}

static ULONG WINAPI InternetProtocolSink_Release(IInternetProtocolSink *iface)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    return IInternetProtocol_Release(PROTOCOL(This));
}

static HRESULT WINAPI InternetProtocolSink_Switch(IInternetProtocolSink *iface,
        PROTOCOLDATA *pProtocolData)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    FIXME("(%p)->(%p)\n", This, pProtocolData);
    return E_NOTIMPL;
}

static HRESULT WINAPI InternetProtocolSink_ReportProgress(IInternetProtocolSink *iface,
        ULONG ulStatusCode, LPCWSTR szStatusText)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    FIXME("(%p)->(%u %s)\n", This, ulStatusCode, debugstr_w(szStatusText));
    return E_NOTIMPL;
}

static HRESULT WINAPI InternetProtocolSink_ReportData(IInternetProtocolSink *iface,
        DWORD grfBSCF, ULONG ulProgress, ULONG ulProgressMax)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    FIXME("(%p)->(%d %u %u)\n", This, grfBSCF, ulProgress, ulProgressMax);
    return E_NOTIMPL;
}

static HRESULT WINAPI InternetProtocolSink_ReportResult(IInternetProtocolSink *iface,
        HRESULT hrResult, DWORD dwError, LPCWSTR szResult)
{
    BindProtocol *This = PROTSINK_THIS(iface);
    FIXME("(%p)->(%08x %d %s)\n", This, hrResult, dwError, debugstr_w(szResult));
    return E_NOTIMPL;
}

#undef PROTSINK_THIS

static const IInternetProtocolSinkVtbl InternetProtocolSinkVtbl = {
    InternetProtocolSink_QueryInterface,
    InternetProtocolSink_AddRef,
    InternetProtocolSink_Release,
    InternetProtocolSink_Switch,
    InternetProtocolSink_ReportProgress,
    InternetProtocolSink_ReportData,
    InternetProtocolSink_ReportResult
};

HRESULT create_binding_protocol(LPCWSTR url, IInternetProtocol **protocol)
{
    BindProtocol *ret = HeapAlloc(GetProcessHeap(), 0, sizeof(BindProtocol));

    ret->lpInternetProtocolVtbl = &BindProtocolVtbl;
    ret->lpInternetBindInfoVtbl = &InternetBindInfoVtbl;
    ret->lpInternetPriorityVtbl = &InternetPriorityVtbl;
    ret->lpInternetProtocolSinkVtbl = &InternetProtocolSinkVtbl;
    ret->ref = 1;

    *protocol = PROTOCOL(ret);
    return S_OK;
}
