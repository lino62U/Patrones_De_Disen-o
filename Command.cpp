#include <iostream>
 
using namespace std;

// Command Interface
class Command
{
public:
	virtual void execute() = 0;
};
 
// Receiver Class
class Light 
{
public:
	void on() {
		cout << "La luz esta encendida\n";
	}
	void off() {
		cout << "La luz esta apagada\n";
	}
}; 

// Command para encender la luz
class LightOnCommand : public Command 
{
private:
	Light *mLight;
public:
        LightOffCommand()
	{nmLight = new Light();}
	void execute(){
		mLight->on();
	}

};
 
// Command para apagar la luz
class LightOffCommand : public Command 
{
private:
	Light *mLight;
public:
        LightOffCommand()
	{nmLight = new Light();}
	void execute(){
		mLight->off();
	}

};

// Invoker 
// Almacena el objeto comando
class RemoteControl 
{
private:
	Command *mCmd;
public:
	void setCommand(Command *cmd) {
		mCmd = cmd;
	}

	void buttonPressed() {
		mCmd->execute();
	} 

};
 
// The client
int main() 
{
	// concrete Command objects 
	LightOnCommand *lightOn = new LightOnCommand();
	LightOffCommand *lightOff = new LightOffCommand();

	// invoker objects
	RemoteControl *control = new RemoteControl;

	// execute
	control->setCommand(lightOn);
	control->buttonPressed();
	control->setCommand(lightOff);
	control->buttonPressed();

	delete light, lightOn, lightOff, control;

	return 0;
}
