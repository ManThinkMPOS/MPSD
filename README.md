
    Copyright (c) ManThink Technology Ltd. co.
    All rights reserved. This program and the accompanying materials
    are made available under the software of IAR for ARM version 8.20.2
    This is a demo working with the SDK of LWS made by ManThink Technology
    LWS is a SDK for OMX02 which realize LoRaWAN function.
    The Demo should be run on the hardware of OMX02 produced by ManThink Technology
    http://www.manthink.cn
    contact info : info@manthink.cn
    contributor  : mingfei zhao
    ###MPOS second development demo
    1.LoRaWAN Stack library： LWS417Alib.a
    The library realise most functions of LoRaWAN stack and provide some interfaces function for users.
    2.MyAPP.c
    The file is used to define some functions of user and setup periodic task and once event task.
    3.MyApp_INT.c
    The file is used to define all the interrupts of MPOS.
    4.MyApp_LWS.c
    The file is used to initial the LoRaWAN parameters and handling events of LoRaWAN stack.
    5.My Board.c
    The file is used to initial the OMX02 havdwares used by users.
    6.MyParse.c
    The file is used to define the analytic functions of users.
    7.MyTask.c
    The file is used to define periodic task and once event task.
    8.MyType.h
    The file is used to define the types of variables.
    9.MyGlobal.c
    The file is used to define the global variables.
    10.mymain.c
    The file is used to initial the LoRaWAN stack and some global configurations.
