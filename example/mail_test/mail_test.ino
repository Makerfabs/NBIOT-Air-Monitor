#define DEBUG true

#define POWER_3V3 21
#define POWER_1V8 48

#define SDA 17
#define SCL 18

#define BUTTON_PIN 8
#define LED_PIN 47

#define BAT_PIN 14

#define IO_RXD2 1
#define IO_TXD2 2

#define IO_GSM_PWRKEY 42
#define IO_GSM_RST 40
#define IO_GSM_DTR 39

#define EMAIL_SERVER "smtp.163.com"
#define EMAIL_ID "EMAIL_ID"
#define EMAIL_POP_PWD "EMAIL_POP_PWD"
#define FROM_NAME "Sensor Alarm"
#define FROM_ADD "XXXXXXX@163.com"
#define TO_NAME "Myself"
#define TO_ADD "XXXXXXX@163.com"

HardwareSerial mySerial2(2);

void setup()
{

    Serial.begin(115200);
    mySerial2.begin(115200, SERIAL_8N1, IO_RXD2, IO_TXD2);

    Serial.println("Maduino Zero LTE CAT-M1 CAT1 NB1/NB2 Test Start!");
    Serial.println("Wait a few minutes for LTE star");
    pin_init();

    delay(3000);

    at_init();
    email_task();
}

void loop()
{
    while (mySerial2.available() > 0)
    {
        Serial.write(mySerial2.read());
        yield();
    }
    while (Serial.available() > 0)
    {
        mySerial2.write(Serial.read());
        yield();
    }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    mySerial2.println(command);
    long int time = millis();
    while ((time + timeout) > millis())
    {
        while (mySerial2.available())
        {
            char c = mySerial2.read();
            response += c;
        }
    }
    if (debug)
    {
        Serial.print(response);
    }
    return response;
}

void pin_init()
{
    pinMode(POWER_3V3, OUTPUT);
    pinMode(POWER_1V8, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BAT_PIN, INPUT);

    pinMode(IO_GSM_RST, OUTPUT);
    pinMode(IO_GSM_PWRKEY, OUTPUT);

    digitalWrite(POWER_3V3, HIGH);
    digitalWrite(POWER_1V8, HIGH);
    digitalWrite(LED_PIN, HIGH);

    digitalWrite(IO_GSM_RST, HIGH);
    delay(1000);
    digitalWrite(IO_GSM_RST, LOW);
    delay(500);
    digitalWrite(IO_GSM_PWRKEY, HIGH);
    delay(1000);
    digitalWrite(IO_GSM_PWRKEY, LOW);
}

void at_init()
{
    Serial.println(F("void at_init()"));

    sendData("AT", 1000, DEBUG);
    sendData("AT+CPIN?", 1000, DEBUG);
    sendData("AT+CCID", 1000, DEBUG);
    sendData("AT+CSQ", 1000, DEBUG);
    sendData("AT+COPS?", 1000, DEBUG);
    sendData("AT+CGATT?", 1000, DEBUG);
    sendData("AT+CNACT=0,1", 1000, DEBUG);
    sendData("AT+CNACT?", 1000, DEBUG);

    // Synchronize time 同步时间
    sendData("AT+CNTPCID?", 1000, DEBUG);
    sendData("AT+CNTP=\"ntp1.aliyun.com\",32", 1000, DEBUG);
    sendData("AT+CNTP", 1000, DEBUG);
    sendData("AT+CCLK?", 1000, DEBUG);
}

void email_task()
{
    String temp = "";
    sendData("AT+EMAILCID=0", 1000, DEBUG);
    sendData("AT+EMAILTO=30", 1000, DEBUG);

    // Your mail server port
    temp = temp + "AT+SMTPSRV=\"" + EMAIL_SERVER + "\",25";
    sendData(temp, 1000, DEBUG);
    // Your email id and smtp password not email password
    temp = "";
    temp = temp + "AT+SMTPAUTH=1,\"" + EMAIL_ID + "\",\"" + EMAIL_POP_PWD + "\"";
    sendData(temp, 1000, DEBUG);
    // Sender Address
    temp = "";
    temp = temp + "AT+SMTPFROM=\"" + FROM_ADD + "\",\"" + FROM_NAME + "\"";
    sendData(temp, 1000, DEBUG);
    // Recipient Address
    temp = "";
    temp = temp + "AT+SMTPRCPT=0,0,\"" + TO_ADD + "\",\"" + TO_NAME + "\"";
    sendData(temp, 1000, DEBUG);

    // Subject
    sendData("AT+SMTPSUB=\"Makerfabs Email Test\"", 1000, DEBUG);
    // Set body length
    sendData("AT+SMTPBODY=13", 1000, DEBUG);
    // Set body
    sendData("Some test txt.\n\r", 1000, DEBUG);

    // Send
    sendData("AT+SMTPSEND", 1000, DEBUG);
}