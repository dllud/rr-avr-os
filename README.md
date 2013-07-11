rr-avr-os
=========

Is a round-robin scheduling OS for Arduino and other AVR platforms. It is written in AVR C. rr-avr-os' goal is to provide an higher level hardware abstraction than [avr-libc](http://www.nongnu.org/avr-libc) while keeping a simple structure. 

rr-avr-os is targeted at experienced developers which want to write their homemade/academic/prototype projects in AVR C to take advantage of all functionalities provided by the AVR platform. rr-avr-os provides a skeleton which frees developers from the hassle of dealing with AVR control registers and lets them write clearer code.

Architecture
------------
rr-avr-os is composed by modules which should encapsulate a well defined functionality. Each module has at least two functions: init and task. The following excerpt from [main.c](/main.c) shows their usage.

	int main(void) {
		TIME_init();
		LED_init(1);
	
		while(1)
		{
			TIME_task();
			LED_task();
		}
	}


The init functions are called during program initialization and should be used to: make configurations, start timers, etc. The task functions are called in round-robin inside an infinite loop and provide the module's functionality, e.g., keep track of time or blink a LED. They should contain the repetitive actions which the module needs to execute.

There are two types of modules: system modules (sysmods) and user modules (usermods). sysmods are provided by rr-avr-os and encapsulate hardware functionality inside a simpler interface. They can also extend the available functionality such as the case of timed writes in [digitalrw](/digitalrw.h) and [pwm](/pwm.h). usermods are written by the project's developer and take care of the business logic, implementing the project's functionality.

sysmods
-------
* [adc](/adc.h) - Reads the Analog-to-Digital converter in Single Conversion Mode.
* [digitalrw](/digitalrw.h) - Reads and writes from digital ports.
* [led](/led.h) - Blinks the "alive" LED.
* [pwm](/pwm.h) - Writes PWM signals in Fast PWM mode.
* [time](/time.c) - Allows the tracking of periods of 200 us, 1 ms, 10 ms, 50 ms, 100 ms, 1 s, 1 min, etc.
* [uart](/uart.h) - Reads and writes chars from/to the UART (serial communication). Directs stdout and stdin to the UART.

Using rr-avr-os
---------------
In order to use rr-avr-os you just need to clone this repository and start writing your usermods. Do not forget to call them from [main.c](/blob/master/main.c). Be aware of your application time constraints and the limitations of round-robin: the code inside a module's task function should have a short execution time, otherwise it may starve other modules of processor time.

Compiling and running
---------------------
Configure the Makefile according to the AVR microcontroller your are using. Then, run `make` to compile and `make program` to upload to your device.

Authorship
----------
The base of what is now rr-avr-os was originally developed by [Renato Nunes](https://fenix.ist.utl.pt/homepage/ist12102). It was deployed on prototype hardware platforms with AVR microcontrollers. These were used for home automation as part of the [DomoBus](http://domobus.net/) project. The code was later given to students of the [Ambient Intelligence course at IST](https://fenix.ist.utl.pt/publico/degreeSite/viewCurricularCourse.faces?organizeBy=groups&hideCourses=false&action=null&degreeCurricularPlanID=432&showRules=false&executionYearID=2258&degreeID=147&curricularCourseID=17606&contentContextPath_PATH=/cursos/meic-a/plano-curricular&locale=en_EN) and improved by [me](https://github.com/dllud) for academic and homemade projects.

