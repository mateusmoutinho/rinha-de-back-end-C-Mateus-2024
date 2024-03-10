#define PORTA_PADRAO 3000
#define INCONSISTENCIA 422
#define NAO_ENCONTRADO 404
#define MAXIMO_BODY 200
#define ERRO_INTERNO 500
#define RETORNO_OK 200
#define MAXIMO_TRANSACOES 10

#ifdef  DEBUG
#define IDENTAR true
#else
#define  IDENTAR false
#endif
#define MAXIMO_FILA 100000
#define MAXIMO_REQUEST 5
#define TIMEOUT_FUNCAO 59
#define TOLERANCIA_BLOQUEIO (TIMEOUT_FUNCAO -1)
#define TIMEOUT_CLIENTE 60

#define VARIAVEL_TOTAL_PROCESSOS "PROCESSOS"