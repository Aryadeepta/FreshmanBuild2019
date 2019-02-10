package frc.robot;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.kauailabs.navx.frc.AHRS;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.cameraserver.CameraServer;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.SerialPort;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.Timer;

import com.ctre.phoenix.motorcontrol.can.TalonSRX;

public class Robot extends TimedRobot { //implements PIDOutput {
    Joystick driverJoy;

    TalonSRX fl = new TalonSRX(2); // front left motor
    TalonSRX fr = new TalonSRX(4); // front right motor
    TalonSRX bl = new TalonSRX(3); // back left motor
    TalonSRX br = new TalonSRX(1); // back right motor

    boolean startTimeSet = false;
    double startTime = 0;

    double yawAngle = 0.0;
    boolean firstTime = true;
    double goalAngle = 0.0;
    double PIDValue = 0.0;

    final int kTimeoutMs = 30;
	final boolean kDiscontinuityPresent = true;
	final int kBookEnd_0 = 910;		/* 80 deg */
    final int kBookEnd_1 = 1137;	/* 100 deg */
    
    double distance = 0.0;
    int autostage = 0;

    AHRS NAVXgyro = new AHRS(SerialPort.Port.kMXP);

    boolean done = false;

//    PIDController PID = new PIDController(.01, 0, .01, NAVXgyro, this);

    @Override
    public void robotInit() { //When the robot starts
        driverJoy = new Joystick(0); // initializes the main controller

        bl.configFactoryDefault();
        bl.configSelectedFeedbackSensor(FeedbackDevice.CTRE_MagEncoder_Absolute, 0, kTimeoutMs);
        br.configFactoryDefault();
        br.configSelectedFeedbackSensor(FeedbackDevice.CTRE_MagEncoder_Absolute, 0, kTimeoutMs);
        fl.follow(bl);
        fr.follow(br);
        br.setSensorPhase(false);
        bl.setSensorPhase(false);
        CameraServer.getInstance().startAutomaticCapture();
        bl.set(ControlMode.PercentOutput, (.01));
        br.set(ControlMode.PercentOutput, (.01));
        System.out.println(br.getSelectedSensorPosition());
        System.out.println(bl.getSelectedSensorPosition());
        br.getSelectedSensorVelocity();
        bl.getSelectedSensorVelocity();

        NAVXgyro.reset();

        initQuadrature();
        
    }

 @Override
    public void autonomousInit() {

    NAVXgyro.reset();
    firstTime = true;
//    PID.setAbsoluteTolerance(5);
//    PID.setInputRange(-180, 180);
//    PID.setOutputRange(-1, 1);
//    PID.setContinuous();
//    PID.enable();

br.setSensorPhase(true);
System.out.println(br.getSelectedSensorPosition(0));

    }

    @Override
    public void autonomousPeriodic () {
    
  //  if (firstTime) {
  //      firstTime = false;
   //     NAVXgyro.reset();
    //    autostage = 0;

    int selSenPos = br.getSelectedSensorPosition(0); //number of ticks
    int pulseWidthWithoutOverflows = br.getSensorCollection().getPulseWidthPosition() & 0xFFF;

	// System.out.print("pulseWidPos:" + pulseWidthWithoutOverflows + "   =>    " + "selSenPos:" + selSenPos);

    double pulses = selSenPos;
    double revolution = Math.abs(pulses/4095.0);

    double distance_traveled = revolution*2*(3.1415629*3);
    System.out.println("Distance_traveled: " + distance_traveled);

    System.out.print("revolution : " + revolution);

    if (distance_traveled < 110 && !done) {
        br.set(ControlMode.PercentOutput, (-.5));
        bl.set(ControlMode.PercentOutput, (.5));
    }
    else if(distance_traveled>=110) {
            br.set(ControlMode.PercentOutput, (0));
            br.getSensorCollection().setQuadraturePosition(10, kTimeoutMs);
            br.getSensorCollection().setPulseWidthPosition(10, kTimeoutMs);
            bl.set(ControlMode.PercentOutput, (0));
            bl.getSensorCollection().setQuadraturePosition(10, kTimeoutMs);
            bl.getSensorCollection().setPulseWidthPosition(10, kTimeoutMs);
            done = true;
        }
        else{
            System.out.println("ERROR");
            pulses = 0;
            distance_traveled = 0;
            revolution = 0;

        }
    }

    public void initQuadrature() {
		int pulseWidth = br.getSensorCollection().getPulseWidthPosition();

		if (kDiscontinuityPresent) {

			int newCenter;
			newCenter = (kBookEnd_0 + kBookEnd_1) / 2;
			newCenter &= 0xFFF;

			pulseWidth -= newCenter;
		}

		br.getSensorCollection().setQuadraturePosition(pulseWidth, kTimeoutMs);
    }

String ToDeg (int units) {
		double deg = units * 360.0 / 4096.0;

		/* truncate to 0.1 res */
		deg *= 10;
		deg = (int) deg;
		deg /= 10;

        return "" + deg;

    }

/*    if (autostage == 0) {
            if (distance < HAB_TO_CARGO) {
                bl.set(ControlMode.PercentOutput, (-.25));
                br.set(ControlMode.PercentOutput, (.25));
            }
            else {
                autostage++;
                bl.set(ControlMode.PercentOutput, (0));
                br.set(ControlMode.PercentOutput, (0));
                NAVXgyro.reset();
                ResetEncoders();
                PID.setSetpoint(-90);
            }
        }    
        else if (autostage == 1) {
            if (startTimeSet == false) {
                startTime = Timer.getFPGATimestamp();
                startTimeSet = true;
            }
            if (Timer.getFPGATimestamp() - startTime < 1) {
                bl.set(ControlMode.PercentOutput, (PIDValue));
                br.set(ControlMode.PercentOutput, (PIDValue));
            }
            else {
                autostage++;
                bl.set(ControlMode.PercentOutput, (0));
                br.set(ControlMode.PercentOutput, (0));
                NAVXgyro.reset();
                ResetEncoders();
                PID.disable();
            }
        }   
        else if (autostage == 2) {
            distance = AverageDistance();
            if (distance < BOT_TO_CARGO) {
                bl.set(ControlMode.PercentOutput, (-.25));
                br.set(ControlMode.PercentOutput, (.25));
            }
            else {
                autostage++;
                bl.set(ControlMode.PercentOutput, (0));
                br.set(ControlMode.PercentOutput, (0));
                NAVXgyro.reset();
                ResetEncoders();
            }
        }
    }
*/

    @Override
    public void teleopPeriodic () { //When you get to start moving the robot
        double straight = (driverJoy.getRawAxis(1)); // amount up or down on the left toggle
        double leftTurn = (driverJoy.getRawAxis(3));
        double rightTurn = (driverJoy.getRawAxis(2));

        //Arcade Mode
        bl.set(ControlMode.PercentOutput, (-straight - rightTurn + leftTurn));
        br.set(ControlMode.PercentOutput, (straight - rightTurn + leftTurn));
   }

/*    @Override
    public void pidWrite(double output) {
        PIDValue = output;
    } */
}