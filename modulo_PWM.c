#include <stdio.h> 
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22    // GPIO do servo motor
#define LED_PIN 12      // GPIO do LED RGB (azul)
#define PWM_FREQ 50     // Frequência do PWM (50Hz)
#define PWM_WRAP 20000  // Período de 20ms (20.000µs)
#define DUTY_180 2400   // 2.400µs (0,12% do ciclo) - 180 graus
#define DUTY_90 1470    // 1.470µs (0,0735% do ciclo) - 90 graus
#define DUTY_0 500      // 500µs (0,025% do ciclo) - 0 graus
#define INCREMENTO 5    // Incremento de ±5µs
#define ATRASO_MS 10    // Atraso de 10ms entre os ajustes

void setup_pwm(uint pin, uint wrap, uint duty) {
    gpio_set_function(pin, GPIO_FUNC_PWM); // Define GPIO como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(pin); // Obtém o slice PWM correspondente

    pwm_set_wrap(slice_num, wrap);   // Configura o período do PWM
    pwm_set_clkdiv(slice_num, 125.0); // Divide o clock para ajustar a frequência (50Hz)
    pwm_set_gpio_level(pin, duty);   // Define o duty cycle inicial

    pwm_set_enabled(slice_num, true); // Ativa o PWM
}

void setup_led(uint pin, float brightness) {
    gpio_set_function(pin, GPIO_FUNC_PWM); // Define GPIO como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(pin); // Obtém o slice PWM correspondente
    uint wrap = 255; // Faixa de 0 a 255 para controle de intensidade
    pwm_set_wrap(slice_num, wrap);  // Define o limite superior para o PWM
    pwm_set_clkdiv(slice_num, 125.0); // Define o divisor de clock para a frequência

    uint duty = (uint)(brightness * wrap);  // Calcula o ciclo ativo baseado no brilho
    pwm_set_gpio_level(pin, duty);  // Define a intensidade do LED
    pwm_set_enabled(slice_num, true); // Ativa o PWM para o LED
}

void movimento_suave() {
    int duty = DUTY_0;  // Começar a movimentação de 0 graus

    // Movimenta do 0 para 180 graus
    while (duty <= DUTY_180) {
        setup_pwm(SERVO_PIN, PWM_WRAP, duty);  // Ajusta a posição do servo
        float brightness = (duty - DUTY_0) / (float)(DUTY_180 - DUTY_0);  // Calcula brilho baseado na posição
        setup_led(LED_PIN, brightness);  // Ajusta o brilho do LED
        printf("Posicionando servo em %dµs, LED brilho %.2f\n", duty, brightness);
        sleep_ms(ATRASO_MS); // Aguarda 10ms para o ajuste suave
        duty += INCREMENTO;  // Incrementa o ciclo ativo
    }

    // Movimenta de volta do 180 para 0 graus
    while (duty >= DUTY_0) {
        setup_pwm(SERVO_PIN, PWM_WRAP, duty);  // Ajusta a posição do servo
        float brightness = (duty - DUTY_0) / (float)(DUTY_180 - DUTY_0);  // Calcula brilho baseado na posição
        setup_led(LED_PIN, brightness);  // Ajusta o brilho do LED
        printf("Posicionando servo em %dµs, LED brilho %.2f\n", duty, brightness);
        sleep_ms(ATRASO_MS); // Aguarda 10ms para o ajuste suave
        duty -= INCREMENTO;  // Decrementa o ciclo ativo
    }
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial (opcional)

    // Posiciona o servo em 180 graus (ciclo de 2.400µs)
    setup_pwm(SERVO_PIN, PWM_WRAP, DUTY_180); 
    setup_led(LED_PIN, 1.0);  // LED totalmente aceso
    printf("Servo posicionado em 180 graus, LED aceso.\n");
    sleep_ms(5000); // Aguarda 5 segundos na posição de 180 graus

    // Posiciona o servo em 90 graus (ciclo de 1.470µs)
    setup_pwm(SERVO_PIN, PWM_WRAP, DUTY_90); 
    setup_led(LED_PIN, 0.5);  // LED com brilho médio
    printf("Servo posicionado em 90 graus, LED com brilho médio.\n");
    sleep_ms(5000); // Aguarda 5 segundos na posição de 90 graus

    // Posiciona o servo em 0 graus (ciclo de 500µs)
    setup_pwm(SERVO_PIN, PWM_WRAP, DUTY_0); 
    setup_led(LED_PIN, 0.0);  // LED apagado
    printf("Servo posicionado em 0 graus, LED apagado.\n");
    sleep_ms(5000); // Aguarda 5 segundos na posição de 0 graus

    // Realiza a movimentação suave do servo entre 0 e 180 graus
    printf("Iniciando movimentação suave.\n");
    while (1) {
        movimento_suave();  // Movimenta suavemente entre 0 e 180 graus
    }

    printf("Finalizando programa.\n");
    return 0;
}