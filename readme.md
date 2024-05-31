# NBIOT Air Monitor


```c++
/*
Version:		V1.0
Author:			Vincent
Create Date:	2024/5/30
Note:

*/
```


![](md_pic/main.jpg)


[toc]

# Makerfabs

[Makerfabs home page](https://www.makerfabs.com/)

[Makerfabs Wiki](https://wiki.makerfabs.com/)

# NBIOT Air Monitor
## Intruduce

Product Link ：

Wiki Link :  

The NBIOT Air Monitor is suitable for IoT applications that need low latency, Low throughput data communication in a variety of radio propagation conditions, such as smart-home, metering, asset tracking, remote monitoring, E-health etc.

## Feature


### Front:

![front](md_pic/front.jpg)

### Back:
![back](md_pic/back.jpg)


# Arduino Complier Option

**If you have any questions，such as how to install the development board, how to download the code, how to install the library. Please refer to :[Makerfabs_FAQ](https://github.com/Makerfabs/Makerfabs_FAQ)**

- Install board : ESP32 Version 2.0.11
- Select "ESP32-S3"
- Select Erase All Flash
- Upload codes

Arduino libraries:

- RadioLib 4.6.0
- Adafruit_Unified_Sensor 1.1.9
- Adafruit_AHT10 0.1.0
- Adafruit_BusIO 1.14.1
- Adafruit_SGP30_Sensor 2.0.0
- BH1750 1.3.0

# Example

## iot_fw_test

Factory test program for testing sensor reading, and AT module initialization.


## at-test

Serial transparent transmission test demo.

## mail_test

A demo for sending an email