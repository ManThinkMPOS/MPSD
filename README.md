
    Copyright (c) ManThink Technology Ltd. co.\<br>
    All rights reserved. This program and the accompanying materials\<br>
    are made available under the software of IAR for ARM version 7.60.2\<br>
    This is a demo working with the SDK of LWS made by ManThink Technology\<br>
    LWS is a SDK for OM 801 which realize LoRaWAN function.\<br>
    The Demo should be run on the hardware of OM801 produced by ManThink Technology\<br>
    http://www.manthink.cn\<br>
    contact info : info@manthink.cn\<br>
    contributor  : mingfei zhao\<br>  
    MPOS second development demo\<br>
    1.LoRaWAN Stack library： LWS417Alib.a\<br>
    The library realise most functions of LoRaWAN stack and provide some interfaces function for users.\<br>
    2.MyAPP.c\<br>  
    The file is used to define some functions of user and setup periodic task and once event task.\<br>
    3.MyApp_INT.c\<br>  
    The file is used to define all the interrupts of MPOS.\<br>
    4.MyApp_LWS.c\<br>  
    The file is used to initial the LoRaWAN parameter and handling events of LoRaWAN stack.\<br>
    5.My Board.c\<br>
    The file is used to initial the OMX02 havdwares used by users.\<br>
    6.MyParse.c\<br>
    The file is used to define the analytic functions of users.\<br>
    7.MyTask.c\<br>  
    The file is used to define periodic task and once event task\<br>
    8.MyType.h\<br>  
    The file is used to define the types of variables.\<br>
    9.MyGlobal.c\<br> 
    The file is used to define the global variables.\<br>
    10.mymain.c\<br> 
    The file is used to initial the LoRaWAN stack and some global configurations.\<br>
