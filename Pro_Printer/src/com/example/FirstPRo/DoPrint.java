package com.example.FirstPRo;

/**
 * Created by ebajian on 2016/4/14.
 */
public class DoPrint implements Runnable {
    public Printer p;
    public DoPrint(Printer p){
        this.p=p;
    }
    public synchronized PrintJob getPrintJob(){
        if(PrintersManeger.list_Jobs.size()>0){
            PrintJob pj=PrintersManeger.list_Jobs.get(0);
            PrintersManeger.list_Jobs.remove(0);
            return pj;
        }else{
            return null;
        }
    }
    public void run(){
        while(true){
            PrintJob nextJb=getPrintJob();
            if(nextJb!=null){
                Double sp=p.speed;
                int pg= nextJb.nPage;
                double time_cost1=(double)(Math.round(pg/sp*100))/100;
                long time_cost=Math.round(1000*pg/sp);
                try{
                    Thread.sleep(time_cost);
                }catch (Exception e){
                    e.printStackTrace();
                }
                MonitorFrame.ta2.append(p.name+" : "+nextJb.name+ " / "+ nextJb.nPage +" pages / cost time "+ time_cost1+ " seconds\n");

            }else{
                try{
                    Thread.sleep(1000);
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }
    }
}
