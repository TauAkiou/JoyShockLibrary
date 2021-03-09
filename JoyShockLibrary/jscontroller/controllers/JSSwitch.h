//
// Created by robin on 3/8/21.
//

#ifndef JOYSHOCKLIBRARY_JSSWITCH_H
#define JOYSHOCKLIBRARY_JSSWITCH_H

// Joycon and Pro conroller stuff is mostly from
// https://github.com/mfosse/JoyCon-Driver
// https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering/
#define JOYCON_VENDOR 0x057e
#define JOYCON_L_BT 0x2006
#define JOYCON_R_BT 0x2007
#define PRO_CONTROLLER 0x2009
#define JOYCON_CHARGING_GRIP 0x200e
#define L_OR_R(lr) (lr == 1 ? 'L' : (lr == 2 ? 'R' : '?'))

class JSSwitch {

};


#endif //JOYSHOCKLIBRARY_JSSWITCH_H
