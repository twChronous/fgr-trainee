#include "CONFIG.h"

struct EmmitData {
    String eventName;
    String result;
    bool finished;
    unsigned long timestamp;
};

class EventEmitter {
public:
    using Callback = void (*)(); // Tipo de função callback (ponteiro para função)

    // Adiciona um listener (callback) para um evento específico
    void on(const char* eventName, Callback callback) {
        for (int i = 0; i < MAX_EVENTS; i++) {
            if (strcmp(events[i], eventName) == 0 || events[i][0] == '\0') {
                // Evento encontrado ou slot vazio
                if (events[i][0] == '\0') {
                    strncpy(events[i], eventName, 20); // Registra o nome do evento
                }
                for (int j = 0; j < MAX_LISTENERS; j++) {
                    if (listeners[i][j] == nullptr) {
                        listeners[i][j] = callback; // Registra o callback
                        return;
                    }
                }
            }
        }
    }

    // Emite o evento, chamando todos os listeners associados
    EmmitData emit(const char* eventName) {
        EmmitData data;
        data.timestamp = millis();
        data.eventName = eventName;
        for (int i = 0; i < MAX_EVENTS; i++) {
            if (strcmp(events[i], eventName) == 0) {
                for (int j = 0; j < MAX_LISTENERS; j++) {
                    if (listeners[i][j] != nullptr) {
                        listeners[i][j](); // Chama o callback
                        data.result = "Success";
                    }
                }
            } else {
                data.result = "Event not found";
            }
        }
        data.finished = true;
        return data; 
    }

private:
    char events[MAX_EVENTS][20]; // Lista de nomes de eventos
    Callback listeners[MAX_EVENTS][MAX_LISTENERS]; // Lista de callbacks para cada evento
};

EventEmitter emitter; // Instância global do EventEmitter