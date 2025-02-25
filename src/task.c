#include "task.h"
//#include "yolov3.h"
int flag1=0;
int flag2=0;
float a=0.0;
int b=0;
int c=0;
 float d=0.0;
 float e=0.0;
// void Led_Pwm_Test(void)
// {
//     int flag = 0;
//     int time = 0; 
//     Ledhandler led;
//     Led_Init(500,&led);
//     while(1)
//     {
//       time = 0;
//       while(!flag)
//       {
//         Led_High(&led);
//         usleep(time*30);
//         Led_Low(&led);
//         usleep((255-time)*30);
//         if((time++)==255)
//           flag = 1;
//       }
//       time = 0;
//       while(flag)
//       {
//         Led_High(&led);
//         usleep((255-time)*30);
//         Led_Low(&led);
//         usleep(time*30);
//         if((time++)==255)
//           flag = 0;
//       }
//     }
// }

// void Led_Test(void)m  
// {
//     int time = 1000000; 
//     Ledhandler led;
//     Led_Init(500,&led);
//     while(1)
//     {
//         Led_Low(&led);
//         usleep(time);
//         Led_High(&led);
//         usleep(time);
//     }
// }



void Led_Pwm_Test(void)
{
    int flag = 0;
    int time = 0; 
    Ledhandler led;
    Led_Init(500,&led);
    while(1)
    {
      time = 0;
      while(!flag)
      {
        Led_High(&led);
        usleep(time*30);
        Led_Low(&led);
        usleep((255-time)*30);
        if((time++)==255)
          flag = 1;
      }
      time = 0;
      while(flag)
      {
        Led_High(&led);
        usleep((255-time)*30);
        Led_Low(&led);
        usleep(time*30);
        if((time++)==255)
          flag = 0;
      }
    }
}

void Led_Test(void)
{
    int time1 = 1000000; 
    Ledhandler led;
    Led_Init(500,&led);

    int time = 100000;
    Sht20Init("/dev/i2c-1",0x40);
    oled_init();
    float buff[2];
    while(1&&flag1)
    {   
    Refresh();
    Led_Low(&led);
    usleep(time1);
    Led_High(&led);
    usleep(time1);//led����˸
    Refresh();

    Sht20GetData(buff);
    printf("�¶�Ϊ:%f \tʪ��Ϊ:%f\n",buff[0],buff[1]);
    usleep(2000000);
  

//     float buff[3];
//     adxl345_Init();
//     adxl345_GetData(buff);
//     printf("AngleX:%f AngleY:%f AngleZ:%f\n",buff[0],buff[1],buff[2]);

//     a=buff[0];
//     d=buff[1];
//     e=buff[2];
//     char s[20];
//     gcvt(a, 6, s);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
//     char s1[20];
//    gcvt(d, 6, s1);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
//    char s2[20];
//    gcvt(e, 6, s2);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();

    
     b=buff[1]/10;
     c=buff[1]-b*10;

    a=buff[0];
    char s[20];
    gcvt(a, 6, s);  
    ColorTurn(TURNOVER_COLOR);
    DisplayTurn(NORMAL_DISPLAY);
    ShowString(0,0,s,size1206);
    Refresh();
    usleep(time);//Һ������ʾ

   pca9557_init("/dev/i2c-1");
   pca9557_setnum(b,c,0,0);
   pca9557_show(); //�������ʾ
    }

}

void Led_Test4(void)
{
    int time = 100000; 
    Ledhandler led;
    Led_Init(452,&led);

    char buff[1024];
    float buff1[1024];
     int buff2[1024];
    Esp32c3* esp32c3ble = (Esp32c3*)malloc(sizeof(Esp32c3));
    memset(esp32c3ble,0,sizeof(Esp32c3));
    Esp32Init(esp32c3ble,"/dev/ttyAMA1");
    Esp32AtCmd(esp32c3ble,"+++");
    usleep(1000000);
    Esp32AtCmd(esp32c3ble,"AT+RESTORE");
    Esp32AtCmd(esp32c3ble,"AT+CIPCLOSE");
    Esp32AtCmd(esp32c3ble,"AT+RESTORE");
    usleep(5000000);

    Esp32AtCmd(esp32c3ble,"ATE0");//ȡ������
    Esp32AtCmd(esp32c3ble,"AT");//��ѯ�Ƿ���������
    Esp32AtCmd(esp32c3ble,"AT+GMR");//��ѯ�汾��Ϣ

    Esp32AtCmd(esp32c3ble,"AT+CWMODE=2"); //����esp32ΪSoftAP
    Esp32AtCmd(esp32c3ble,"AT+CWSAP=\"ESP32_SOFTAP\",\"1234567890\",5,3");//����ESP32�ȵ��˺ź�����
    usleep(10000000);//10s
    printf("Wait PC connect...\n");

    memset(buff,0,sizeof(1024));
    printf("ȷ��PC�Ƿ���UDP������");
    printf("����Ѿ�����,������yes\n");
    while (1)
    {
        scanf("%s",buff);
        printf("%s",buff);

        if(strstr(buff,"yes") == NULL)
            continue;
        else
            break;
        memset(buff,0,sizeof(1024));
        usleep(1000000);
    }
    Esp32AtCmd(esp32c3ble,"AT+CIPSTART=\"UDP\",\"192.168.4.2\",8080,2233,0");//����PC��UDP������ 
    usleep(1000000);

    Esp32AtCmd(esp32c3ble,"AT+CIPMODE=1");//���� UART Wi-Fi ����ģʽ
    usleep(1000000);

    Esp32AtCmd(esp32c3ble,"AT+CIPSEND");//����͸��

    printf("���� AT+CIPCLOSE  �ر�TCP����\n ");
    printf("���� AT+CIPMODE=0  �˳� UART Wi-Fi ͸��ģʽ\n ");//ͨ��WIFI���ӵ�����


    rtems_time_of_day tod={
        .year=2022,
        .month=6,
        .day=30,
        .hour=12,
        .minute=30,
        .second=30,
        .ticks =1
    };
    //rtc_set_time(&tod);
    memset(&tod,0,sizeof(tod));
    rtc_get_time(&tod);
    printf("%d-%d-%d %d:%d:%d\n",tod.year,tod.month,tod.day,tod.hour,tod.minute,tod.second);

    // while(1)
    // {
    //     sleep(1);
    //     rtc_get_time(&tod);
    //     printf("%d-%d-%d %d:%d:%d\n",tod.year,tod.month,tod.day,tod.hour,tod.minute,tod.second);
    // }


    while (1&&(!flag1))
    {
        printf("���������ַ��������䣺");

        sleep(1);
         rtc_get_time(&tod);
         printf("%d-%d-%d %d:%d:%d\n",tod.year,tod.month,
                 tod.day,tod.hour,tod.minute,tod.second);

        memset(buff1,0,sizeof(1024));
        Sht20GetData(buff1);
        printf("�¶�Ϊ:%f \tʪ��Ϊ:%f\n",buff1[0],buff1[1]);
         usleep(2000000);

         a=buff1[0];
     char s[20];
     gcvt(a, 6, s);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();

      d=buff1[1];
     char s1[20];
     gcvt(d, 6, s1);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();


        printf("humidty:");
        Esp32AtCmd(esp32c3ble,s);

        printf("temperature:");
        Esp32AtCmd(esp32c3ble,s1);
        memset(buff1,0,sizeof(1024));
    } 
}

void Led_Test2(void)//s3_pressdown
{
    int time = 100000; 
    Ledhandler led;
    Led_Init(452,&led);
    while(1&&flag2)
    {
        Led_Low(&led);
        usleep(time);
        Led_High(&led);
        usleep(time);
    }
}

void Led_Test3(void)//s3_pressup
{
    int time = 1000000;
    Ledhandler led;
    Led_Init(452, &led);
    int cnt = 5;
    while (cnt--)
    {
        Led_Low(&led);
        usleep(time);
        Led_High(&led);
        usleep(time);
    }
    //Yolov3_Test();
    Led_Low(&led);
}

static uint8_t ReadKeyS2Status(void)
{
    uint8_t res = 0;
    Keyhandler key;
    Key_Init(S2,&key);
    res =  Key_Status(&key);
    Key_close(&key);
    return res;
}
static uint8_t ReadKeyS3Status(void)
{
    uint8_t res = 0;
    Keyhandler key;
    Key_Init(S3, &key);
    res = Key_Status(&key);
    Key_close(&key);
    return res;
}

static void* S2_pressDown_callback_thread(void* args)
{
    printf("############### S2 Key  PRESS_DOWN ###############\n");
    flag1=1;
    Led_Test();
    return 0;
    
}
static void* S2_pressUp_callback_thread(void* args)
{
    printf("############### S2 Key  PRESS_UP ###############\n");
    flag1=0;
    Led_Test4();
    return 0;
    
}
static void* S3_pressDown_callback_thread(void* args)
{
    printf("############### S3 Key  PRESS_DOWN ###############\n");
    flag2 = 1;
    Led_Test2();
    return 0;

}
static void* S3_pressUp_callback_thread(void* args)
{
    printf("############### S3 Key  PRESS_UP ###############\n");
    flag2 = 0;
    Led_Test3();
    return 0;

}
static void CallBackS2_PressDown(void* args)
{
    pthread_t taskid;
    pthread_create(&taskid,0,S2_pressDown_callback_thread,NULL);
    //pthread_join(taskid,NULL);
}
static void CallBackS2_PressUP(void* args)
{
    pthread_t taskid;
    pthread_create(&taskid,0,S2_pressUp_callback_thread,NULL);
    //pthread_join(taskid,NULL);
}
static void CallBackS3_PressDown(void* args)
{
    pthread_t taskid;
    pthread_create(&taskid, 0, S3_pressDown_callback_thread, NULL);
    //pthread_join(taskid,NULL);
}
static void CallBackS3_PressUP(void* args)
{
    pthread_t taskid;
    pthread_create(&taskid, 0, S3_pressUp_callback_thread, NULL);
    //pthread_join(taskid,NULL);
}

void Key_Test()
{
    Button*  button = (Button*)malloc(sizeof(Button));
    memset(button,0,sizeof(Button));
    Button* button1 = (Button*)malloc(sizeof(Button));
    memset(button1, 0, sizeof(Button));

    TPin_level  pin_levels2 = ReadKeyS2Status;
    TPin_level  pin_levels3 = ReadKeyS3Status;

    button_init(button,pin_levels2,0,1);
    button_init(button1,pin_levels3,0,1);

    button_attach(button,PRESS_DOWN,CallBackS2_PressDown);
    button_attach(button,PRESS_UP,CallBackS2_PressUP);

    button_attach(button1, PRESS_DOWN, CallBackS3_PressDown);
    button_attach(button1, PRESS_UP, CallBackS3_PressUP);
    
    button_start(button1);
    button_start(button);
    while(1)
    {
        button_ticks();

        usleep(5000);//5ms
    }
    button_stop(button);
    button_stop(button1);

    free(button);
    free(button1);
}



void main_Test()
{
    Button*  button = (Button*)malloc(sizeof(Button));
    memset(button,0,sizeof(Button));
    Button* button1 = (Button*)malloc(sizeof(Button));
    memset(button1, 0, sizeof(Button));

    TPin_level  pin_levels2 = ReadKeyS2Status;
    TPin_level  pin_levels3 = ReadKeyS3Status;

    button_init(button,pin_levels2,0,1);
    button_init(button1,pin_levels3,0,1);

    button_attach(button,PRESS_DOWN,CallBackS2_PressDown);
    button_attach(button,PRESS_UP,CallBackS2_PressUP);

    button_attach(button1, PRESS_DOWN, CallBackS3_PressDown);
    button_attach(button1, PRESS_UP, CallBackS3_PressUP);
    
    button_start(button1);
    button_start(button);
    while(1)
    {
        button_ticks();

        usleep(5000);//5ms
    }
    button_stop(button);
    button_stop(button1);

    free(button);
    free(button1);
}
// void Key_Test()
// {
//     Button*  button = (Button*)malloc(sizeof(Button));
//     memset(button,0,sizeof(Button));
//     TPin_level  pin_levels2 = ReadKeyS2Status;

//     button_init(button,pin_levels2,0,1);
//     button_attach(button,LONG_PRESS_HOLD,CallBackS2_PressDown);
//     button_start(button);
//     while(1)
//     {
//         button_ticks();
//         usleep(5000);//5ms
//     }
//     button_stop(button);
//     free(button);
// }




/**
* ESP32 Ble���԰���
*0x304 Ϊ�ͻ���д����
*0x306 Ϊ�ͻ��˶�����
*/
static void *sppread(void* arg)
{
    Esp32c3* temp;
    char buff[1024];
    temp = (Esp32c3*)arg;
    while (1)
    {
        memset(buff,0,1024);
        uart_read(temp->device_fd,buff);
        if(strlen(buff) != 0)
            printf("\r\n>>%s\n",buff);
        usleep(1000000);
    }
    return 0;
}
static void *sppwrite(void* arg)
{
    Esp32c3* temp;
    char buff[1024]; 
    temp = (Esp32c3*)arg;
    while(1)
    {
        printf("<<");scanf("%s",buff);
        uart_send(temp->device_fd,buff);
        usleep(1000000);
    }
    return 0;
}
static void *idle_handle(void* arg)
{
    Esp32c3* temp;
    temp = (Esp32c3*)arg;
    while(1)
    {
        uart_send(temp->device_fd,"+++");
        usleep(1000000);
    }
    return 0;
}
/**
* ESP32 Ble���԰���
*/
void Esp32_Ble_Test()
{
    //int res = 0;
    char buff[1024];
    pthread_t read_tid;
    pthread_t write_tid;

    Esp32c3* esp32c3ble = (Esp32c3*)malloc(sizeof(Esp32c3));
    memset(esp32c3ble,0,sizeof(Esp32c3));

    Esp32Init(esp32c3ble,"/dev/ttyAMA1");
    Esp32AtCmd(esp32c3ble,"+++");
    usleep(1000000);
    Esp32AtCmd(esp32c3ble,"AT+RESTORE");
    Esp32AtCmd(esp32c3ble,"AT+CIPCLOSE");
    Esp32AtCmd(esp32c3ble,"AT+RESTORE");

    usleep(5000000);
    
    Esp32AtCmd(esp32c3ble,"AT");            /*< ��ѯAT ָ���Ƿ���������*/

    Esp32AtCmd(esp32c3ble,"ATE0");          /*< ��ѯAT �رջ���*/

    Esp32AtCmd(esp32c3ble,"AT+GMR");        /*< ��ѯAT �汾��Ϣ*/

    Esp32AtCmd(esp32c3ble,"AT+BlEINIT?");   /*< ��ѯ Bluetooth LE �Ƿ��ʼ��*/

    Esp32AtCmd(esp32c3ble,"AT+BLEINIT=2");   /*< ��ʼ��Bluetooth LE �����*/

    Esp32AtCmd(esp32c3ble,"AT+BLEGATTSSRVCRE");     /*< ESP32 Bluetooth LE ����˴�������*/

    Esp32AtCmd(esp32c3ble,"AT+BLEGATTSSRVSTART");   /*< ESP32 Bluetooth LE ����˿�������*/
    
    Esp32AtCmd(esp32c3ble,"AT+BLEADDR?");           /*< ESP32 Bluetooth LE ��������ȡ�� MAC ��ַ*/

    Esp32AtCmd(esp32c3ble,"AT+BLEADVDATA=\"0201060A09457370726573736966030302A0\"");    /*<���� Bluetooth LE �㲥����*/

    Esp32AtCmd(esp32c3ble,"AT+BLEADVSTART");        /*< ESP32 Bluetooth LE ����˿�ʼ�㲥*/

    printf("�ֻ��� nRF �������֣����� SCAN ��ʼɨ�裬�ҵ� ESP32 Bluetooth LE ����˵� MAC ��ַ����\
�� CONNECT ��������\n");                      /*< ESP32 Bluetooth LE ��������*/

    Esp32AtCmd(esp32c3ble,"AT+BLEGATTSSRV?");       /*< ESP32 Bluetooth LE ����˲�ѯ����*/

    Esp32AtCmd(esp32c3ble,"AT+BLEGATTSCHAR?");      /*< ESP32 Bluetooth LE ����˷�������*/

    printf("���ֻ� nRF �������ֿͻ��˵�� UUID:0xA002 �� UnKnown Service\n");   /*< ESP32 Bluetooth LE �ͻ��˷��ַ���*/

    printf("��ʱ���ֻ� nRF �������ֿͻ��˵� UUID:0xA002 �� UnKnown Service ������һ��ѡ����ѡ����\
PropertiesΪNOTIFY ���� INDICATE �ķ����������Ҳఴť������ ESP-AT Ĭ�� Properties Ϊ NOTIFY\
���� INDICATE �ķ��������� 0xC305 �� 0xC306),��ʼ����PropertiesΪNOTIFY ���� INDICATE ��\
��������\n");                                       /*< �ֻ� nRF �������ֿͻ��˷�������*/


    printf("����Ѿ�����,������yes\n");
    while (1)
    {
        scanf("%s",buff);
        printf("%s",buff);

        if(strstr(buff,"yes") == NULL)
            continue;
        else
            break;
        memset(buff,0,sizeof(1024));
        usleep(1000000);
    }

    usleep(5000000);

    Esp32AtCmd(esp32c3ble,"AT+BLESPPCFG=1,1,7,1,5");    /*< ESP32 Bluetooth LE ��������� Bluetooth LE SPP*/

    usleep(5000000);

    Esp32AtCmd(esp32c3ble,"AT+BLESPP");                 /*< ESP32 Bluetooth LE �����ʹ�� Bluetooth LE SPP*/
    
    pthread_create(&write_tid,NULL,sppwrite,esp32c3ble);
    pthread_create(&read_tid,NULL,sppread,esp32c3ble);
    pthread_join(read_tid,NULL);
}

/**
* ESP32 UDP���԰���
*/
void Esp32_UdpClient_Test()
{
    char buff[1024];
    Esp32c3* esp32c3ble = (Esp32c3*)malloc(sizeof(Esp32c3));
    memset(esp32c3ble,0,sizeof(Esp32c3));


    Esp32Init(esp32c3ble,"/dev/ttyAMA1");
    Esp32AtCmd(esp32c3ble,"+++");
    usleep(1000000);
    Esp32AtCmd(esp32c3ble,"AT+RESTORE");
    Esp32AtCmd(esp32c3ble,"AT+CIPCLOSE");
    Esp32AtCmd(esp32c3ble,"AT+RESTORE");
    usleep(5000000);

    Esp32AtCmd(esp32c3ble,"ATE0");//ȡ������
    Esp32AtCmd(esp32c3ble,"AT");//��ѯ�Ƿ���������
    Esp32AtCmd(esp32c3ble,"AT+GMR");//��ѯ�汾��Ϣ

    Esp32AtCmd(esp32c3ble,"AT+CWMODE=2"); //����esp32ΪSoftAP
    Esp32AtCmd(esp32c3ble,"AT+CWSAP=\"ESP32_SOFTAP\",\"1234567890\",5,3");//����ESP32�ȵ��˺ź�����
    usleep(10000000);//10s
    printf("Wait PC connect...\n");

    memset(buff,0,sizeof(1024));
    printf("ȷ��PC�Ƿ���UDP������");
    printf("����Ѿ�����,������yes\n");
    while (1)
    {
        scanf("%s",buff);
        printf("%s",buff);

        if(strstr(buff,"yes") == NULL)
            continue;
        else
            break;
        memset(buff,0,sizeof(1024));
        usleep(1000000);
    }
    Esp32AtCmd(esp32c3ble,"AT+CIPSTART=\"UDP\",\"192.168.4.2\",8080,2233,0");//����PC��UDP������ 
    usleep(1000000);

    Esp32AtCmd(esp32c3ble,"AT+CIPMODE=1");//���� UART Wi-Fi ����ģʽ
    usleep(1000000);

    Esp32AtCmd(esp32c3ble,"AT+CIPSEND");//����͸��

    printf("���� AT+CIPCLOSE  �ر�TCP����\n ");
    printf("���� AT+CIPMODE=0  �˳� UART Wi-Fi ͸��ģʽ\n ");
    while (1)
    {
        
        printf("���������ַ��������䣺");
        scanf("%s",buff);
        Esp32AtCmd(esp32c3ble,buff);
        memset(buff,0,sizeof(1024));
    }
}// ------------------------------------------------------------------------------------------����ʵ��

//�õ�ַΪ��֪����
char http_url[]="AT+HTTPCLIENT=2,0,\"https://api.seniverse.com/v3/weather/now.json?key=SZRaEMZNu4ieYZ3R3&location=hangzhou&language=zh-Hans&unit=c\",,,2\r\n";
void Esp32_HttpClient_Test()
{
    char buff1[1024];
    char buff2[1024];
    char* begin;
    char* end; 
    int i=0;
    char* path ;
    const char* json_ = buff2;
    cJSON *item,*localtion,*now,*time,*temp;
    Esp32c3* esp32c3ble = (Esp32c3*)malloc(sizeof(Esp32c3));
    memset(esp32c3ble,0,sizeof(Esp32c3));

    cJSON* message;

    Esp32Init(esp32c3ble,"/dev/ttyAMA1");
    Esp32AtCmd(esp32c3ble,"+++");
    usleep(1000000);
    Esp32AtCmd(esp32c3ble,"ATE0");//ȡ������
    Esp32AtCmd(esp32c3ble,"AT");//��ѯ�Ƿ���������
    Esp32AtCmd(esp32c3ble,"AT+GMR");//��ѯ�汾��Ϣ

    Esp32AtCmd(esp32c3ble,"AT+CWMODE=1");       /*����wifi ģʽΪstation*/
    Esp32AtCmd(esp32c3ble,"AT+CWJAP=\"abc\",\"17816376987\""); /*����·����  �����ֱ�Ϊ�ֻ��ȵ��˺ź�����*/ 
    usleep(5000000);
    
    
    Esp32AtCmd(esp32c3ble, http_url);       /*����http ����*/
    usleep(2000000);
    memset(buff1,0,1024);
    uart_read(esp32c3ble->device_fd,buff1);
    begin = strchr(buff1,'{');
    end = strrchr(buff1,'}');

    while(begin != end)
    { 
        buff2[i++]=*begin; 
        begin++;
    }


    buff2[i] = '}';
    buff2[i+1] = '\0';

    //printf("%s\n",buff2);

    message = cJSON_Parse(json_);

    // printf("%s\n",cJSON_Print(message));

    //���ص�Json���ݸ�ʽ

    // {
    //     "results":[
    //         {
    //             "location":{
    //                 "id":"WTMKQ069CCJ7",
    //                 "name":"����",
    //                 "country":"CN",
    //                 "path":"����,����,�㽭,�й�",
    //                 "timezone":"Asia/Shanghai",
    //                 "timezone_offset":"+08:00"
    //                 },
    //             "now":{
    //                 "text":"С��",
    //                 "code":"13",
    //                 "temperature":"18"
    //                 },
    //             "last_update":"2022-05-10T16:50:02+08:00"
    //         }
    //      ]
    // }
    
    item = cJSON_GetObjectItem(message,"results");
    item = cJSON_GetArrayItem(item,0);

    localtion = cJSON_GetObjectItem(item,"location");
    temp = cJSON_GetObjectItem(localtion,"name");
    path = cJSON_GetStringValue(temp);
    printf("�ص�:%s\n",path);


    time = cJSON_GetObjectItem(item,"last_update");
    path = cJSON_GetStringValue(time);
    printf("ʱ��:%s\n",path);


    now = cJSON_GetObjectItem(item,"now");
    temp = cJSON_GetObjectItem(now,"text");
    path = cJSON_GetStringValue(temp);
    printf("����:%s\n",path);
    temp = cJSON_GetObjectItem(now,"temperature");
    path = cJSON_GetStringValue(temp);
    printf("����:%s\n",path);


    cJSON_free(message);
}


void Adxl345_Test()
{
    float buff[3];
    adxl345_Init();

    adxl345_GetData(buff);
    printf("AngleX:%f AngleY:%f AngleZ:%f\n",buff[0],buff[1],buff[2]);
    a=buff[0];
    d=buff[1];
    e=buff[2];
}





void Oled_Test(void)
{
     int time = 100000;
    Sht20Init("/dev/i2c-1",0x40);
    float buff[2];
    while (1)
    { 
    Refresh();
    Sht20GetData(buff);
    printf("�¶�Ϊ:%f \tʪ��Ϊ:%f\n",buff[0],buff[1]);
    usleep(2000000);

//     float buff[3];
//     adxl345_Init();
//     adxl345_GetData(buff);
//     printf("AngleX:%f AngleY:%f AngleZ:%f\n",buff[0],buff[1],buff[2]);

//     a=buff[0];
//     d=buff[1];
//     e=buff[2];
//     char s[20];
//     gcvt(a, 6, s);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
//     char s1[20];
//    gcvt(d, 6, s1);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
//    char s2[20];
//    gcvt(e, 6, s2);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();

    oled_init();
    b=buff[1]/10;
    c=buff[1]-b*10;

    // char s[20];
    // gcvt(b, 6, s);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
    // char s1[20];
    // gcvt(c, 6, s1);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
    a=buff[0];
    char s[20];
    gcvt(a, 6, s);  // ת��Ϊ�ַ���������6λ��Ч����Sht20Close();
    ColorTurn(TURNOVER_COLOR);//��ɫ��ʾ
    DisplayTurn(NORMAL_DISPLAY);//������ʾ
    ShowString(0,0,s,size1206);//��ʾASCII�ַ� 
  //  ShowString(0,12,s1,size1608);//��ʾASCII�ַ�    
  //  ShowString(0,28,s2,size1608);//��ʾASCII�ַ�  
    Refresh();
   usleep(time);//Һ������ʾ

   pca9557_init("/dev/i2c-1");
   pca9557_setnum(b,c,0,0);
   pca9557_show(); //�������ʾ
    }
    
}//-----------------------------�������������ʪ��������ܺ�LED����ʾ



void Sht20_Test(void)
{


    Sht20Init("/dev/i2c-1",0x40);
    float buff[2];
    while (1)
    {
        Sht20GetData(buff);
        printf("�¶�Ϊ:%f \tʪ��Ϊ:%f\n",buff[0],buff[1]);
        usleep(2000000);
    }
     Sht20Close();
}




void Pca9557_Test(void)
{
    pca9557_init("/dev/i2c-1");
    pca9557_setnum(1,2,3,4);
    pca9557_show();
}

void Ds1399u_Test()
{
    rtems_time_of_day tod={
        .year=2022,
        .month=6,
        .day=30,
        .hour=12,
        .minute=30,
        .second=30,
        .ticks =1
    };
    //rtc_set_time(&tod);
    memset(&tod,0,sizeof(tod));
    rtc_get_time(&tod);
    printf("%d-%d-%d %d:%d:%d\n",tod.year,tod.month,tod.day,tod.hour,tod.minute,tod.second);

    while(1)
    {
        sleep(1);
        rtc_get_time(&tod);
        printf("%d-%d-%d %d:%d:%d\n",tod.year,tod.month,tod.day,tod.hour,tod.minute,tod.second);
    }
}