#include <psp2/appmgr.h>

int main() {
    while (1) {
        sceAppMgrLaunchAppByUri(0xF0000, "http://customprotocol.com");
        sceKernelExitProcess(0);
    }
}
