/**

ATIVIDADE 06:

Desenvolver um programa para o Arduino que faça a leitura
de um sensor ultrassônico e acione dois motores quando
observado um objeto a uma distância inferior à um metro.

*/

enum rotate_direction {
	normal,
  	inverse
};

float get_sensor_distance();
void rotate_motor(int first_pin, int second_pin, rotate_direction direction);
void turn_off_motor(int first_pin, int second_pin);

// Sensor
#define ECHO_PIN 2
#define TRIGGER_PIN 3
#define MIN_DISTANCE 100.00

// First Motor
#define MOTOR_PIN_01 5 // Pin 14 of L293
#define MOTOR_PIN_02 6 // Pin 10 of L293

// Second Motor
#define MOTOR_PIN_03 10 // Pin 7 of L293
#define MOTOR_PIN_04 9 // Pin 2 of L293

float get_sensor_distance()
{
  	digitalWrite(TRIGGER_PIN, LOW);
  	delayMicroseconds(2);

  	digitalWrite(TRIGGER_PIN, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIGGER_PIN, LOW);

  	long duration = pulseIn(ECHO_PIN, HIGH);

  	return duration * 0.034 / 2;
}

void rotate_motor(int first_pin, int second_pin, rotate_direction direction)
{
	if (direction == inverse)
    {
  		digitalWrite(first_pin, LOW);
  		digitalWrite(second_pin, HIGH);
    	delay(1000);

      	return;
    }

	digitalWrite(first_pin, HIGH);
    digitalWrite(second_pin, LOW);
   	delay(1000);
}

void turn_off_motor(int first_pin, int second_pin)
{
	digitalWrite(first_pin, LOW);
    digitalWrite(second_pin, LOW);
}

void setup()
{
 	Serial.begin(115200);

  	pinMode(ECHO_PIN, INPUT);
  	pinMode(TRIGGER_PIN, OUTPUT);

  	pinMode(MOTOR_PIN_01, OUTPUT);
  	pinMode(MOTOR_PIN_02, OUTPUT);
  	pinMode(MOTOR_PIN_03, OUTPUT);
  	pinMode(MOTOR_PIN_04, OUTPUT);
}

void loop()
{
  	// Turn off all motors
  	turn_off_motor(MOTOR_PIN_01, MOTOR_PIN_02);
    turn_off_motor(MOTOR_PIN_03, MOTOR_PIN_04);

  	// Get current sensor distance
  	float distance = get_sensor_distance();
  	Serial.print("Distância calculada: ");
  	Serial.println(distance);

  	if (distance <= MIN_DISTANCE)
    {
    	// Rotate all motors clockwise for 2 seconds
  		rotate_motor(MOTOR_PIN_01, MOTOR_PIN_02, normal);
    	rotate_motor(MOTOR_PIN_03, MOTOR_PIN_04, normal);

    	// Rotate all motors counterclockwise for 2 seconds
   		rotate_motor(MOTOR_PIN_01, MOTOR_PIN_02, inverse);
   		rotate_motor(MOTOR_PIN_03, MOTOR_PIN_04, inverse);
    }

  	delay(1000);
}
