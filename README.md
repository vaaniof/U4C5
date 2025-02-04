# 🚦 Atividade 1 - Semáforo com Raspberry Pi Pico

## 📌 Descrição
Este projeto implementa um sistema de semáforo utilizando um Raspberry Pi Pico. O LED RGB conectado aos GPIOs 11, 12 e 13 alterna entre as cores vermelho, amarelo e verde a cada 3 segundos. Além disso, uma mensagem é exibida na porta serial a cada 1 segundo para indicar o funcionamento do sistema.

## 🎯 Requisitos
- Início na cor vermelha, seguido de amarelo e verde.
- Temporizador com atraso de 3 segundos (3.000 ms).
- Mudança de estado dos LEDs na função de callback do temporizador.
- Impressão de mensagem na porta serial a cada 1 segundo (1.000 ms).
- Uso do LED RGB com GPIOs 11, 12 e 13 na ferramenta BitDogLab.
- Abra a pasta especifica dessa atividade a U4C5T1 para compilação correta do código.

## 🛠️ Hardware Utilizado
- Raspberry Pi Pico
- LED RGB conectado aos GPIOs 11, 12 e 13
- Resistores adequados para os LEDs

## 🚀 Como Rodar o Código
### Configurar o Ambiente:
1. Instale o SDK do Raspberry Pi Pico.
2. Configure a compilação com CMake.
3. Utilize o simulador Wokwi ou BitDogLab para testar o código.

### Compilar e Executar:
```sh
mkdir build
cd build
cmake ..
make
```
Carregue o arquivo `.uf2` no Raspberry Pi Pico.

### Testar no Hardware:
1. Observe a alternância das cores do LED RGB.
2. Verifique a saída serial para confirmar o funcionamento.

## 📝 Estrutura do Código
### Inicialização
- Configura os GPIOs 11, 12 e 13 como saídas para o LED RGB.
- Inicializa a comunicação serial para exibir mensagens.

### Temporizador Principal
- Usa `add_alarm_in_ms(3000, callback_semaforo, NULL, true);` para alternar as cores do semáforo a cada 3 segundos.

### Temporizador Serial
- Usa `add_alarm_in_ms(1000, callback_serial, NULL, true);` para exibir mensagens na porta serial a cada 1 segundo.

### Funções de Callback
- **callback_semaforo**: Alterna entre as cores do semáforo (vermelho → amarelo → verde).
- **callback_serial**: Exibe uma mensagem na porta serial indicando o estado atual do semáforo.

# Atividade 2 - Controle de LEDs com Temporizador e Botão

## 📌 Descrição
Este projeto implementa o controle de três LEDs utilizando um botão e um temporizador no **Raspberry Pi Pico**. Ao pressionar o botão, os LEDs acendem e mudam de estado automaticamente a cada 3 segundos, seguindo uma sequência pré-definida. O botão só pode ser pressionado novamente após o ciclo ser concluído.

## 🎯 Requisitos
1. Ao pressionar o botão (GPIO 5), os três LEDs (GPIOs 11, 12 e 13) acendem simultaneamente.
2. A cada 3 segundos:
   - Apenas dois LEDs permanecem acesos.
   - Depois, apenas um LED permanece aceso.
   - Por fim, todos os LEDs se apagam.
3. A mudança de estado dos LEDs deve ser feita através de **funções de callback do temporizador**.
4. O botão só pode ser pressionado novamente **depois que todos os LEDs forem desligados**.
5. O código deve ser testado na **ferramenta BitDogLab**.
6. Implementação de **debounce por software** para evitar acionamentos errados do botão.
7. Abra a pasta especifica dessa atividade a U4C5T2 para compilação correta do código.

## 🛠️ Hardware Utilizado
- **Raspberry Pi Pico**
- **LEDs** conectados aos GPIOs **11, 12 e 13**
- **Botão** conectado ao GPIO **5**
- **Resistores de pull-up internos** para o botão

## 🚀 Como Rodar o Código
1. **Configurar o Ambiente:**
   - Instale o SDK do Raspberry Pi Pico.
   - Configure a compilação com CMake.
   - Utilize o simulador Wokwi ou BitDogLab para testar o código.

2. **Compilar e Executar:**
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
   - Carregue o arquivo `.uf2` no Raspberry Pi Pico.
   
3. **Testar no Hardware:**
   - Pressione o botão e observe a sequência de LEDs.
   - O botão só funcionará novamente após todos os LEDs se apagarem.

## 📝 Estrutura do Código
- **Inicializa GPIOs** para LEDs e botão.
- **Configura interrupção** no botão.
- **Implementa debounce por software**.
- **Usa `add_alarm_in_ms(3000, callback, NULL, false);`** para alternar LEDs a cada 3 segundos.
- **Impede múltiplas ativações do botão enquanto os LEDs ainda estão acesos**.

## 📷 Exemplo de Funcionamento
1️⃣ **Pressiona o botão →** Todos os LEDs acendem.  
2️⃣ **Após 3s →** Apenas dois LEDs ficam acesos.  
3️⃣ **Após 3s →** Apenas um LED fica aceso.  
4️⃣ **Após 3s →** Todos os LEDs apagam e o botão pode ser pressionado novamente.  

## 📚 Referências
- [Documentação oficial do Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/)  
- [BitDogLab - Simulador Educacional](https://bitdoglab.com/)  

---
💡 **Dica:** Se os LEDs não estiverem funcionando corretamente, verifique as conexões e os resistores pull-up do botão. 😊
