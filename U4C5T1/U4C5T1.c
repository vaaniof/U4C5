#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos GPIO para os LEDs
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

// Função de callback chamada periodicamente pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    static int state = 0; // Variável de estado para controlar o LED aceso

    // Liga apenas um LED por vez de acordo com o estado atual
    gpio_put(LED_RED, state == 0);
    gpio_put(LED_YELLOW, state == 1);
    gpio_put(LED_GREEN, state == 2);

    // Atualiza o estado para o próximo ciclo
    state = (state + 1) % 3;
    return true; // Retorna true para continuar a repetição do timer
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial padrão

    // Inicializa os pinos dos LEDs
    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN);

    // Define os pinos como saída
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    struct repeating_timer timer; // Estrutura para armazenar o temporizador
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); 
    // Configura um temporizador repetitivo que chama a função a cada 3 segundos

    // Loop principal
    while (true) {
        printf("Semáforo funcionando...\n"); // Mensagem indicando funcionamento
        sleep_ms(1000); // Aguarda 1 segundo antes da próxima iteração do loop
    }
}
