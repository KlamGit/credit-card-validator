#include <microhttpd.h>
#include <stdio.h>

int main() {
    printf("MHD Version: %s\n", MHD_get_version());
    return 0;
}