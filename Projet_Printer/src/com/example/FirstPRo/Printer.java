package com.example.FirstPRo;

import java.util.ArrayList;

/**
 * Created by ebajian on 2016/4/13.
 */
public class Printer {

    String name;
    String model_type;
    Double speed;

    ArrayList<String> list_user = new ArrayList<String>();
    ArrayList<String> List_task = new ArrayList<String>();
    ArrayList<String> List_status = new ArrayList<String>();

    public Printer(String name, String model_type, Double speed){
        this.name=name;
        this.model_type=model_type;
        this.speed=speed;
    }
}
