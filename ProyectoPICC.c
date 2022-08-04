//Libreria del microcontrolador
#include <ProyectoPICC.h>
//#difine de algunos componentes
#define use_portb_kbd TRUE
//Librerias de los componentes
#include <lcd.c>
#include "C:\Users\Christian Rodriguez\Documents\Documentos\Pic C Compiler\kbd4x4_1.C"
#include "C:\Users\Christian Rodriguez\Documents\Documentos\Pic C Compiler\TONES.C"

//Prototipos de funciones
void MotorP(int, int);
void Notas(char);
void Contador();
void Datos(int);
//Funcion principal
void main()
{
   char k;   //Declaramos k como una variable local en el main
   port_b_pullups(0xFF);  //puerto b como entradas pulliup
   lcd_init();        //iniciamos el lcd
   lcd_putc("\BIENVENIDO!!\n");   //msj de bienvenida
   delay_ms(1000);

   while(TRUE)   //ciclo infinito
   {
      //lcd_putc("\f");
      lcd_putc("\aElija una opcion");  //msj del menu
      k = kbd_getc();

      switch(k){    //un swiitch para determinar cual funcion ejecutar
      
      case '1': {
      //Motor a Pasos
      lcd_putc("\f");
      lcd_putc("\Motor a Pasos");   //
      while(k != '*'){     //ciclo paa ejecutar el proceso, se sale con *
      k = kbd_getc();    
      if(k == '1'){      //si se presiona 1 entonces se gira le motor a la derecha
         MotorP(100, 1);
      }
      if (k == '3'){     //si se presiona 3, el motor da un giro a la izquierda
         MotorP(100, 2);
      }
      }
      break;
      }
      
      case '2': {       
      //Calculadora
      lcd_putc("\f");
      lcd_putc("\Calculadora");
      delay_ms(3000);
      k = kbd_getc();
      while(k != '*'){     //ciclo para ejecutar el proceso de la calculadora
      char n1, n2, op;    //variables para guardar las entradas
      int aux1, aux2;     //variables para guardar la conversion a int
         do{         //ciclo para leer el primer caracter
         //lcd_putc("\f");
         lcd_putc("\aIngrese num 1");   
         n1 = kbd_getc();
         //delay_ms(500);
         }while(n1 == '\0');
         lcd_putc("\f");
         do{            //ciclo para leer el segundo caracter que es el ooperador
         //delay_ms(500);
         //lcd_putc("\f");
         lcd_putc("\aIngrese operacion");
         op = kbd_getc();
         }while(op == '\0');
         lcd_putc("\f");
         do{                //ciclo para leer le tercer caracter
         //delay_ms(1000);
         //lcd_putc("\f");
         lcd_putc("\aIngrese num 2");
         n2 = kbd_getc();   
         }while(n2 == '\0');
      aux1 = n1 - '0';      //Conversion de caracter a entero, por medio de una resta para cambiar el cofigo ascii
      aux2 = n2 - '0';

      
      switch(op){      //segun el caracter del operador, se va a realizar alguna operacion matematica
      case '+': {
         lcd_putc("\f");
         printf(lcd_putc, "%d", aux1 + aux2);    
         delay_ms(5000);
         break;
      }
      case '-': {
         lcd_putc("\f");
         printf(lcd_putc, "%d", aux1 - aux2);
         delay_ms(5000);
         break;
      }
      case 'X': {
         lcd_putc("\f");
         printf(lcd_putc, "%d", aux1 * aux2);
         delay_ms(5000);
         break;
      }
      case '/': {
         lcd_putc("\f");
         printf(lcd_putc, "%d", aux1 / aux2);
         delay_ms(5000);
         break;
      }
 
      }
      do{       //ciclo que nos permite decidir si repetir el bucle o roperlo
         
         //delay_ms(500);
         //lcd_putc("\f");
         lcd_putc("\aReset con ON/C");
         k = kbd_getc();
         }while(k == '\0');
     
      }
      break;
      
      }
      
      case '3': {       
      //HEX del caracter mostrado
      lcd_putc("\f");
      lcd_putc("\Char a HEX");
      delay_ms(1000);
      k = kbd_getc();
      while(k != '*'){    //ciclo para realizar el proceso
      int i = 0;      
      lcd_putc("\f");
      lcd_putc("\ingrese Valor:");   //solicitamos que ingrese un numero
      delay_ms(500);
      char cad[3];                   //creamos un cadena de caracteres para almacenar el numero a convertir
      lcd_putc("\f");
      do{                            //en este ciclo almacenamos los datos del usuario en la cadena
      k = kbd_getc();
      
      if(k != '\0'){
         cad[i] = k;
         lcd_putc(k);
         i++;
         //
         delay_ms(1000);
         
      }
      }
      while(k != '=');                  //ciclo para trabajar y mostrar el resultado
      
         int aux1, aux2, aux3, hex;    //variables que vamos a usar para convertir los caracteres y gurdarlos en una sola variable
         aux1 = cad[0] - '0';          //conversion de los caracteres en entero por medio de una resta para modificar el codigo ascii
         aux2 = cad[1] - '0';
         aux3 = cad[2] - '0';
         lcd_putc("\f");
         lcd_putc("Convirtiendo");
         hex = (aux1 * 100) + (aux2 * 10) + aux3;    //gurdamos los datos en una sola variable 
         delay_ms(1000);
         lcd_putc("\f");
         printf(lcd_putc, "%X",hex);             //mostramos la variable hex en lcd pero usando %X par amostrarlo en hexadecimal
         delay_ms(5000);
         delay_ms(1000);
      do{
         lcd_putc("\aReset con ON/C");       //ciclo par ael erset
         k = kbd_getc();
         }while(k == '\0');
      }
      break;
      }
      
      case '4': {
      //Notas musicales
      lcd_putc("\f");
      lcd_putc("\Notas");
      while(k != '*'){     //ciclo par aealizar el proceso
      k = kbd_getc();
      Notas(k);             //los caracteres que se leen del kbd los mandamos a la funcion
      }
      break;
      }
      
       case '5': {
      //Contador
      lcd_putc("\f");   //Limpiar
      lcd_putc("\Contador");  //mensajito
      //while(k != '*'){
      k = kbd_getc();
      int i = 0;                   //variable para poder hacer incrementos y decrementos
      while(k != '*'){
         //i++;
         //lcd_putc("\f");
         k = kbd_getc();               //leemos el kbd
         if(k == '+'){i++;lcd_putc("\f");printf(lcd_putc, "%3u", i);delay_ms(500);}    //si se lee el + entonces se incrementa en 1
         if(k == '-'){i--;lcd_putc("\f");printf(lcd_putc, "%3u", i);delay_ms(500);}    //si sse lee el -  se decrementa en 1
         //k = kbd_getc();
         //if(k == '*'){break;}
      }
      
      
      break;
      }
      case '6': {
      //Datos del alumno
      lcd_putc("\f");
      lcd_putc("\Datos");  
      while(k != '*'){     //ciclo pra realizar el proceso
         k = kbd_getc();   
         if(k == '='){     //si el valor leido es = entonces muestra los datos de Christian
         datos(1);
         }
         if(k == '+'){     //Si el valor leido es + entonces muestra los datos de Marco
         Datos(2);
         }
      }
      break;
      }
      }
 

   }
}

//Funciones
void MotorP(int pasos, int direccion){
   if (direccion == 1){
   for(int i = 1; i <= pasos; i++){     //Generamos pulsos para mover el motor a pasos
      output_high(PIN_C0);
      delay_ms(10);
      output_low(PIN_C0);
      delay_ms(10);
   }
   }
   else{
   for(int i = 1; i <= pasos; i++){   //Pulsos pero en otro pin
      output_high(PIN_C1);
      delay_ms(10);
      output_low(PIN_C1);
      delay_ms(10);
   }
   }
}

void Notas(char c){

   switch(c){     //Dependiendo del caracter leido se manda un tono el pin c2
   case '1':{
   generate_tone(Ab_NOTE[4], 10);
   break;
   }
   case '2':{
   generate_tone(G_NOTE[4], 10);
   break;
   }
   case '3':{
   generate_tone(C_NOTE[4], 10);
   break;
   }
   case '4':{
   generate_tone(D_NOTE[4], 10);
   break;
   }
   case '5':{
   generate_tone(E_NOTE[4], 10);
   break;
   }
   case '6':{
   generate_tone(Ab_NOTE[4], 10);
   break;
   }
   case '7':{
   generate_tone(Ab_NOTE[4], 10);
   break;
   }
   case '8':{
   generate_tone(Eb_NOTE[4], 10);
   break;
   }
   case '9':{
   generate_tone(Db_NOTE[4], 10);
   break;
   }
   }
}

void Contador(){    //no se uso
      for(int i = 0; i < 1000; i++){
      lcd_putc("\f");
      printf(lcd_putc, "%3u", i);
      delay_ms(500);
   } 
}

void Datos(int h){  //Se manda en el lcd los datos del alumno
   if(h == 1){
   lcd_putc("\f");
   lcd_putc("\Christian R. H.");
   lcd_putc("\n201848582");
   }
   else{
      lcd_putc("\f");
   lcd_putc("\Marco R. G.");
   lcd_putc("\n201830279");
   }
}
