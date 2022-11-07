#define OUTPUT_BUZZER 2
#define OUTPUT_LED_1 9
#define OUTPUT_LED_2 10
#define OUTPUT_LED_3 11
#define OUTPUT_LED_4 12
#define INPUT_LDR 5
#define INPUT_BOTAO_1 15
#define INPUT_BOTAO_2 16

// variável quantidade de leituras realizadas
int leituras = 0;

// armazenar as leituras realizadas
int dec_cadast[4] = {0,0,0,0};

int normalizar_entre_0_a_15(int entrada)
{


  int max_ldr = 4095;


  int min_ldr = 524;


  int numero_normalizado_entre_1_a_15 = 0;


  int valor_atual = max_ldr;


  while(valor_atual >= entrada) {

    numero_normalizado_entre_1_a_15++;
    valor_atual -= 273;


  if(valor_atual <= min_ldr) {
    numero_normalizado_entre_1_a_15 = 16;
    break;
  }

  }
  
  return 16 - numero_normalizado_entre_1_a_15;
  
}


void decimal_to_binarie(int n, int binario_inverso[4])
{

  for(int i = 0; i < 4; i++) {

    binario_inverso[i] = 0;

  }
 
  int i = 0;

  while (n > 0) {
  
      binario_inverso[i] = n % 2;
      n = n / 2;
      i++;

  }

}

void acender_leds(int binario_inverso[4]) 
{


  int output[4] = {OUTPUT_LED_4, OUTPUT_LED_3, OUTPUT_LED_2, OUTPUT_LED_1};

  for(int i = 0; i < 4; i++) {

    // Acendendo ou apagando um LED com base no número binário passado.
    switch(binario_inverso[i]) {

      case 1:
        digitalWrite(output[i], HIGH);
      break;

      case 0:
        digitalWrite(output[i], LOW);

    }

  }

}

int hertz_do_numero(int decimal_normalizado)
{

  return decimal_normalizado*200;

}

void som_erro() 
{

  for(int i = 0; i < 3; i++) {

    tone(OUTPUT_BUZZER, 3000);
    delay(500);
    noTone(OUTPUT_BUZZER);
    delay(100);

  }

}

void setup() 
{
  Serial.begin(19200);


  pinMode(OUTPUT_BUZZER, OUTPUT);
  pinMode(OUTPUT_LED_4, OUTPUT);
  pinMode(OUTPUT_LED_3, OUTPUT);
  pinMode(OUTPUT_LED_2, OUTPUT);
  pinMode(OUTPUT_LED_1, OUTPUT);
  pinMode(INPUT_LDR, INPUT);
  pinMode(INPUT_BOTAO_1, INPUT);
  pinMode(INPUT_BOTAO_2, INPUT);


}

void loop() 
{

  // leitura analógica do sensor LDR
  int leitura = analogRead(INPUT_LDR);

  Serial.println("Leitura realizada:");
  Serial.println(leitura);


  int valor_normalizado = normalizar_entre_0_a_15(leitura);

  int binario_inverso[4];


  decimal_to_binarie(valor_normalizado, binario_inverso);


  acender_leds(binario_inverso);

  int botao_1_esta_pressionado = digitalRead(INPUT_BOTAO_1);

  if(botao_1_esta_pressionado) {


    if(leituras < 4) {

      dec_cadast[leituras] = valor_normalizado;

      leituras++;
      acender_leds(binario_inverso);
      tone(OUTPUT_BUZZER, hertz_do_numero(valor_normalizado));

      delay(1000);
      noTone(OUTPUT_BUZZER);
    } 
    else {

      som_erro();

    }

  }

  int botao_2_esta_pressionado = digitalRead(INPUT_BOTAO_2);

  if(botao_2_esta_pressionado) {

    if(leituras != 4) {

      som_erro();

    } else {

      for(int i = 0; i < 4; i++) {


        int binario_inverso[4];


        decimal_to_binarie(dec_cadast[i], binario_inverso);
        acender_leds(binario_inverso);

        tone(OUTPUT_BUZZER, hertz_do_numero(dec_cadast[i]));
        delay(500);
        noTone(OUTPUT_BUZZER);
      }
    }
  }
}
