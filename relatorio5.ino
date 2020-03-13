/*
Diogo Neiss, Leo Lobato e Lucas Saliba
*/

int entrada1 = 0;   
int entrada2 = 0;
int opCode = 0;
int led1 = 11;
int ledA = 13;
int ledB = 12;
int ledCout = 10;

int portaAnd(int a, int b);
int portaor(int a, int b);
int soma(int a, int b);
int portanot(int a);
void printarBit(int led, int bit);

int saida;

void setup() {
	Serial.begin(9600);     
	pinMode(led1,OUTPUT);
	pinMode(ledA,OUTPUT);
	pinMode(ledB,OUTPUT);
	pinMode(ledCout,OUTPUT);
	
}

void loop() {
	if (Serial.available() > 0) {
		
		//arranjo que receberá a entrada
		char entradatotal[4];
		
		//ler serial, converter em char* e enviar pra lá
		Serial.readString().toCharArray(entradatotal, 4);
		Serial.print("Entrada inserida: ");
		
		Serial.print(entradatotal);
		Serial.println();
		
		//conversão atoi
		entrada1 = (int)(entradatotal[0])- 48;
		entrada2 = (int)(entradatotal[1] - 48);
		opCode = (int)(entradatotal[2])- 48 ;
		
		
		//prints das entradas, para testar o cast
		Serial.print("entrada1= ");
		Serial.print(entrada1);
		printarBit(ledA, entrada1);
		Serial.println();
		
		Serial.print("entrada2= ");
		Serial.print(entrada2);
		printarBit(ledB, entrada2);
		Serial.println();
		
		Serial.print("op code= ");
		Serial.print(opCode);
		Serial.println();
		
		//verificar se a entrada é um num
		int valido = (entradatotal[0] >= '0' && entradatotal[0] <= '9' && entradatotal[1] >= '0' && entradatotal[1] <= '9' && entradatotal[2] >= '0' && entradatotal[2] <= '9');
		
		if (valido)
		{
			
			//resetar os outputs
			printarBit(ledCout, 0);
			printarBit(led1, 0);
			
			
			char op = entradatotal[2];
			int resp = 0;
			//and 0
			if (opCode == 0){
				Serial.print("and= ");
				resp = portaAnd(entrada1 , entrada2);
				Serial.print(resp);
				Serial.println();
			}
			//or 1
			else if (opCode == 1){
				Serial.print("or= ");
				resp = portaor(entrada1 , entrada2);
				Serial.print(resp);
				Serial.println();
			}
			//not 2
			else if (opCode == 2){
				Serial.print("not a = ");
				resp = portanot(entrada1);
				Serial.print(resp);
				Serial.println();
			}
			//soma 3
			else if (opCode == 3){
				Serial.print("soma= ");
				resp = soma(entrada1 , entrada2);
				
				if(resp > 1){
					//vai1
					printarBit(ledCout, 1);	
					Serial.print("Vai1 = VERDADEIRO. Soma: ");
					
				}
				else
					Serial.print("Vai1 = FALSO. Soma: ");
				
				Serial.println();
				
				Serial.print(resp);
				Serial.println();
			}
			printarBit(led1, resp);
			Serial.print("Fim do programa.");
			Serial.println();
		}  
	}
}
void printarBit(int led, int bit){
	digitalWrite(led, bit % 2);
}

int portaor(int a, int b)
{
	return(a|b);
}

int portaAnd(int a, int b)
{
	return(a&b);
}

int portanot(int a)
{
	int resp = 0;
	if(a == 0)
		resp = 1;
	return resp;
}

int soma(int a, int b){
	return a+b;
}

