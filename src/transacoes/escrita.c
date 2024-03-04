

void escreve_transacao_no_disco(DtwResource *banco, DtwResource *id_cliente, cJSON *dados, int saldo,Transacao *transacao){

    UniversalGarbage  *garbage = newUniversalGarbage();

    //adicionando o novo saldo
    cJSON_ReplaceItemInArray(dados,SALDO_INDEX, cJSON_CreateNumber(saldo));


    //criando a transacao
    cJSON *json_transacao = cJSON_CreateArray();
    UniversalGarbage_add(garbage, cJSON_Delete,json_transacao);
    if(transacao->tipo == CODIGO_CREDITO){
        cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(transacao->valor));
    }
    if(transacao->tipo== CODIGO_DEBITO){
        cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(transacao->valor * -1));

    }
    cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(time(NULL)));
    cJSON_AddItemToArray(json_transacao, cJSON_CreateString(transacao->descricao));


    int id_transacao = 0;
    cJSON *lista_transacoes = cJSON_GetArrayItem(dados,TRANSACOES_INDEX);

    int total_transacoes  = cJSON_GetArraySize(lista_transacoes);
    if(total_transacoes > 0){
        cJSON *ultima = cJSON_GetArrayItem(lista_transacoes,total_transacoes -1);
        id_transacao = ultima->valueint+1;
    }

    DtwResource *resource_transacaos = DtwResource_sub_resource(id_cliente,CAMINHO_TRANSACOES);


    cJSON_AddItemToArray(lista_transacoes, cJSON_CreateNumber(id_transacao));
    total_transacoes+=1;
    if(total_transacoes >MAXIMO_TRANSACOES){
        int primeiro = cJSON_GetArrayItem(lista_transacoes,0)->valueint;
        DtwResource *transacao_mais_antiga = DtwResource_sub_resource(resource_transacaos,"%d",primeiro);
        DtwResource_destroy(transacao_mais_antiga);

        cJSON_DeleteItemFromArray(lista_transacoes,0);
    }

    //definindo as resources
    char *json_transacao_str = cJSON_PrintUnformatted(json_transacao);
    UniversalGarbage_add_simple(garbage,json_transacao_str);


    char *dados_str = cJSON_PrintUnformatted(dados);
    UniversalGarbage_add_simple(garbage, dados_str);

    DtwResource_set_string_in_sub_resource(resource_transacaos,json_transacao_str,"%d",id_transacao);
    DtwResource_set_string_in_sub_resource(id_cliente, dados_str, CAMINHO_DADOS);
    DtwResource_commit(banco);
    UniversalGarbage_free(garbage);

}