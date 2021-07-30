/*
 * Sample Program for GR001:G-ROBOT
 * Copyright(C) all right reserved. 2011 Isao Hara,AIST,Japan.
 *
 */
#include <GR001/stdafx.h>
#include <GR001/GROBO.h>
#include <GR001/SerialRobot.h>
#include <iostream>


static int loop = 1;
static GR001 *G_ROBO;

/*
  Signal handler for Ctr-C
  Close com_fd and stop threads
*/
void 
sighandler(int x)
{
  loop = 0;
  G_ROBO->setServo(0, 1);
  delete G_ROBO;
  return;
}

/*
 *  M A I N 
 */
int 
main(int argc, char* argv[])
{
  int c;
  char x;
  char line[1024];
  int v1,v2,v3;
  int count;

  int portNo = 0;
  char fname[128] = "Motion.m";
  int devnum = 0;
  int sval;

  int freeM=0;

#ifdef WIN32
   char *devname = "COM1";
#else
 // char *devname = "/dev/ttyS0";
  char *devname = "/dev/ttyUSB0";
#endif

  signal(SIGINT, sighandler);

  if(argc > 1){
    devname  = (char *)argv[1];
  }

  G_ROBO = new GR001((char *)devname);


  if( G_ROBO->connect() < 0 ){
	  std::cerr << "Error: can't find G-Robot: " <<  devname << std::endl;
 //   exit(1);
  }

  if(G_ROBO->startThread() == 0){
	  std::cerr << "Error: fail to create thread" << std::endl;
    delete G_ROBO;
    exit(1);
  }

  G_ROBO->setMotionDir("motion");
  while(loop){
    std::cout << "G-001 >";
    fgets(line, 1024, stdin);

    switch(line[0]){
      case 'q':
		 std::cerr << "Terminated" <<std::endl;
        loop = 0;
        break;

      case 'i':
		  G_ROBO->initPosition();
        break;

      case 'S':
		  // G_ROBO->servo("all", true);
		  G_ROBO->setServo(1,0);
        break;

      case 's':
        c=0;
	    count=SSCANF(line,"s %c", &x);
        if( count == 1){
          switch(x){
            case 'a':
              c=4;
              break;
            case 'l':
              c=7;
              break;
            default:
              if(isdigit(x)){
                c = x - 0x30;
              }
              break;
          }
        }
		G_ROBO->setServo(0, c);
        break;

     case 'f':
		 if(freeM == 1){ freeM=0;}
		 else{ freeM=1;}
		G_ROBO->setFreeMotion(freeM);
       
        break;

	  case 'b':
		  G_ROBO->setServo(2,0);
        break;

      case 'm':
	    SSCANF(line,"m %d %d %d", &v1, &v2, &v3);
        G_ROBO->moveJoint( (char)v1, (short)v2, (unsigned short)v3);
        break;

      case 't':
	     SSCANF(line,"t %d", &sval);
		 std::cerr << " motioTime = " << G_ROBO->setDefaultMotionTime(sval) << std::endl;
        break;

      case 'r':
		  G_ROBO->startMotion();
        break;

      case 'R':
	    c = SSCANF(line,"R %d", &count);
        if(c != 1){
          count = 1;
        }
        G_ROBO->setMotionCount(count);
        break;

      case 'c':
	    SSCANF(line,"c %s", fname);
		std::cout << "fname = " << fname << std::endl;
        G_ROBO->appendCurrentPosture();
		G_ROBO->saveMotionToM(fname);
        break;

      case 'e':
		G_ROBO->saveMotionToM(NULL);
        break;

      case 'C':
        	G_ROBO->clearMotion();
        break;

     case 'p':
        G_ROBO->setJointsFromString( &line[1] );
		G_ROBO->startMotion();
        break;

      case 'l':
	    SSCANF(line,"l %s", fname);
		std::cout << "fname = "<< fname << std::endl;
        G_ROBO->loadMotion(fname);
        break;

      case 'a':
	    SSCANF(line,"a %s", fname);
		std::cout << "fname = "<< fname << std::endl;

		if(G_ROBO->loadMotion(fname) > 0){
		  G_ROBO->setMotionCount(1);
		}
        break;
 
/*
      case 'a':
	    c = SSCANF(line,"a %d", &count);
        if( c == 1){
	      std::cerr << "Motion " << count << std::endl;
          G_ROBO->activateMotionSlot((unsigned char)count);
        }
      case 'A':
	     c = SSCANF(line,"A %d", &count);
        if(c == 1){
	      std::cerr << "Motion " << count << std::endl;
		  G_ROBO->activateSenario((unsigned char)count);
        }
*/
        break;

      default:
        break;
    }
    G_ROBO->printPosture();
  }

  /** Servo Off */
  G_ROBO->setServo(0, 1);

  delete G_ROBO;

  std::cerr <<"Terminated." << std::endl;

  exit(0);
}

