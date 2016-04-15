package com.example.FirstPRo;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by ebajian on 2016/4/14.
 */
public class JobGenerator {
    public static int nJob;

    public static ArrayList<PrintJob> JobGenerator(int n){

        ArrayList<PrintJob> list= new ArrayList<PrintJob>();
        nJob=n;

        for(int i=0;i<nJob;i++){
            int nPage=1+(int)(Math.random()*50);
            PrintJob pj=new PrintJob("user_"+String.valueOf(i),"job_"+String.valueOf(i),nPage);
            list.add(pj);
        }

        return list;
    }
}
