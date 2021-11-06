#include "webserver.h"
void setupSystem(){
    addHttpApi("/reset/",[](){
        server.send(200);
        delay(500); // chờ send thành công.
        ESP.restart();
    });
}