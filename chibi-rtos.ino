#include <ChibiOS_AVR.h>

MUTEX_DECL(demoMutex); //declare mutex

static THD_WORKING_AREA(waTh2, 100); //data structure & stack for thread 2
static THD_WORKING_AREA(waTh3, 100); //data structure & stack for thread 3


//Mutex Serial Function---------------------------------------------------------
void notify(const char* name, int state) {
  chMtxLock(&demoMutex); //enter protected region
  Serial.print(name);
  Serial.write(": ");
  Serial.println(state);
  chMtxUnlock(&demoMutex); //exit protected region
}
//Declare Thread Functions -----------------------------------------------------


static THD_FUNCTION(thread1, args) {
     while (true) {
        notify((const char*)args, 2);
        chThdSleep(1000);
    }
}


static THD_FUNCTION(thread2, args) {
     while (true) {
        notify((const char*)args, 2);
        chThdSleep(2000);
    }
}

static THD_FUNCTION(thread3, args) {
     while (true) {
        notify((const char*)args, 1);
        chThdSleep(4000);
    }
}


//------------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    delay(100); //wait for serial
    chBegin(chSetup); //start ChibiOS
    while(1); //never return
}


//Schedule Threads------------------------------------------------------
void chSetup() {
  chThdCreateStatic(waTh2, sizeof(waTh2), NORMALPRIO, thread2, (void*)"Thread 2"); //schedule thread 2
  chThdCreateStatic(waTh3, sizeof(waTh3), NORMALPRIO, thread3, (void*)"Thread 3"); //schedule thread 3
  thread1((void*)"Thread 1"); //thread 1 - main thread
}


//------------------------------------------------------------------------------
void loop() {/* not used */}