package com.example.FirstPRo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.*;
import java.util.List;

/**
 * Created by ebajian on 2016/4/14.
 */
public class NewFrame  extends JFrame {
    private Printer new_printer=null;
    //private String s_name=null;
    //private String s_type=null;

    private JTextField jt_name =null;
    private JTextField jt_type =null;
    private JTextField jt_speed =null;

    public NewFrame() {
        JLabel jl = new JLabel("Add a new printer", SwingUtilities.CENTER);
        Font font = new Font("Arial", Font.BOLD, 20);
        jl.setFont(font);
        jl.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        this.add(jl, BorderLayout.NORTH);

        font = new Font("Arial",Font.PLAIN,12);

        JLabel jl_name = new JLabel("Name    ",SwingUtilities.RIGHT);
        jl_name.setFont(font);

        JLabel jl_model = new JLabel("Model    ",SwingUtilities.RIGHT);
        jl_model.setFont(font);

        JLabel jl_speed = new JLabel("Speed    ",SwingUtilities.RIGHT);
        jl_speed.setFont(font);

        JPanel jp_center_left = new JPanel();
        jp_center_left.setLayout(new GridLayout(5,1));
        jp_center_left.add(jl_name);
        jp_center_left.add(jl_model);
        jp_center_left.add(jl_speed);

        jt_name = new JTextField();
        jt_type = new JTextField();
        jt_speed = new JTextField();

        JPanel jp_center_right = new JPanel();
        jp_center_right.setLayout(new GridLayout(5,1));
        jp_center_right.add(jt_name);
        jp_center_right.add(jt_type);
        jp_center_right.add(jt_speed);

        JPanel jp_center = new JPanel();
        jp_center.setLayout(new GridLayout(1,2));
        jp_center.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 60));
        jp_center.add(jp_center_left);
        jp_center.add(jp_center_right);

        JButton jb1 = new JButton("Apply");
        jb1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String s_name=jt_name.getText().trim();
                String s_type=jt_type.getText().trim();
                String s_speed=jt_speed.getText().trim();
                Double d_speed=Double.parseDouble(s_speed);
                new_printer = new Printer(s_name,s_type,d_speed);

                PrintersManeger.list_Printers.add(new_printer);
                PFrame.comboBox.addItem(new_printer.name);

                List<String> dataList=new ArrayList<String>();
                dataList.add("Printer Name,Model Type,Speed");
                for(int i=0;i<PrintersManeger.list_Printers.size();i++){
                    dataList.add(PrintersManeger.list_Printers.get(i).name+","+PrintersManeger.list_Printers.get(i).
                            model_type+","+String.valueOf(PrintersManeger.list_Printers.get(i).speed));
                }
                exportCSV.exportCSV(new File("C:/Users/ebajian/Documents/Printers.csv"), dataList);

                dispose();
            }
        });

        JButton jb2 = new JButton("Cancel");
        jb2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        JPanel jp_south = new JPanel();
        jp_south.add(jb1);
        jp_south.add(jb2);
        jp_south.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        this.add(jp_center);
        this.add(jp_south,BorderLayout.SOUTH);
    }
}
