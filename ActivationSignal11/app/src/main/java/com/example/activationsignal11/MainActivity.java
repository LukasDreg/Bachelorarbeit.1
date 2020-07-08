package com.example.activationsignal11;


import androidx.appcompat.app.AppCompatActivity;

import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;

import android.content.Context;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraManager;


public class MainActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    //Number of Repetitions of the on-off signal in the activation signal
    private static final int signalRepetition = 10; //
    //Time difference of the on-time between the sensor modules in milliseconds
    //for example: signalModuleDifference = 1  --> flash time for module 1: 20 ms, flash time for module 2: 21 ms ...
    private static final int signalModuleDifference = 5; //
    //Time when the flash is off between the activation signal repititions and basic time for the flash signal (signalModuleDifference is added) in milliseconds
    private static final int signalOffTime = 20;

    //Int to record the selected sensor module
    private int selectedModule = 0; //
    //Int to keep track of the activation signal process
    private int flashCount = 0; //

    private Handler handler = new Handler();

    private CameraManager mCameraManager;
    private String mCameraId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Spinner spinner = findViewById(R.id.spinner1);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(MainActivity.this, R.array.numbers, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(this);

        mCameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
        try {
            assert mCameraManager != null;
            mCameraId = mCameraManager.getCameraIdList()[0];
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }

        final Button button = findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                button.setClickable(false);

                try {
                    for (int i = 0; i < signalRepetition; i++) {
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                //Turn flash On
                                turnOnFlashLight();
                                Log.d("myTag", "ON!!!!!!!!!!!!!!!!!!");
                            }
                            //Set up the moments when the flash gets turned on for all repetitions
                        }, signalOffTime + i * (signalOffTime * 2 + selectedModule * signalModuleDifference)); //old: 20 + i * (40 + selectedModule * 5)
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                //keep track of the number of repetitions
                                flashCount++;
                                //Turn flash Off
                                turnOffFlashLight();
                                Log.d("myTag", "OFF???????????????????");
                                if(flashCount >= signalRepetition)
                                {
                                    //After all the activation signal repetitions are executed
                                    flashCount = 0;
                                    button.setClickable(true);
                                }
                                //After all the activation signal repetitions are executed


                            /*
                            //Start decoding the information
                            StorageManager.getInstance().timeStartRecording = System.nanoTime();
                            recordingData=true;

                            //Starts a new timer to check timeout for decoding
                            TimerID++;
                            new Timer().schedule(new DecodingTimeOutTask(TimerID),TIME_OUT_LENGTH);

                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    btnCapture.setClickable(true);
                                }
                            });

                             */


                            }
                            //Set up the moments when the flash gets turned off for all repetitions
                        }, signalOffTime * 2 + selectedModule * signalModuleDifference + i * (signalOffTime * 2 + selectedModule * signalModuleDifference)); // old: 40 + selectedModule * 5 + i * (40 + selectedModule * 5)
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }

                /*
                try {
                    for (int i = 0; i < signalRepetition; i++) {
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                //Turn flash On
                                turnOnFlashLight();
                            }
                            //Set up the moments when the flash gets turned on for all repetitions
                        }, signalOffTime + i * (signalOffTime * 2 + selectedModule * signalModuleDifference)); //old: 20 + i * (40 + selectedModule * 5)
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                //Turn flash Off
                                turnOffFlashLight();
                                //keep track of the number of repititions
                                flashCount++;
                            }
                            //Set up the moments when the flash gets turned off for all repetitions
                        }, signalOffTime * 2 + selectedModule * signalModuleDifference + i * (signalOffTime * 2 + selectedModule * signalModuleDifference)); // old: 40 + selectedModule * 5 + i * (40 + selectedModule * 5)
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }

                 */

                /*
                try {
                    for (int i = 0; i <= 100; i++) {
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                turnOnFlashLight();
                            }
                        }, 20 + i * (40 + selectedModule * 5)); //old: 20 + i * (40 + record)
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                turnOffFlashLight();
                                if (count > 0) {
                                    button.setClickable(true);
                                    count = 0;
                                } else {
                                    count++;
                                }
                            }
                        }, 40 + selectedModule * 5 + i * (40 + selectedModule * 5)); // old 40 + record + i * (40 + record)
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }

                 */
            }
        });
    }


    private void turnOnFlashLight() {
        try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                mCameraManager.setTorchMode(mCameraId, true);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void turnOffFlashLight() {
        try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                mCameraManager.setTorchMode(mCameraId, false);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        selectedModule = position;
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }
}
