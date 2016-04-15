package com.example.FirstPRo;

import javax.swing.*;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by ebajian on 2016/4/13.
 */
public class PrintersManeger {

    public static ArrayList<Printer> list_Printers = new ArrayList<Printer>();
    public static ArrayList<PrintJob> list_Jobs = new ArrayList<PrintJob>();

    public static void main(String[] args){

        List<String> dataList=readLocalCSV.readLocalCSV(new File("C:/Users/ebajian/Documents/Printers.csv"));

        if(dataList!=null && !dataList.isEmpty()){
            for(int i=1;i<dataList.size();i++){
                String[] ss = dataList.get(i).split(",");
                Printer p=new Printer(ss[0],ss[1],Double.parseDouble(ss[2]));
                list_Printers.add(p);
            }
        }

        /*
        Printer p1=new Printer("printer_A","type_A",5.0);
        Printer p2=new Printer("printer_B","type_B",10.0);
        Printer p3=new Printer("printer_C","type_C",20.0);
        list_Printers.add(p1);
        list_Printers.add(p2);
        list_Printers.add(p3);
        */


        //PFrame frame = new PFrame(list_Printers);
        MonitorFrame frame=new MonitorFrame();

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        frame.setSize(500, 500);
        frame.setResizable(true);
        frame.setLocationRelativeTo(null);

        /*
        List<String> dataList=new ArrayList<String>();
        dataList.add("Printer Name,Model Type,Speed");
        for(int i=0;i<list_Printers.size();i++){
            dataList.add(list_Printers.get(i).name+","+list_Printers.get(i).model_type+","+String.valueOf(list_Printers.get(i).speed));
        }
        exportCSV.exportCSV(new File("C:/Users/ebajian/Documents/Printers.csv"), dataList);
        */
    }
}
