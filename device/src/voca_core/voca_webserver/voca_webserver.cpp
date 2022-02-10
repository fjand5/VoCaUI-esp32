#include "voca_webserver.h"
VocaWebserver vocaWebserver(80);
VocaWebserver::VocaWebserver(int port) : WebServer(port)
{
}
void VocaWebserver::begin(/* args */)
{

    vocaStatus.waitStatus(Status_SetupWifi_Done);
    on("/", HTTP_GET, [this]()
       {
           sendComHeader();
#ifdef USE_DATA_FROM_FILE
           File index_html = SPIFFS.open("/index.html.gz", "r");
           streamFile(index_html, "text/html");
           index_html.close();
#else
            sendHeader("Content-Encoding", "gzip");
            send_P(200, "text/html", index_html, index_html_length);
#endif
       });
    on("/checkToken",
       [this]()
       {
           if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
           {

               sendComHeader();
               if (method() == HTTP_OPTIONS)
               {
                   send(200);
                   xSemaphoreGive(semHttpRequest);
                   return;
               }
               String token = header("Authorization");
               token.replace("Bearer ", "");
#ifdef AUTH_FEATURE
               if (vocaAuth.checkAuthJwt(token))
               {
                   String bearerHeader = String("Bearer ") + vocaAuth.createAuthJwt();
                   sendHeader("Authorization", bearerHeader);
                   send(200);
               }
               else
               {
                   send(401);
               }
#else
                send(200);
#endif
               xSemaphoreGive(semHttpRequest);
           }
       });
    on("/login",
       [this]()
       {
           if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
           {

               sendComHeader();
               if (method() == HTTP_OPTIONS)
               {
                   send(200);
                   xSemaphoreGive(semHttpRequest);
                   return;
               }
#ifdef AUTH_FEATURE
               if (authenticate(vocaAuth.getUsername().c_str(), vocaAuth.getPassword().c_str()))
               {
                   String bearerHeader = String("Bearer ") + vocaAuth.createAuthJwt();
                   sendHeader("Authorization", bearerHeader);

                   send(200);
               }
               else
               {
                   send(401);
               }
#else
                String bearerHeader = String("Bearer ") + "";
                sendHeader("Authorization", bearerHeader);

                send(200);
#endif
               xSemaphoreGive(semHttpRequest);
           }
       });
    on("/changePassword",
       [this]()
       {
           if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
           {

               sendComHeader();
               if (method() == HTTP_OPTIONS)
               {
                   send(200);
                   xSemaphoreGive(semHttpRequest);
                   return;
               }
#ifdef AUTH_FEATURE

               String token = header("Authorization");
               token.replace("Bearer ", "");
               if (vocaAuth.checkAuthJwt(token))
               {
                   String bearerHeader = String("Bearer ") + vocaAuth.createAuthJwt();
                   sendHeader("Authorization", bearerHeader);
                   String _arg = arg(0);
                   DynamicJsonDocument _doc(258);
                   deserializeJson(_doc, _arg);
                   JsonObject obj = _doc.as<JsonObject>();
                   String password = obj["password"];
                   String newPassword = obj["newPassword"];
                   if (vocaAuth.getPassword() == password)
                   {
                       vocaAuth.setPassword(newPassword);
                       send(200);
                   }
                   else
                   {
                       send(400);
                   }
               }
               else
               {
                   send(401);
               }
#else
                send(200);
#endif
               xSemaphoreGive(semHttpRequest);
           }
       });
    on("/js/app.js",
       [this]()
       {
           if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
           {
               sendComHeader();

#ifdef USE_DATA_FROM_FILE
               File app_js = SPIFFS.open("/app.js.gz", "r");
               streamFile(app_js, "application/javascript");
               app_js.close();
#else
                sendHeader("Content-Encoding", "gzip");
                send_P(200, "application/javascript", app_js, app_js_length);
#endif
               xSemaphoreGive(semHttpRequest);
           }
       });
    on("/fonts/element-icons.woff",
       [this]()
       {
           if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
           {
               sendComHeader();

#ifdef USE_DATA_FROM_FILE
               File font_woff = SPIFFS.open("/element-icons.woff.gz", "r");
               streamFile(font_woff, "application/javascript");
               font_woff.close();
#else
                sendHeader("Content-Encoding", "gzip");
                send_P(200, "application/javascript", font_woff, font_woff_length);
#endif
               xSemaphoreGive(semHttpRequest);
           }
       });
    on("/static/favicon.ico",
       [this]()
       {
           if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
           {
               sendComHeader();
#ifdef USE_DATA_FROM_FILE
               File favicon_ico = SPIFFS.open("/favicon.ico.gz", "r");
               streamFile(favicon_ico, "application/javascript");
               favicon_ico.close();
#else
                sendHeader("Content-Encoding", "gzip");
                send_P(200, "application/javascript", favicon_ico, favicon_ico_length);
#endif
               xSemaphoreGive(semHttpRequest);
           }
       });
    httpUpdater.setup(this);
    WebServer::begin();
    semHttpRequest = xSemaphoreCreateBinary();
    xSemaphoreGive(semHttpRequest);
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            VocaWebserver *_vocaWebserver = (VocaWebserver *)param;
            log_w("loopWebserver is running on core: %d", xPortGetCoreID());
            vocaStatus.setStatus(Status_WebServer_Ready);
            vocaStatus.waitStatus(Status_WebSocket_Ready);

            while (1)
            {
                _vocaWebserver->handleClient();
                delay(20);
            }
        },
        "loopWebserver",
        4096,
        (void *)this,
        1,
        NULL,
        VOCA_CORE_CPU);
}
void VocaWebserver::sendComHeader()
{
    sendHeader(F("Access-Control-Allow-Origin"), "*");
    sendHeader(F("Access-Control-Allow-Methods"), "PUT,POST,GET,OPTIONS");
    sendHeader(F("Access-Control-Allow-Headers"), "*");
    sendHeader(F("Access-Control-Expose-Headers"), "*");
}
void VocaWebserver::addHttpApi(const String url, Response response)
{
    String _url = url;
    if (url.startsWith("/"))
        _url = url.substring(1);
    on(String("/api/") + _url, [this, response]()
       {
              if (xSemaphoreTake(semHttpRequest, portMAX_DELAY) == pdTRUE)
              {
                sendComHeader();
                if (method() == HTTP_OPTIONS)
                {
                  send(200);
                  xSemaphoreGive(semHttpRequest);
                  return;
                }
#ifdef AUTH_FEATURE
                String token = header("Authorization");
                token.replace("Bearer ", "");
                if (vocaAuth.checkAuthJwt(token))
                {
                  String bearerHeader = String("Bearer ") + vocaAuth.createAuthJwt();
                  sendHeader("Authorization", bearerHeader);
                  response();
                }
                else
                {
                  send(401);
                }
#else
                    response();
#endif
                xSemaphoreGive(semHttpRequest);
              } });
}

VocaWebserver::~VocaWebserver()
{
}