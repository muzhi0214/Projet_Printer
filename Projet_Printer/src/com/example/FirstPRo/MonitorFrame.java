package com.example.FirstPRo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.*;

/**
 * Created by ebajian on 2016/4/14.
 */
public class MonitorFrame extends JFrame {

    public static JTextArea ta1=null;
    public static JTextArea ta2=null;
    public MonitorFrame() {

        ta1=new JTextArea();
        JScrollPane sp1=new JScrollPane(ta1);

        ta2=new JTextArea();
        JScrollPane sp2=new JScrollPane(ta2);

        JButton jb1 = new JButton("Generate PrintJobs");

        jb1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {

                int n=10+(int)(Math.random()*20);
                //System.out.print(n);

                PrintersManeger.list_Jobs = JobGenerator.JobGenerator(n);
                //System.out.print(PrintersManeger.list_Jobs.size());

                for(int i=0;i<PrintersManeger.list_Jobs.size();i++){
                    PrintJob pj=PrintersManeger.list_Jobs.get(i);
                    ta1.append(pj.name+", "+pj.user+", "+pj.nPage+"pages\n");
                }
            }
        });

        final ArrayList<DoPrint> list_thread=new ArrayList<DoPrint>();
        JButton jb2 = new JButton("Print");
        jb2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                for(int i=0;i<PrintersManeger.list_Printers.size();i++){
                    DoPrint t=new DoPrint(PrintersManeger.list_Printers.get(i));
                    list_thread.add(t);
                }
                for(int i =0;i<list_thread.size();i++){
                    Thread thread=new Thread(list_thread.get(i));
                    thread.start();
                }
            }
        });

        JPanel jp_north = new JPanel();
        jp_north.setLayout(new GridLayout(1,2));
        jp_north.add(jb1);
        jp_north.add(jb2);
        jp_north.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        JPanel jp_center = new JPanel();
        jp_center.setLayout(new GridLayout(1,2));
        jp_center.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        jp_center.add(sp1);
        jp_center.add(sp2);

        JButton jb3 = new JButton("View Printers");
        jb3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                PFrame frame = new PFrame(PrintersManeger.list_Printers);

               // frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
                frame.setSize(400, 350);
                frame.setResizable(true);
                frame.setLocationRelativeTo(null);
            }
        });

        JPanel jp_south = new JPanel();
        jp_south.add(jb3);
        jp_south.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        this.setTitle("PrintJob Monitor");
        this.add(jp_north);
        this.add(jp_north,BorderLayout.NORTH);
        this.add(jp_center);
        this.add(jp_south,BorderLayout.SOUTH);
    }
}
