#!/usr/bin/env python
"""
Cette node traite le comportement d'evitement en mode manuel

2015-8-03: Retrait du ralentissement automatique et fusion avec keyboard_node
"""

# importation des modules
import rospy
from std_msgs.msg import Bool, Char
from geometry_msgs.msg import Twist
class arion_behavior():
    def __init__(self):
        #Initialisation des variables
        self.update_rate = 10.0    # Frequence de rafraichissement [Hz]
        self.man_ctrl = True    # Controle manuel ou auto donne par l'utilisateur
        self.man_speed = 0.0    # Vitesse manuel donnee par l'utilisateur
        self.man_steering = 0.0 # Steering manuel donne par l'utilisateur

        self.SPACE_KEY=32
        self.W_KEY=119
        self.S_KEY=115
        self.A_KEY=97
        self.D_KEY=100
	self.buff=0
	self.buff2=0
	self.buff3=0


        self.manual_movement_command_topic = rospy.get_param("~manual_movement_command",'/man_cmd_vel')
        self.keyboard_topic = rospy.get_param("~keyboard_sub",'keyboard') # 2015-08-03

        self.keyboard_increment = rospy.get_param("~keyboard_increment", 0.1) # Increment de vitesse pour le controle au clavier 2015-08-03
        self.keyboard_decay = rospy.get_param("~keyboard_decrement", 0.1) # Decrement de vitesse pour le controle au clavier 2015-08-03

        self.manual_movement_command_pub = rospy.Publisher(self.manual_movement_command_topic, Twist, queue_size=1)
        rospy.Subscriber(self.keyboard_topic, Char, self.keyboard_callback) 

        self.r = rospy.Rate(self.update_rate)

        self.updater()

    def keyboard_callback(self, data): 
        increase = self.keyboard_increment

        if data.data == self.SPACE_KEY:
            self.man_ctrl = not self.man_ctrl
            rospy.loginfo("Manual control set to: "+str(self.man_ctrl))
            if self.man_ctrl == False:
                self.man_speed = 0.0
                self.man_steering = 0.0
        elif self.man_ctrl == True:
            if data.data == self.W_KEY and self.buff == self.W_KEY and self.buff2 == self.W_KEY and self.buff3 == self.W_KEY:
                self.man_speed = min([(self.man_speed+increase),0.5])
		
            elif data.data == self.S_KEY and self.buff == self.S_KEY and self.buff2 == self.S_KEY and self.buff3 == self.S_KEY:
                self.man_speed = max([(self.man_speed-increase),-0.5])
                
	    elif data.data == self.D_KEY and self.buff == self.D_KEY and self.buff2 == self.D_KEY and self.buff3 == self.D_KEY:
                self.man_steering =max([(self.man_steering-increase),-0.5])
                
	    elif data.data == self.A_KEY and self.buff == self.A_KEY and self.buff2 == self.A_KEY and self.buff3 == self.A_KEY:
                self.man_steering =min([(self.man_steering+increase),0.5])

	self.buff3 = self.buff2
	self.buff2 = self.buff
	self.buff = data.data
	

    def updater(self):
        while not rospy.is_shutdown(): 

            motor_msg = Twist()
            motor_msg.linear.x = self.man_speed
            motor_msg.angular.z = self.man_steering
            
            if self.man_ctrl == True:

                self.manual_movement_command_pub.publish(motor_msg)
                
                if abs(self.man_speed) >= self.keyboard_decay:
                    self.man_speed = self.man_speed - self.keyboard_decay * (abs(self.man_speed)/self.man_speed)
                else:
                    self.man_speed = 0.0

                if abs(self.man_steering) >= self.keyboard_decay:
                    self.man_steering = self.man_steering - self.keyboard_decay * (abs(self.man_steering)/self.man_steering)
                else:
                    self.man_steering = 0.0

            self.r.sleep()

# Initialisation de la node dans ROS, cree une instance de la Class de la node
# Main function.
if __name__ == '__main__':
	# Initialize the node and name it.
	rospy.init_node('arion_behavior_node')
	try:
		arion_behavior()
	except rospy.ROSInterruptException:
		pass

