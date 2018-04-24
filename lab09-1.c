#pragma config(Motor,  motorA,          J1,            tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          J2,            tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#define LENGTH 41
#define LENGTH 1
#define TF 1
#define J1_INIT 0
#define J2_INIT 180

#define J1_SCALE 0.94 //done tuning
#define J2_SCALE 3.75 	//needs to be tuned 

int path[LENGTH][2] = {
{0,90}};



void goToTheta(int t1, int t2){ //puts joints at desired theta one and theta two
	
	int tick = 0; //encoder ticks, used for joint 2 offset
	
	while(nMotorEncoder(J1)!= round(J1_SCALE*(t1-J1_INIT)) || nMotorEncoder(J2)!= round(J2_SCALE*(t2-J2_INIT)) + round(J1_SCALE*(t1-J1_INIT)/TF)){ //while both joints are not at the desired location
		//nxtDisplayString(4,"%d",tick);
		
		nxtDisplayClearTextLine(5);
		nxtDisplayClearTextLine(6);
		nxtDisplayString(5,"%d",nMotorEncoder(J1));
		nxtDisplayString(6,"%d",nMotorEncoder(J2));
		
		tick = tick + 1; //increment encoder tick
		
		if(nMotorEncoder(J1) < round(J1_SCALE*(t1-J1_INIT))){ //if motor encodes is less than desired 
				motor[J1] = 10; //go forewards
				//if(tick % 4 == 0){ //add offset to second joint to offset backlash
					//t2 = t2 + 1;
				//}
		}			
		else if(nMotorEncoder(J1) > round(J1_SCALE*(t1-J1_INIT))){ //if greater
				motor[J1] = -10; //go backwards
				//if(tick % 4 == 0){ //add offset to second joint to offset backlash
					//t2 = t2 - 1;	
				//}	
		}		
		else{				//if equal
				motor[J1] = 0; //stop
		}
		//nxtDisplayString(7,"%d",t2);
		if(nMotorEncoder(J2) < round(J2_SCALE*(t2-J2_INIT)) + round(J1_SCALE*(t1-J1_INIT)/TF)){ //same thing but for the other motor
				motor[J2] = 10;
				nxtDisplayString(7,"1");
		}
		else if(nMotorEncoder(J2) > round(J2_SCALE*(t2-J2_INIT)) + round(J1_SCALE*(t1-J1_INIT)/TF)){
				motor[J2] = -10;
				nxtDisplayString(7,"2");
		}
		else{
				nxtDisplayString(7,"3");
				motor[J2] = 0;
		}
	}
	motor[J1] = 0; //stops both motors
	motor[J2] = 0;
}

task main()
{
	nMotorEncoder(J1) = 0; //reset encoders
	nMotorEncoder(J2) = 0;
	for(int i = 0; i< LENGTH; i++){
		goToTheta((int)path[i][0], (int)path[i][1]); //for each angle pair, go to said angles
	}
	while(1){ //just displays encoder values
		nxtDisplayClearTextLine(5);
		nxtDisplayClearTextLine(6);
		nxtDisplayString(5,"%d",nMotorEncoder(J1));
		nxtDisplayString(6,"%d",nMotorEncoder(J2));
		
	};
}
