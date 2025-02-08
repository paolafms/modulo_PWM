# Link do vídeo:

# Controle de Servomotor e LED RGB com PWM no Raspberry Pi Pico:
- Este projeto demonstra como controlar um servomotor e um LED RGB utilizando PWM (Pulse Width Modulation) no Raspberry Pi Pico. O código foi desenvolvido em C utilizando o SDK do Raspberry Pi Pico e a ferramenta Wokwi.

# Descrição do Projeto:
O projeto consiste em controlar um servomotor e um LED RGB de forma sincronizada. O servomotor é movimentado suavemente entre 0 e 180 graus, enquanto o brilho do LED é ajustado proporcionalmente à posição do servo. O controle é realizado através de sinais PWM, que são gerados pelo Raspberry Pi Pico.

# Funcionalidades:
- Controle de Servomotor: O servomotor é posicionado em 0°, 90° e 180° com um atraso de 5 segundos entre cada posição.
- Controle de LED RGB: O brilho do LED é ajustado proporcionalmente à posição do servomotor.
- Movimentação Suave: O servomotor é movimentado suavemente entre 0° e 180° com incrementos de 5µs, enquanto o brilho do LED é ajustado em tempo real.

# Configurações:
- Servomotor: Conectado ao GPIO 22.
- LED RGB (Azul): Conectado ao GPIO 12.
- Frequência PWM: 50Hz (período de 20ms).

# Ciclo Ativo (Duty Cycle):
- 0°: 500µs (0,025% do ciclo).
- 90°: 1.470µs (0,0735% do ciclo).
- 180°: 2.400µs (0,12% do ciclo).
