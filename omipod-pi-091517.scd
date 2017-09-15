/* OMIPODPI Testing

changelog:

____091517

Added code to look at the first msg index for the OSC symbol, the rest gets preserved and sent as the msg.


____090617

Adding list to collect IPs of computers that ping us.



____ OLD STUFF

added arduino quark


*/

// Our (OMIPODPI) IP Address:

i = Pipe.new("ip route show | awk '/src/ {print $9}'", "r").getLine;

// create a list to keep netaddrs in

~netAddrs = List[];

// this will listen for /ip_request messages and assign the message IP to ~destination for use in the below$

(
OSCdef(\ip_register, {|msg, time, addr|

	// check list to see if IP exists.  if it doesn't, add it.

	if (~netAddrs.includesEqual(addr).not, {~netAddrs.add(addr) } ) ;

}, '/ip_request');
)

// run ls /dev/tty* without arduino, then again with it to find mount point -- can we automate this?

// create the arduino object
p = ArduinoSMS("/dev/ttyUSB0", 115200);

// test it
//p.action = {|... msg| msg.postln};

// throw it at your other computer!
(
p.action = {|... msg|
	var id, array;
	id = msg[0];  // this is our oscmessage identifier
	array = msg;
	array.removeAt(0); // this is the rest of the array
	array.postln;

	// for however many netAddrs are present, sent the sensor data
	~netAddrs.do { |i|  i.sendMsg(id, *array); };
	//id.postln;
	//array.postln;
};
)


p.action = nil



x = [0,1,6];
x.removeAt(1);
x


/*

SSH into your Pi from a Mac using an ethernet cable (must already have SSH enabled...)

"https://medium.com/@tzhenghao/how-to-ssh-into-your-raspberry-pi-with-a-mac-and-ethernet-cable-636a197d055"

*/


// OLD TESTING BELOW

~netAddrs = List[];


OSCdef(\testing, {|msg, time, addr, port| msg.postln; time.postln; addr.postln; port.postln;

	if ( ~netAddrs.includesEqual(addr).not, { ~netAddrs.add(addr)} ) ;

}, '/testRequest');


n = NetAddr("127.0.0.1", 57120); // local machine

n.sendMsg("/ip_request");
~netAddrs




if  ( ~netAddrs.includes(70).not,  { ~netAddrs.add(rrand(0, 100)) })




