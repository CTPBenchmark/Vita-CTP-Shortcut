#include <psp2/kernel/threadmgr.h>
#include "CTPApiThread.hh"
#include "CTPApi.hh"
#include <psp2/kernel/clib.h>

void getPostsByApiStartThread() {

    SceUID thid = sceKernelCreateThread(
                "CTPApithread", (SceKernelThreadEntry) getPostsByApiThread, 0x40, 0x20000, 0,
                0, nullptr);
    sceKernelStartThread(thid, 0, nullptr);

}

void getPostsByApiThread() {
    CTPApi::getInstance()->getPostsByApi();

    sceKernelExitDeleteThread(0);
}