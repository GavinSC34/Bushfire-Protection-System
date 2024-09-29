## Bushfire Protection System 👋

Climate change challenges homeowners to face the reality of increasingly frequent and
intense bushfires. To avoid major loss of life, the advice from the fire service, police and planners
is to evacuate. Take what you can, leave your house, and hope fire fighters can cope. And often,
they can't cope. 

The project aims to protect the house from bushfire when you are told to leave.
Spraying systems can be activated, by the homeowner, or automatically.
Loss of mains electricity and internet is common in major fires and is addressed.

Temperature and smoke sensors, as well as press button and Blynk, can start spraying.

The author lives in a rural area of Tasmania, Australia. He was a volunteer fire fighter for 15 years
and worked extensively on fire safety for the home through a community fireguard program.

In Australia and many other countries, rural residents rely on tank water. Many have limited water to fight fires and probably don't have ‘off the grid’ solar power available. Your situation might be different of course, you might even have the luxury of a piped, good pressure, water supply. 

![image](https://github.com/user-attachments/assets/0e590538-de56-4061-aa4a-ea10ec9b031e)

A deep cycle battery and 12 volt pump is used to spray water around the house. Since a small pump has limited capacity, a micro-controller sequentially controls a number of spray or sprinkler lines. A number of ‘triggers’ are built into the controller. The triggers utilise temperature and smoke sensors programmed to automatically start the pump at critical thresholds: 

• high temperature 

• sudden rise in temperature 

• heavy smoke 

• elevated temperature plus smoke 

As well, the system can be started by 

• a start switch (‘start and run’ switch) 

• a smart phone app switch linked to the system via the home WiFi and thus the internet. 

If the WiFi is unavailable the sensors will still work automatically. The phone app also shows the temperature and smoke, allowing monitoring from many kilometres away – provided the WiFi is working and the internet is available. Phone towers have been disabled in past major bushfires. While a 12v system is designed for the 240v power supply going down, you may want to consider an arrangement that can start on 240v and switch to 12v only if needed. This refinement is not included here (the simplest option may be adding a 240v battery charger).

Another useful addition would be an ESP32-CAM sending photos to Blynk.

Development of the concept is welcomed.

---------------------------------------------
<i>What will it cost? </i>

Each situation will be different. For those with off-grid power and a large dam, there is less infrastructure. Much of the work involves siting sprinklers, leading hoses to them, and fitting solenoid valves and wires. The micro-controller costs are surprisingly low but learning to code Arduino boards and the Blynk phone app is a steep learning curve for those not immersed in IT. The code is freely available as an example.

<i>Is it worth doing?</i>

While an automated spray/sprinkler system cannot guarantee your home will survive a bushfire, it should certainly improve your chances. With climate change and more forceful evacuation messages it should provide better peace of mind, if not save your situation. Do you have to evacuate? Legally, in most Australian jurisdictions, the answer is no. However it is usually the safest option if done early. Consider not only your safety, but the safety of fire fighters.

<i>How good is the science?</i>

The short answer is, it’s early days. Smoke sensors have been around for years and are utilised in building fire systems and smoke alarms. Temperature sensors are likewise proven items, as anyone with a home weather station can attest. Micro-controllers drive anything from washing machines to coffee makers. Phone apps are ubiquitous. What isn’t known is what level to set the ‘triggers’. How long to spray for? Will it be enough water in high wind? What can go wrong in your situation? The battery will pump continuously for maybe an hour, longer with intermittent pumping. Is that enough? Will the electronics be robust enough? All these can be considered however, and adapted to your situation. Plus, we need many installations and many tests before final guidelines can be provided. 

<b>Water</b>

Properties without a reliable water supply will need a water tank. A 4600 litre tank, minimum, is suggested for a small to medium sized house. More water is needed to protect sheds and outbuildings. The tank(s) are best dedicated to fire safety in the summer. 

<b>Hardware for water distribution</b>

SEAFLO 55 Series Water Pressure Pump (12V/5.5GPM/60PSI) (20.8LPM/413Kpa) $224, Amazon

Century Deep Cycle Battery N70T 102 Amp-hour 
https://www.supercheapauto.com.au/p/century-century-deep-cycle-battery-n70t-102ah/602320.html     $252

Solar panel and charger
https://www.supercheapauto.com.au/p/ridge-ryder-ridge-ryder-solar-panel-kit---110-watt/610689.html $149 

12V DC 1/2" Water Solenoid Valves - Normally Closed https://www.amazon.com.au/gp/product/B07SB3SGDY/ref=ppx_od_dt_b_asin_title_s00?ie=UTF8&psc=1 $8.47 each

IN4007 ‘flyback’ diodes. To protect the circuit from voltage spikes when the solenoids are activated. This forum article explains why and how to connect them up: 
https://forum.arduino.cc/t/flyback-diode-required-for-relay-board-and-12v-solenoid/422993/6
Available from Little Bird Electronics or Jaycar.

0.5mm Multi-Core Irrigation Cable
https://sunshoweronline.com.au/multi-core-irrigation-cable-0-5mm/?srsltid=AfmBOoq4aenDGwDpCoG9nAsx4MGBPU3200Nt_RN-uvlo1nnpS_S6_2yu&ref=124109
9 Core Irrigation Cable 0.5mm costs $2.85 per metre.  3 core costs $1 per metre. You will probably need a mix.

Sprinkler capable of covering approximately 450 to 500m². 
Holman 15mm Metal Impact Sprinkler Head, Bunnings
https://www.bunnings.com.au/holman-15mm-metal-impact-sprinkler-head_p3110996
$24.55 OR,
VYRSA 35 3/4" Brass Full-Circle Impact Sprinkler Dural Irrigation $52.58
https://duralirrigation.com.au/products/vyrsa-35-3-4-brass-full-circle-impact-sprinkler
This second sprinkler promises better performance with the above pump and an 18mm (¾”) supply hose, according to it’s specifications.

<b>Pipe and Hose</b>
How many of each? Maybe you need two systems, one for the house, the other for the sheds. That’s two pumps, two batteries and maybe onesolar panel and charger. The example house has four impact sprinklers and solenoids for them, plus three spray/mist lines and solenoids for each hose line. Connecting wire depends on distance from the pump and battery and how many ‘arms’ the system has. The sheds will have a similar arrangement.

It’s worth testing to see what hose works. Garden hose is 12mm, but 18mm is preferable for getting a volume of water over a long run. See https://www.bunnings.com.au/holman-18mm-x-30m-yardmate-garden-hose_p0047705. 30m costs $80. Maybe you have a short run and 12mm hose works. That’s fine, and cost is $20 to $30 for 30m. Map it out. Polypipe is often the best solution although joins aren't quite as easy as garden style hose. If you have 1 inch input and output on your pump, use 1 inch polypipe for delivery. Bury the hose line.

If you put the solenoids near the pump and not at the end of the hose line, and have one line for every sprinkler or sprayer you will save on wire, but may need more hose. The mist spray lines use 13mm black poly pipe with a spray every metre or so. If you have a lot of spray outlets on the line, it requires a lot of water.

<b>Micro-controller and related parts</b>

The suggested controller is a Lonely Binary ESP32-S3, $30. This model has an external antenna. It also comes supplied with enough solderable pins to mount the unit on a breadboard or PCB.
https://www.amazon.com.au/Development-Bluetooth-Espressif-ESP32-S3-DevKitC-1U-N16R8-Micropython/dp/B0CKYRGHBD?th=1

8 Channel relay to handle 12v, $21.95 at Jaycar.
https://www.jaycar.com.au/arduino-compatible-8-channel-relay-module/p/XC4418
Automotive Fused Relay SPST 30A, 12.95 Jaycar
https://www.jaycar.com.au/automotive-fused-relay-spst-30a/p/SY4077?pos=1&queryId=9bb946e0decf165f56a96eda1acf7d23
The 12v water pump has a high electrical load, particularly when starting up. This heavy duty relay connects the positive from the deep cycle battery to the positive of the pump. When the micro-controller ‘pump’ relay is activated it in turn switches this one. (Two relays piggy-backed). Heavy duty wiring can thus be fully employed between the battery and the pump.

Power supply regulator, 12v to 5v. Arduino Compatible DC Voltage Regulator Module CAT.NO: XC4514 Jaycar $10.25. Different regulators were tried and some failed, ruining parts. This one has proven to be stable. 
https://www.jaycar.com.au/arduino-compatible-dc-voltage-regulator-module/p/XC4514
Temperature sensor TMP36 - Analog Temperature sensor, Little Bird Electronics $5.80 https://littlebirdelectronics.com.au/products/tmp36-analog-temperature-sensor-tmp36?_pos=16&_sid=ebc1da120&_ss=r Note that different sensors, even in the same TMP36 package, can have the anode and cathode reversed. Check the data sheet carefully and don’t get them mixed up.
MQ-2 smoke sensor module, Little Bird Electronics $9.66.
https://littlebirdelectronics.com.au/products/mq-2-smoke-sensor-module?_pos=2&_psq=smoke&_ss=e&_v=1.0

Resistors, 1/4w: 220 ohm, 10K ohm.

LED. Little Bird has a selection.

Push button switch. Little Bird has a selection.

Jumper wire F/F to neatly connect the circuit to the sensors and relays. 
https://littlebirdelectronics.com.au/products/40-pin-15cm-jumper-wire-f-f?_pos=27&_sid=7b3ef1029&_ss=r gives flexible choice, $6.36.

Solderable breadboard, Core Electronics, $9.80.
https://core-electronics.com.au/solder-able-breadboard.html?gad_source=5&gclid=EAIaIQobChMIrMbalvKTiAMV8pKDBx2msAy4EAQYAiABEgKlpfD_BwE

Circuit diagram:
![image](https://github.com/user-attachments/assets/e892fe29-462a-4b33-82c1-cd006e720507)


<b>PCB</b>

KiCad was used to design a PCB and SeeedStudio to make a it. A unit that lives out in the weather, even if it is in a plastic box, will be prone to corrosion. Since there is a lot at stake, everything to be as reliable as you could make it.
If your needs just happen to be close to this design, there are a few spare PCB boards available. However most situations will be different – the number of lines, available power and so on.

<b>The External Circuitry</b>

The example follows the circuit suggested by LarryD in the flyback diode post mentioned above, https://forum.arduino.cc/t/flyback-diode-required-for-relay-board-and-12v-solenoid/422993
The major difference is the inclusion of an 8 channel relay. (Jaycar provides a datasheet for this, item XC4418.) Note that the centre terminal on each channel connects to the +ve, and the leftmost terminal will carry that positive to the solenoid once the relay is activated.

In the example build the ESP32, buck converter (or voltage regulator) and relays are all housed in one box, but the wiring is almost the same. <i>Important difference: an eight channel relay takes 12v, so the black and red wires to the relay will come from the battery end of the buck converter.</i> Jaycar one to four channel relays use 5v as shown here.

![image](https://github.com/user-attachments/assets/fa903b7d-eb2b-4657-95dd-168ee2593b55)


Attrib: LarryD.

For eight channels the wiring to each solenoid is repeated. The detailed illustration below shows the eight channel hookup, the horizontal red +ve wires are connecting each centre pin. The lower red wires, when switched, will take the +ve to the solenoids or the pump. The dark plugs at the bottom are waterproof connectors. Note this is not automotive style +ve and -ve wiring in the connectors.

![image](https://github.com/user-attachments/assets/7cb8f9e8-e74d-4acf-b04f-37956c41cec2)


<b>Bushfire behaviour</b>

Bushfire attack essentially takes five forms:

• <b>Wind:</b> Strong winds resulting from severe bushfires will drive embers into vulnerable areas of a building, preheat and dry fuel ahead of a fire, lift roofing and extend flames along a more horizontal plane closer to building elements.
    
• <b>Smoke:</b> While smoke will cause minimal damage to property, it can severely affect the health of residents. Smoke is a significant factor in at risk developments, particularly where residents are susceptible to respiratory disorders. Smoke can also reduce visibility during evacuation or shelter situations.
    
• <b>Embers:</b> Ember attack is responsible for most bushfire related building fires. Embers can also cause spotting in advance of the bushfire and ignite building elements.
    
• <b>Radiant heat:</b> Radiant heat can severely impair the health of residents and the integrity of building elements. Radiant heat can prevent emergency services personnel assisting occupants of at risk developments.
    
• <b>Flame:</b> Flame attack will severely restrict fire fighting operations, resulting in the ignition of building elements and a threat to the health of residents and their capacity to evacuate the area.
    
-– NSW Rural Fire Service, https://www.rfs.nsw.gov.au/plan-and-prepare/building-in-a-bush-fire-area/what-you-need-to-know/decision-tree-pages/goal-13

Your system
Planning your system requires you to carefully evaluate how to respond to each of those elements of bushfire behaviour.

<b>Wind:</b> you should be aware of your most likely wind direction for bush fire. Gale-force hot winds, which way do they come? What’s affecting the direction? Valleys, trees, vegetation? That side of your house may need more water. If you get the chance, set up a sprinkler next high fire danger day and see what it does. Think about wind carrying your water spray away from where it will be effective. How long will it take to dry that side of your house if you do spray it? How long does it take to wet it down?

<b>Smoke:</b> isn’t going to burn your house down, but is a warning and thus a trigger for your system. You can have intense smoke from kilometres away, think about how that might work. Really intense pungent smoke is usually an indication that a fire is on top of you. If you have limited water, that should be your trigger. You might use a beekeeper’s smoker to calibrate my system.

<b>Embers:</b> the peril of eucalyptus forests. Consider your house from top to bottom. The example situation has a Colourbond roof and vertical board walls. There is a fine mesh gutter guard in all the buildings’ gutters – for keeping leaves and embers out of the gutters and also to keep leaves out of the water tanks. To cool the boards and windows there ise a fine mist line high up the walls and running all the way around the house. This also serves to add to the accumulated water at the foot of the walls, because that is where smouldering or even burning leaves will gather. Further out, there are the heavy duty sprinklers spraying in an arc to saturate the closer trees, shrubs, lawns and walkways.

<b>Radiant heat:</b> what fuel is near the house? Remove flammable trees or have enough water and spray power to wet them down. Imagine your favourite gums on fire, up their bark and in their crowns. Don’t have an avenue of such trees around your house, particularly on the fire weather side, separated trees are better. Look at the trees for wind protection (needed) and trees as fuel (a problem). It’s a tricky balance that has to be addressed. Also look at adjacent sheds or buildings. Can they catch alight? Look to your windows, how might they be affected?

<b>Flame:</b> is what we are trying to avoid. Wet, cool surfaces don’t burn. However the extremes of bushfires make it hard to plan for a fire sequence. It might be ember attack, then fire front, then ember attack for hours following. It might be fire front first! Your system has to cope with the possibilities.

The example installation is set up to spray a sequence of a minute each, heavy sprinkler, then mist line, then next heavy sprinkler, then next mist line, working around the house. It was checked it out on a high fire danger day with strong hot winds and everything around the house looked flooded. A sequence lasts about seven minutes, then will start again if smoke and temperature trigger it, or if set going through the phone app. 
<TABLE BORDER=5><TBODY>  <TR>
    <TH>More on bushfires</TH>
<TD>Doing Community Fireguard work for Tasmanian Fire Service some years ago, a number of older residents talked about their experiences in the 1967 fires – still considered one of the worst ever – and later fires. Here are three observations: “The winds were 100 miles an hour, the temperature 100 degrees [ºF], and the dams were all empty!” (Ted Domeney. talking about 1967.) “I watched the embers flying across the Channel and saw the fires start up on Bruny Island. There were fireballs, burning balls of gas, blowing over the water.” (Colin Glanville, talking about 1967.) “The big gum outside the house had burnt and the heat had cracked the upstairs window. Sparks blew in and a chair was smouldering. Luckily we got back just in time.” (Ridgeway resident, talking about 1998). Ideally, your house, and windows, should be cool and wet enough to survive. Bushfires can be extreme, and quirky.</TD></TR> 
</TBODY></TABLE>
Now look again. Heat travels upwards. On the leeward side of this house there is a hill that falls away. Unfortunately it has many gums and wattles. After a fire front has passed that area may take a while to be set off by embers, but when it gets going it will be very hot, burning hard, uphill, right towards the house. Are you exposed?

<b>Arduino on the trigger</b>

The automated part of the system involves the micro-controller (an Arduino ESP32 model in my case), programmed to start the pumping sequence when:

• the temperature is over 45º C. Rationale: a 35 to 40º C day is not uncommon for fire weather, plus the sensor is in a box. The box is ventilated to allow air (and smoke) to move through it but an elevated temperature is expected. Then a fire will add to that.

• the smoke is more than 4000 ppm. Rationale: calibrated by passing smoke over the sensor. Also checked using the gas from a cigarette lighter held close to the sensor.

• the smoke is more than 2500 ppm AND the temperature is over 45º C. Rationale: a fire could be approaching in lower temperature and the wind is not blowing intense smoke over the unit yet. Smoke and heat together should be a useful trigger.

• the temperature increases 4º C in a sudden ramp. Rationale, an approaching fire might raise heat more or less steadily above the ambient hot day temperature, even on a 25º C day. Any weather hotter than 20º with winds more that 20 knots plus low humidity can be bad fire weather. (The 20/20 rule.) The system takes an average of a ten second period (call this a decade) and compares it against the decade just before, and just before that, looking back over the past nine decades.

These figures have not been tested in a bush fire! We need many units and some real world experience to add to the science. The example system will monitor the sensors through the coming summer so as to add to our knowledge and fine-tune the estimates. 

<b>Finger on the trigger</b>

It may be that your local radio, fire brigade or community fireguard alert you to an approaching fire. Fires start somewhere, you might be unlucky and it starts near you. Throw your valuables into the car, turn on the system and press the button. The spray should be working as you drive away to your evacuation centre. After one full spraying sequence it will stop. But the sensors are there waiting; as it’s triggered it will start another sequence.

<b>Blynk on the trigger</b>

Micro-controllers are readily connected to WiFi. Some units can be connected to the mobile phone network in 4G or 5G. This system is based on the house WiFi and the unit can send and receive information over the internet. Blynk (https://blynk.io/) provides a fairly easily built system to allow Arduino style programs to interact with a phone app or via a computer. The app includes a button to start the system at a distance, and a monitor to see if it has already started due to one of the other triggers.

If the power to the house is lost so is the WiFi – unless there is time to change the modem to battery, where it will continue to connect to the internet via 4G. (No fibre optic NBN here, but at least we have moved up from ADSL+.) Since the system is on a 12 v battery, the Arduino should keep communicating.

![image](https://github.com/user-attachments/assets/5af6a400-6e5f-418b-b32c-ca4ba8235c31)


The app, and the start button, are useful for testing the system –  especially to check if program changes work correctly.

<b><i>Part 2 – Software and Communication></i></b>

<i>Arduino to PCB – a steep learning curve</i>

A number of people have expressed interest in the system, but were daunted by having to learn electronics and programming. This section explains a little of what is involved - those already conversant with Arduino programming, OTA, circuit design and board making etc may skip this section. 

If you don’t like the idea of soldering and programming, you might find someone in your family or community who is willing to take this on. The plumbing of the hose lines is something most people can do.

The internet has great resources for training videos and discussion. The Arduino and Blynk websites have very useful introductions. Jaycar and other product supplier websites have not only Arduino compatible products, but also specification sheets explaining how to wire up the item and use it with a micro-controller. The Arduino IDE makes programming very straight-forward.

<b>Arduino</b>

As of February 2020, the Arduino community included about 30 million active users based on the IDE downloads. 
-– https://en.wikipedia.org/wiki/Arduino

Arduino micro-controllers have been available for nearly 20 years and their programming and utility is very well developed. They have a reputation for reliability. The ‘integrated development environment’ handles the programming aspect, with a programming language check, upload to the Arduino board facility and a comprehensive library of ready to run software called ‘sketches’ – and much more.

For those interested in the challenge of learning to build projects and program the Arduino, or compatible devices of other brands, there are excellent learning resources online, including beginners courses. Paul McWhorter’s Arduino Lessons (https://toptechboy.com/arduino-lessons/) are comprehensive and entertaining. Although I must admit I’m still a novice programmer.

I was given an Arduino Uno to ‘start playing with’; thanks Gene. I blew it up after a few weeks by powering it from an external source, then, wanting to upload a changed sketch, I plugged the board into my computer in the usual way. Lights out. Not good. That encouraged me to work through the tutorials more carefully.

I soon realised it would be easier if I could upload the sketches wirelessly. This led to OTA or Over the Air programming – a great improvement. OTA however means you can’t use the serial port in the IDE to track and debug your sketch, so you need an external window, like Telnet. Fortunately someone had already written the code, it was a matter of using the right Google search to find it.
Then on to Blynk and the phone app. Once again there were many examples to look at, and simple sketches to begin with. Blynk also led to the choice of the ESP32 S3 board with an external antenna. I had found, for this situation, the low powered boards need this extra hardware.

The code incorporates not only the triggers and pump start-stop relays, but also WiFi and OTA, Telnet and Blynk. And I had to make sure that the basic triggers would keep working if the WiFi was unavailable – quite possible in a real bush fire.

Pete Knight, a moderator on the Blynk forum, recommends ESP32 boards, and also, ‘keep your main loop clean’. The forum proved invaluable. The programming was more of a challenge than soldering up the parts.
               
<i>Breadboards to PCBs</i>

I started with a basic ‘push in the leads’ breadboard to test the idea. Wires everywhere! And hardly robust – after a week some of the connections were loose. On to a solderable breadboard with components on the front and fairly linear wiring on the reverse. Still rather messy and a dry joint was very hard to track down. The soldering was tricky too, I needed magnifiers to see what I was doing and a new soldering iron with a tiny point. I finally landed on a battery powered 6W soldering iron from Jaycar https://www.jaycar.com.au/battery-powered-6w-soldering-iron/p/TS1535?srsltid=AfmBOooegESU0W7gDC9mIWZrKJpWLnCHWekQW4WTpALk9IwkM9n9iz5e
Only 6 watts? It’s very adequate for PCBs and has the added benefit of longer protection of the tip. You only heat it up when you need it (10 seconds). No cord! I bought some heavy duty re-chargeable batteries and I’m still on the first charge.

KiCad was suggested for PCB design. Thanks Gene.

![image](https://github.com/user-attachments/assets/cd9410ce-6e97-4c18-b2b6-672acecaf223)
