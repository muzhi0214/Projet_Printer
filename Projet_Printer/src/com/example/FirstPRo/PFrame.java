package com.example.FirstPRo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by ebajian on 2016/4/13.
 */


public class PFrame extends JFrame {
    private ArrayList<Printer> Plist = new ArrayList<Printer>();
    public static JComboBox comboBox= null;
    private JTextField jt_name = null;
    private JTextField jt_type = null;
    private JTextField jt_speed = null;

    public PFrame( ArrayList<Printer> list_Printers ){
       this.Plist = list_Printers;

        JLabel jl = new JLabel("Printer Manager",SwingUtilities.CENTER);
        Font font = new Font("Arial", Font.BOLD,24);
        jl.setFont(font);
        jl.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        this.add(jl,BorderLayout.NORTH);

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



        jt_name = new JTextField(Plist.get(0).name);
        jt_type = new JTextField(Plist.get(0).model_type);
        jt_speed = new JTextField(String.valueOf(Plist.get(0).speed));
        jt_name.setEditable(false);
        jt_type.setEditable(false);
        jt_speed.setEditable(false);

        JPanel jp_center_right = new JPanel();
        jp_center_right.setLayout(new GridLayout(5,1));
        jp_center_right.add(jt_name);
        jp_center_right.add(jt_type);
        jp_center_right.add(jt_speed);

        JPanel jp_left = new JPanel();
        jp_left.setLayout(new GridLayout(5,1));
        jp_left.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        comboBox=new JComboBox();

        for(int i = 0;i < Plist.size(); i ++){
            Printer P_temp=Plist.get(i);
            comboBox.addItem(P_temp.name);
        }

        comboBox.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int i = comboBox.getSelectedIndex();
                //System.out.print(i);

                jt_name.setText(Plist.get(i).name);
                jt_type.setText(Plist.get(i).model_type);
                jt_speed.setText(String.valueOf(Plist.get(i).speed));
                //jt_type = new JTextField(Plist.get(i).model_type);
                //jt_speed = new JTextField(String.valueOf(Plist.get(i).speed));
            }
        });

        jp_left.add(comboBox);

        JPanel jp_center = new JPanel();
        jp_center.setLayout(new GridLayout(1,3));
        jp_center.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 60));
        jp_center.add(jp_left);
        jp_center.add(jp_center_left);
        jp_center.add(jp_center_right);

        JButton button_add = new JButton("New Printer");
        button_add.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                NewFrame frame = new NewFrame();

               // frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
                frame.setSize(250, 350);
                frame.setResizable(true);
                frame.setLocationRelativeTo(null);
            }
        });

        JPanel jp_south = new JPanel();
        jp_south.add(button_add);
        //jp_south.add(jb2);
        jp_south.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 260));

        this.add(jp_center);
        this.add(jp_south,BorderLayout.SOUTH);

    }
}
