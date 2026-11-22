# AI-Powered Drone for Aerial Image Detection

An integrated mechatronics and embedded-systems graduation project for aerial imaging, real-time flight control, wireless telemetry, environmental monitoring, and AI-assisted crop-health analysis.

I was responsible for the electronics, communication protocols, IoT subsystem, and the complete transmitter/receiver system. This included PCB design, component integration, firmware, wiring, bench testing, and hardware troubleshooting.

## Project demonstration

The complete 3-minute project demonstration is available in [`media/videos/AI-Powered_Drone_Full_Demonstration.mp4`](media/videos/AI-Powered_Drone_Full_Demonstration.mp4).

![Drone demonstration highlight](media/gifs/drone-demo-highlight-1.gif)

![Drone demonstration highlight](media/gifs/drone-demo-highlight-2.gif)

![Drone demonstration highlight](media/gifs/drone-demo-highlight-3.gif)

## System architecture

| Subsystem | Hardware and implementation |
| --- | --- |
| Flight platform | Quadcopter frame, BLDC motors, electronic speed controllers, APM 2.8 flight controller, servo/control interfaces, power distribution, and onboard electronics |
| Mechanical design | Custom quadcopter frame and mounting components designed in SolidWorks; structural stress analysis and assembly documentation are included |
| Transmitter | ESP32 with dual-axis joysticks, calibration logic, OLED status display, nRF24L01 wireless radio, and two flight-control switches |
| Receiver | Arduino Nano with nRF24L01 radio, PWM/servo outputs for APM 2.8, altitude-hold and stabilize-mode signals, and disarmed safe-output behavior |
| Wireless link | nRF24L01 at channel 76, 1 Mbps data rate, maximum RF power, and a shared `NODE1` RF pipe |
| IoT monitoring | ESP8266, DHT11 temperature/humidity sensor, Wi-Fi access, and Blynk cloud dashboards for Android, iOS, and PC |
| AI and image analysis | Computer vision for drone-based aerial image acquisition, crop-health inspection, and detection support |

## Transmitter

The custom transmitter is based on an ESP32 and reads four calibrated joystick axes:

- Throttle
- Yaw
- Pitch
- Roll

The firmware measures each joystick at the center position, calculates offsets, applies a dead-zone, inverts the throttle where required, and maps the four channels to PWM values from 1000 to 2000 microseconds. An OLED displays the live channel values and switch states.

**Hardware:**

- ESP32
- Dual 2-axis joystick modules
- SSD1306 OLED display
- nRF24L01 wireless transceiver
- Signal/altitude-hold switch
- Flight-mode switch

**Files:** [`firmware/transmitter/Transmitter.ino`](firmware/transmitter/Transmitter.ino)

![Custom transmitter PCB and hardware](hardware/pcb/Transmitter_PNG.png)

## Receiver

The receiver uses an Arduino Nano and an nRF24L01 radio. It listens on the same RF channel and address as the transmitter and converts the received control packet into five servo/PWM channels for the APM 2.8 flight controller:

- Roll
- Pitch
- Throttle
- Yaw
- Flight mode

When the signal switch is inactive, the receiver sends neutral 1000-microsecond outputs for a safe disarmed state.

**Hardware:**

- Arduino Nano
- nRF24L01 wireless transceiver
- Servo/PWM output stage
- APM 2.8 flight-controller inputs
- Receiver and step-down power PCB

**Files:** [`firmware/receiver/Receiver.ino`](firmware/receiver/Receiver.ino)

![Custom receiver PCB and hardware](hardware/pcb/Reciever_PNG.png)

## PCB and electronics

Proteus PCB designs and rendered PCB images are provided for the transmitter and receiver.

- [Transmitter PCB design](hardware/pcb/MG_Drone_Transmitter.pdsprj)
- [Receiver and step-down PCB design](hardware/pcb/MG_Drone_Reciever&StepDown.pdsprj)
- [Transmitter PCB render](hardware/pcb/Transmitter_PNG.png)
- [Receiver PCB render](hardware/pcb/Reciever_PNG.png)
- [Additional transmitter/receiver PCB image](hardware/pcb/Picture3.png)
- [PCB hardware screenshot](hardware/pcb/Screenshot%202025-06-26%20160215.png)

The PCB work integrates radio modules, microcontrollers, control switches, joystick/display wiring, PWM outputs, and power regulation. Low-voltage regulation is separated from the flight power path, and ground and supply connections must be checked against the final assembly before energizing the system.

## IoT monitoring

An ESP8266 reads DHT11 temperature and humidity data and publishes the measurements to Blynk virtual pins V0 and V1. The project includes Android, iOS, and PC dashboard views.

**Files:** [`firmware/iot/IOT_final.ino`](firmware/iot/IOT_final.ino)

Before compiling, replace the placeholder Wi-Fi and Blynk credentials in the source.

![Android IoT dashboard](media/photos/iot/Android.jpg)

![Android IoT dashboard](media/photos/iot/Android2.jpg)

![iOS IoT dashboard](media/photos/iot/IOS.jpg)

![PC IoT dashboard](media/photos/iot/PC.png)

## Mechanical and development work

![SolidWorks-style drone render](media/photos/drone/drone-render.png)

![Drone assembly](media/photos/drone/drone-build.jpg)

![Drone assembly detail](media/photos/drone/drone-build-detail.jpg)

![Stress analysis](hardware/design/Stress_Analysis.png)

[SolidWorks design assembly video](media/videos/SolidWorks_Drone_Design.mp4)

Development images are collected under [`media/photos/development/`](media/photos/development/).

## Launch Exhibition 3 — 3rd place

Our team placed **3rd among Egyptian universities** in mechatronics at the Launch Exhibition 3 competition and received a trophy.

![Me with my friend and the project award](media/photos/exhibition/friend-and-award.jpg)

![Team photo with the project award](media/photos/exhibition/team-and-award.jpg)

![Exhibition award presentation](media/photos/exhibition/exhibition-award-photo.jpg)

![Receiving the trophy](media/gifs/launch-exhibition-award.gif)

**Trophy reveal**

![Launch Exhibition trophy reveal](media/gifs/launch-exhibition-trophy-reveal.gif)

**Award ceremony**

![Launch Exhibition award moment](media/gifs/launch-exhibition-award-moment.gif)

**Team and exhibition moment**

![Launch Exhibition team moment](media/gifs/launch-exhibition-team-moment.gif)

[Award-moment video](media/videos/Launch_Exhibition_Award_Moment.mp4)

Additional exhibition photos are in [`media/photos/exhibition/`](media/photos/exhibition/).

## Mohamed Gamal — Project and Exhibition

![Mohamed Gamal presenting the drone project](media/photos/mohamed-gamal/mohamed-gamal-project-presentation.jpg)

![Mohamed Gamal with the project team](media/photos/mohamed-gamal/mohamed-gamal-team.jpg)

![Mohamed Gamal at the recognition event](media/photos/mohamed-gamal/mohamed-gamal-recognition.jpg)

![Mohamed Gamal working on the electronics](media/photos/mohamed-gamal/mohamed-gamal-soldering.jpg)

## Institutional recognition

![Egyptian Ministry of Higher Education and Scientific Research](media/photos/recognition/ministry-of-higher-education.png)

![New Cairo Technological University](media/photos/recognition/new-cairo-technological-university.png)

![Union of Technology Youth](media/photos/recognition/technology-youth-federation.png)

## Documentation

- [Project booklet PDF](documentation/Drone_Project_Booklet.pdf)
- [Project poster PDF](documentation/Project_Poster.pdf)
- [Main project presentation](documentation/AI-Powered%20Drone%20for%20Aerial%20Image%20Detection.pptx)
- [Business presentation](documentation/AI-Powered%20Drone%20for%20Aerial%20Image%20Detection_Business.pptx)
- [Phase 1 presentation](documentation/Ai_Powerd_Drone_For_Image_Ditection_Phase_1.pptx)
