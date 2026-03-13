A simple LAN\WEB Albrecht AE-5900 remote control
=================================================

## Main purpose of the project:

Build a simple LAN\WEB remote control for the amazing Albrecht AE-5900 and similiar Radios

The simple idea is, to emulate the 3 button (4 include PTT) Mic and publish the control of these buttons to a flask / python over network / web.
In my case i set the middle button of my AE5900 to Mode (modulation).
So i can CH Up / CH Down / Mode and PTT my device from everywere.
For audio i just use a usb Soundcard, some components and mumble on my raspberry and my phone.

## A picture will say more than your wife

- From first testing to put all the stuff in to a small case

	![AE-5900_Remote_v1](ae5900remote_trash2final.jpeg)

## About & Why

The Albrecht AE-5900 is the fantastic new (2026) FM/AM/SSB/CW Radio i did not expect. It has a huge potential to have fun with it and brings me back to CB after 35 years of silence. 

So, i build something additional for it and someone (yeah, thanks again bro) told me to publish it on github and i said hmmmkay.
The device i build is based on an Pro Micro atmega32u4, a cheap usb soundcard, a usb hub breakout board, coils, resistors, capacitors, optocouplers and some stuff i had around in my scrapbox. It is working well and i've fun with it.
Let's see what will happen in next days.

But Why:

It is the hobby you will not have enough time for.
Especially if you are a old guy with kids, one or more jobs and all that surprises life will have for you. So now it is possible to use your home station, with your perfect antenna from your workingpaces toilet or whatever.

Thats just why.


## How it works:

Plug the remote device in to a raspi or somehing else that will run the python script. And also your ae5900 mic plug and speaker output should be connected.
Start mumble on your host / You migt have to crossover Input and Output.
run the python3 app.py
browse your localhost:5000
Pull down the setup part
Set your ae5900 to use the middlebutton of mic TYPE1 to MODE
Set your ae5900 manually to CH1 and Mode PA
Press the sync button in websetup menu for 3 sec
Now change, on web page, first the modulation as desired and then switch the chanels.
Start mumble on your remote device and have fun.
Had good Audio-feedbacks on some QSO's

Thats all.

## Building

The hardware in detail.
i'm not so much familiar with KiCad, normally i do not plan my projects and write them down. I just do and it works somehow. I this case, just for you, because some people asking, i tried to show a shematic here:

- Shematic overview in detail

	![AE-5900_Remote_v1](shematics/3partstogether.png)

The Atmega32U4 i used is a Pro Micro, often from SpakFun or similiar brands.
In my case i used pin 2 - 5. You can see at the bottom of the picture TX0 RX1 GND GND  (2 3 4 5 6 7.....) <- thats wehre we connect the resistors and optocouplers.
On following Picture i marked the points wehre you can solder an USB port if you're not a fan of lot of plugs in your projects

- Pro Micro with 32U4 chip

	![AE-5900_Remote_v1](projectpictures/USB_Soldering_32U4ProMicro.jpg)

### Software needed

- just for bulding

Arduino IDE neded to flash/upload the Sketch (.ino file) to Pro Micro 32U4

- to make the device useable

Mumble & Mumble Server for your voice i/o on the computer/raspberry that will host your remote control

	# sudo apt install mumble mumble-server
	
Mumble on your remotecomputer or Mumla on your Android phone.

Tailscale on host and remote, for use your device from all over the world. :)

In best case you have pipewire or pulseaudio preinstalled on your host system.
Otherwise just install all of that stuff.

	# details and configs will follow soon. most of you already know how.


## What you can expect more:

Nothing more than my experience.
I will not support you personaly.
But i will upload some scripts, pictures and ideas to share with people.

I'm not a coder, but i can read what someone has written, i can understand and implement in my projects.

## Whats happen here last days:

10/Mar/2026:
1. Opened github repo
2. Added a picture of the stuff i build.
3. I put some infos in the readme

11/Mar/2026:

1. Uploaded lot of informations, pictures,"shematics", the scripts (cleaned by googles ki)
It looks like chaos and yes, it is. Give me some time.

12/Mar/2026:

1. Chill
2. Make and edit some pictures for dokumentation - future uploads will follow
3. Testing the device heavier to find problems
4. Editing this readme and get a structure
5. Lot of Test-QSO's - amazig feedbacks came in

13/Mar/2026

1. Had a coffe
2. Might i solved the slow key reaction - testing is ongoing
3. Editing this readme


