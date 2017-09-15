//

n = NetAddr("172.29.28.254", 57120);
n.sendMsg("/ip_request");

OSCdef(\color, {|array| array.postln; }, '/color');
OSCdef(\distance, {|array| array.postln; }, '/distance');
OSCdef(\sound, {|array| array.postln; }, '/sound');
OSCdef(\acceleration, {|array| array.postln; }, '/acceleration');

