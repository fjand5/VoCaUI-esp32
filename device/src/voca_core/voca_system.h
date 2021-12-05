#include "voca_webserver.h"
void setupSystem(){
    addHttpApi("/reset",[](){
        log_d("reset system");
        server.send(200);
        delay(500); // chờ send thành công.
        ESP.restart();
    });
}