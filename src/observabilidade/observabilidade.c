

void plotar_request_corrente(CwebHttpRequest *request){
        UniversalGarbage  *garbage = newUniversalGarbage();
        cJSON  * data = cJSON_CreateObject();
        UniversalGarbage_add(garbage, cJSON_Delete,data);
        cJSON_AddStringToObject(data,"rota",request->route);
        if(request->content_length){
            unsigned  char *content = CwebHttpRequest_read_content(request,200);
            if(content){
                cJSON *parsed = cJSON_Parse((char*)content);
                if(parsed){
                    cJSON_AddItemToObject(data,"json_body",parsed);
                }
                else{
                    cJSON_AddStringToObject(data,"body",(char*)content);
                }
            }
        }
        char *result = cJSON_Print(data);
        UniversalGarbage_add_simple(garbage,result);

        CTextStack *path = newCTextStack_string_format(
                "requisicoes/%d/request.json",
                cweb_actual_request
                );
        UniversalGarbage_add(garbage, CTextStack_free,path);
    dtw_write_string_file_content(path->rendered_text,result);
    UniversalGarbage_free(garbage);

}

void plotar_resposta_corrente(CwebHttpResponse *resposta){
    UniversalGarbage  *garbage = newUniversalGarbage();
    cJSON  * data = cJSON_CreateObject();
    UniversalGarbage_add(garbage, cJSON_Delete,data);
    cJSON_AddNumberToObject(data,"status",resposta->status_code);
    if(resposta->content_length){
            char *resposta_formatada = (char*)malloc(resposta->content_length+2);
            UniversalGarbage_add_simple(garbage,resposta_formatada);
            memcpy(resposta_formatada,resposta->content,resposta->content_length);
            resposta_formatada[resposta->content_length] = '\0';
            cJSON *parsed = cJSON_Parse(resposta_formatada);
            if(parsed){
                    cJSON_AddItemToObject(data,"json_body",parsed);
            }
            if(!parsed){
                cJSON_AddStringToObject(data,"body",resposta_formatada);
            }
    }

    char *result = cJSON_Print(data);
    UniversalGarbage_add_simple(garbage,result);

    CTextStack *path = newCTextStack_string_format(
            "requisicoes/%d/resposta.json",
            cweb_actual_request
    );
    UniversalGarbage_add(garbage, CTextStack_free,path);
    dtw_write_string_file_content(path->rendered_text,result);
    UniversalGarbage_free(garbage);

}