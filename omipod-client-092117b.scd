/*

SuperCollider code for working with the OMIPOD prototype

Part of the Open Music Initiative OMIPOD Workshop presented in partnership with Digital Humanities Lab
and the Center for Collaborative Arts and Media.

4pm, September 21, 2017


OMIPOD Prototype "Boxy" IP = 172.29.29.133
"Firsty" IP = 172.29.28.254

*/


// You need the IP address of the POD -- fill in below in the string ("") and evaluate
n = NetAddr("172.29.29.133", 57120);
// This will send your IP address to the POD and register you to receive messages
n.sendMsg("/ip_request");

/*

Below are pre-formatted OSCdefs that will look for the messages being sent by the OMIPOD.  To sonify the incoming data, simply use the data contained in the 'array' argument.  The number and type of data is described above each OSCdef.

*/

// COLOR: The color sensor array contains three floats for red, green, and blue
OSCdef(\color, {|array| array.postln

	// Write sound sonification code for the color sensor here


}, '/color');

// DISTANCE: The distance sensor array contains one integer representing distance in centimeters
OSCdef(\distance, {|array| array.postln;

	// Write sound sonification code for the color sensor here



}, '/distance');


// SOUND: The sound sensor array contains one float representing the ambient loudness of the room
OSCdef(\sound, {|array| array.postln;

	// Write sound sonification code for the sound sensor here


}, '/sound');


// ACCELEROMETER: The accelerometer sensor array contains floats for three axes and a string representing the orientation of the sensor
OSCdef(\acceleration, {|array| array.postln;

	// Write sound sonification code for the accelerometer sensor here

	// array.postln;

}, '/acceleration');


// LIGHT: The light sensor array contains one integer representing the ambient light amount in the room
OSCdef(\light, {|array| array.postln;

	// Write sound sonification code for the accelerometer sensor here


}, '/light');



/*____________________________________________________

 Calibration: registers low and high values for
 all the sensors:

Light: To work effectively, point the front of the POD at a bright
light, then cover up the light sensor.

Sound: make a loud sound into the mic

Distance: Put the front of the POD against a wall, then
slowly back up until you are more than 15 feet away.

Color:  ???

Accelerometer: make a looping, figure-eight motion
with the OMIPOD.

____________________________________________________*/


(
d = ( );
	// sound
	d.sLo = 99999;
	d.sHi = 0;
	// light
	d.lLo = 99999;
	d.lHi = 0;
	// distance
	d.dLo = 99999;
	d.dHi = 0;
	// accelerometer
	d.xLo = 99999;
	d.xHi = 0;
	d.yLo = 99999;
	d.yHi = 0;
	d.zLo = 99999;
	d.zHi = 0;
	// color
	d.rLo = 99999;
	d.rHi = 0;
	d.gLo = 99999;
	d.gHi = 0;
	d.bLo = 99999;
	d.bHi = 0;


OSCdef(\sound, {|array| array.removeAt(0);


	case{ array[0] < d.sLo}{d.sLo = array[0]} { array[0] > d.sHi}{d.sHi = array[0]};

}, '/sound');

OSCdef(\distance, {|array| array.removeAt(0);

	array[0].postln;
	case{ array[0] < d.dLo}{d.dLo = array[0]} { array[0] > d.dHi}{d.dHi = array[0]};

}, '/distance');

OSCdef(\light, {|array| array.removeAt(0);

	case{ array[0] < d.lLo}{d.lLo = array[0]} { array[0] > d.lHi}{d.lHi = array[0]};

}, '/light');

OSCdef(\color, {|array| array.removeAt(0);

	case{ array[0] < d.rLo}{d.rLo = array[0]} { array[0] > d.rHi}{d.rHi = array[0]}
		{ array[0] < d.gLo}{d.gLo = array[1]} { array[1] > d.gHi}{d.gHi = array[1]}
		{ array[0] < d.bLo}{d.bLo = array[2]} { array[2] > d.bHi}{d.bHi = array[2]};

}, '/color');

OSCdef(\accelerometer, {|array| array.removeAt(0);

	case{ array[0] < d.xLo}{d.xLo = array[0]} { array[0] > d.xHi}{d.xHi = array[0]}
		{ array[1] < d.yLo}{d.yLo = array[1]} { array[1] > d.yHi}{d.yHi = array[1]}
		{ array[2] < d.zLo}{d.zLo = array[2]} { array[2] > d.zHi}{d.zHi = array[2]};

}, '/acceleration');


)

// test a few...

d.yHi





/* After callibration, press cmd or ctl + return to remove the responders.
All of the global variables will retain their values until redefined.
*/

// Evaluate this line to preserve your callibration settings
// write the dictionary to a file (mac).  Remove the Desktop part to write to any user's home directory.
 d.writeArchive( "~/Desktop/pod-calibration.txt".standardizePath);

// read the event from the file (mac)
e = Object.readArchive( "~/Desktop/pod-calibration.txt".standardizePath);




/*____________________________________________________*/

/* Simple Sonification Examples */

/*____________________________________________________*/


// Define control buses to which to write any incoming data:
(
~lightBus = Bus.control(s, 1);
~distBus = Bus.control(s, 1);
~soundBus = Bus.control(s, 1);
~colorBus = Bus.control(s, 3);
~accelBus =  Bus.control(s, 3);
)

// Simple Buffer Examples: use incoming sensor data to control the playback of a sound loop

// Load a buffer
b = Buffer.read(s, "/Users/scacinto/Google Drive/External Sync/TEACHING/OMIPOD/amenbreakNorm.wav");


// EXAMPLE 1: USING DISTANCE TO CONTROL PLAY POSITION / LIGHT CONTROLS TRIGGER

// SPOOFING CODE:

~lightBus.value = 12;
~distBus.value = b.numFrames / 20;


// Step 1: Register the light function
(
OSCdef(\light, {|array|
	var mapping;
	array[1].postln;
	mapping = array[1].asInteger.abs.linlin(d.lLo.abs, d.lHi.abs, 0.5, 200).lag(0.1);
	~lightBus.value = mapping;

}, '/light');

// Step 2: Register the distance function


OSCdef(\distance, {|array|
	var mapping;
	array[1].postln;
	mapping = array[1].asInteger.abs.linlin(d.dLo.abs, d.dHi.abs, 0, b.numFrames);
	~distBus.value = mapping;

}, '/distance');


OSCdef(\distance, {|array|
	var mapping;
	array[1].postln;
	mapping = array[1].asInteger.abs.linlin(d.dLo.abs, d.dHi.abs, 0, b.numFrames);
	~distBus.value = mapping;

}, '/distance');
)


// Step 3: Instantiate the synth.  Synth uses ~light and ~distance values being set in real-time by the OSCdefs.

SynthDef(\help_PlayBuf, { arg out=0, bufnum=0;
    var trig;
	trig = Impulse.kr(~lightBus.kr());
    Out.ar(out,
		PlayBuf.ar(2, bufnum, BufRateScale.kr(bufnum), trig, ~distBus.kr(), 1)
    )
}).play(s, [\out, 0, \bufnum, b]);


