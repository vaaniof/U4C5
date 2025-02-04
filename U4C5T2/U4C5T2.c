#include "pico/stdlib.h"   // Biblioteca padrão do Raspberry Pi Pico
#include "hardware/gpio.h" // Biblioteca para controle de GPIOs
#include "hardware/timer.h" // Biblioteca para manipulação de temporizadores

// Definição dos pinos dos LEDs e do botão
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13
#define BUTTON 5

// Variáveis globais
volatile bool button_pressed = false; // Indica se o botão foi pressionado
volatile bool timer_running = false;  // Indica se o temporizador está em execução
volatile int led_state = 0;           // Estado atual dos LEDs

// Função de callback do temporizador: Executa a cada 3 segundos para alterar o estado dos LEDs.

int64_t timer_callback(alarm_id_t id, void *user_data) {
    switch (led_state) {
        case 0:
            // Acende os três LEDs
            gpio_put(LED_RED, 1);
            gpio_put(LED_YELLOW, 1);
            gpio_put(LED_GREEN, 1);
            led_state = 1;
            add_alarm_in_ms(3000, timer_callback, NULL, false); // Agenda a próxima mudança
            break;
        case 1:
            // Desliga o LED vermelho, mantém os outros dois acesos
            gpio_put(LED_RED, 0);
            gpio_put(LED_YELLOW, 1);
            gpio_put(LED_GREEN, 1);
            led_state = 2;
            add_alarm_in_ms(3000, timer_callback, NULL, false); // Agenda a próxima mudança
            break;
        case 2:
            // Apenas o LED verde permanece aceso
            gpio_put(LED_RED, 0);
            gpio_put(LED_YELLOW, 0);
            gpio_put(LED_GREEN, 1);
            led_state = 3;
            add_alarm_in_ms(3000, timer_callback, NULL, false); // Agenda a próxima mudança
            break;
        case 3:
            // Todos os LEDs são desligados
            gpio_put(LED_RED, 0);
            gpio_put(LED_YELLOW, 0);
            gpio_put(LED_GREEN, 0);
            led_state = 0;
            timer_running = false; // Permite que o botão inicie um novo ciclo
            break;
    }
    return 0; // Retorna 0 para indicar que o temporizador não precisa ser repetido automaticamente
}

// Função de debounce do botão: Evita leituras erradas devido ao efeito bouncing (ruído elétrico).
bool debounce() {
    static uint32_t last_time = 0; // Armazena o último tempo que o botão foi pressionado
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if ((current_time - last_time) > 50) { // Tempo mínimo de 50ms entre leituras
        last_time = current_time;
        return true;
    }
    return false;
}

// Interrupção para detectar a pressão do botão: Só permite nova ativação se o ciclo anterior já tiver terminado.

void button_isr(uint gpio, uint32_t events) {
    if (debounce() && !timer_running) { // Só permite pressionar se os LEDs estiverem desligados
        button_pressed = true;
    }
}

int main() {
    // Inicializa os pinos GPIOs dos LEDs e do botão
    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON);

    // Define os LEDs como saída
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    // Define o botão como entrada
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON); // Habilita resistor de pull-up interno para evitar flutuação no sinal

    // Configura a interrupção para detectar o acionamento do botão (bordas de descida)
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_isr);

    // Loop principal
    while (1) {
        if (button_pressed && !timer_running) {
            button_pressed = false; // Reseta o estado do botão
            timer_running = true;   // Indica que o temporizador está em execução
            add_alarm_in_ms(3000, timer_callback, NULL, false); // Inicia o ciclo dos LEDs
        }
        sleep_ms(1); // Pequena pausa para evitar sobrecarga da CPU
    }

    return 0;
}
