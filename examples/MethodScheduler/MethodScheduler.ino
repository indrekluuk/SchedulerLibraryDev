#include <Scheduler.h>



class TimedSerialOutput {
  
private:

  char* m_outputPrefix;
  int m_interval;
  // every object instance will have its own private scheduler
  MethodScheduler<TimedSerialOutput> m_scheduler;
  
public:
  
  TimedSerialOutput(char* prefix) : 
        m_outputPrefix(prefix), 
        m_interval(0), 
        // MethodScheduler must be initiated with the object whose methods are to be called
        m_scheduler(this) 
  {}
  
  // "MethodScheduler" calls object's method and therefore 
  // all object variables are accessible on callback
  void doOutput() {
    Serial.print(m_outputPrefix);
    Serial.print(m_interval);
    Serial.println(" millisecond tick");
  }
  
  void startOutput(unsigned long interval) {
    m_interval = interval;
    m_scheduler.set(&TimedSerialOutput::doOutput).runPeriodically(interval);
  }
};



TimedSerialOutput serial1("object 1: ");
TimedSerialOutput serial2("object 2: ");



void setup() {
  Serial.begin(9600);
  // objects operate separately with their own intervals
  serial1.startOutput(2000);
  serial2.startOutput(500);
}


void loop() {
  // run scheduler timing checks
  Scheduler::run();
}

