package com.example.homeweatherstationapp;


import static java.sql.Types.NULL;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.example.homeweatherstationapp.ui.home.HomeFragment;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.ArrayList;
import java.util.List;

public class BackgroundWorker extends AsyncTask<String,Void,String> {
    public static List<String> LIST1 = new ArrayList<>();//заполнение StreetTemp
    public static List<String> LIST2 = new ArrayList<>();//заполнение StreetHum
    public static List<String> LIST3 = new ArrayList<>();//заполнение Rain
    public static List<String> LIST4 = new ArrayList<>();//заполнение BatteryCharge
    public static List<String> LIST5 = new ArrayList<>();//заполнение WindDirect
    public static List<String> LIST6 = new ArrayList<>();//заполнение WindSpeed
    public static List<String> LIST7 = new ArrayList<>();//заполнение HomeTemp
    public static List<String> LIST8 = new ArrayList<>();//заполнение HomeHum
    public static List<String> LIST9 = new ArrayList<>();//заполнение Pressuare
    public static List<String> LIST10 = new ArrayList<>();//заполнение Time для домаш параметров
    public static List<String> LIST11 = new ArrayList<>();//заполнение Time для уличн параметров

    public static int ChartDaysMode = 1;

    public static boolean StopFlag;
    public static String result = "";
    public static boolean EndFlag = false;

    Context context;
    //AlertDialog alertDialog;
    public BackgroundWorker(Context ctx){
        context = ctx;
    }
    @Override
    protected String doInBackground(String... params) {
        String type = params[4];
        String login_url = "";
        int id = 1;
        String line = "";
        StopFlag = false;

        switch (ChartDaysMode) {
            case 1:
                login_url = params[0];
                break;
            case 3:
                login_url = params[1];
                break;
            case 5:
                login_url = params[2];
                break;
            case 7:
                login_url = params[3];
                break;
            default:
                break;
        }

        try {
            URL url = new URL(login_url);
            HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
            httpURLConnection.setRequestMethod("POST");
            httpURLConnection.setDoOutput(true);
            httpURLConnection.setDoInput(true);
            OutputStream outputStream = httpURLConnection.getOutputStream();
            BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(outputStream, "UTF-8"));

            String post_data = "";
            if (type.equals("register")) {
                post_data = URLEncoder.encode("id", "UTF-8") + "=" + URLEncoder.encode(Integer.toString(id), "UTF-8");
            } else if (type.equals("login")) {
                post_data = URLEncoder.encode("id", "UTF-8") + "=" + URLEncoder.encode(Integer.toString(id), "UTF-8");
            }

            bufferedWriter.write(post_data);
            bufferedWriter.flush();
            bufferedWriter.close();
            outputStream.close();
            InputStream inputStream = httpURLConnection.getInputStream();

            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream, "UTF-8"));
            result = "";
            line = "";
            while ((line = bufferedReader.readLine()) != null) {
                result += line;
            }
            bufferedReader.close();
            inputStream.close();
            httpURLConnection.disconnect();
            FillAllParamsNew(result);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    protected void onPreExecute() {
        //alertDialog = new AlertDialog.Builder(context).create();
        //alertDialog.setTitle("Login Status");
        LIST1.clear();
        LIST2.clear();
        LIST3.clear();
        LIST4.clear();
        LIST5.clear();
        LIST6.clear();
        LIST7.clear();
        LIST8.clear();
        LIST9.clear();
        LIST10.clear();
        LIST11.clear();
        Toast.makeText(context.getApplicationContext(),"Пожалуйста подождите, идет синхронизация с базой данных...",Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPostExecute(String result) {

        FillDisplayParam();
        Toast.makeText(context.getApplicationContext(),"Загрузка информации с БД завершена!",Toast.LENGTH_LONG).show();
        EndFlag = true;
    }
    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
    public void FillAllParamsNew(String result)
    {
        int flag = 0;
        int i = 0;
        int k = 0;
        int id = 1;//для домашних параметров
        int id1 = 1;//для уличных параметров, т.к. их кол-во может быть разным
        String Result;
        //for(int id = 1; id <= 2000; id++)
        while (i < result.length())
        {
            //заполнение HomeTemp
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST7.add(id-1, Result);}
            i++;
            k = i;
            //заполнение StreetTemp
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST1.add(id1-1, Result);}
            i++;
            k = i;
            //заполнение HomeHum
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST8.add(id-1, Result);}
            i++;
            k = i;
            //заполнение StreetHum
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST2.add(id1-1, Result);}
            i++;
            k = i;
            //заполнение Pressuare
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST9.add(id-1, Result);}
            i++;
            k = i;
            //заполнение WindSpeed
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST6.add(id1-1, Result);}
            i++;
            k = i;
            //заполнение WindDirect
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST5.add(id1-1, Result);}
            i++;
            k = i;
            //заполнение Rain
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST3.add(id1-1, Result);}
            i++;
            k = i;
            //заполнение BatteryCharge
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {LIST4.add(id1-1, Result); id1++; flag = 1;}
            i++;
            k = i;
            //заполнение Time
            while(result.charAt(i) != '|')
            {
                i++;
            }
            Result = result.substring(k,i);
            if (!Result.equals("NULL")) {
                LIST10.add(id-1, Result);
                if (flag == 1)
                {
                    LIST11.add(id1-2, Result);
                    flag = 0;
                }
            }
            i=i+6;
            k = i;

            id++;
        }
        if (i != 0) HomeFragment.time_for_display = LIST10.get(LIST10.size() - 1).replace(',', '\n');
        //Форматирование времени
        /*for (int j = 0; j < LIST10.size(); j++) {
            LIST10.set(j, LIST10.get(j).substring(0, 8));
        }*/

    }
    public void FillDisplayParam()
    {
        try {
            HomeFragment.HOME_TEMP.setText(LIST7.get(LIST7.size() - 1));
            if (!LIST1.get(LIST1.size() - 1).equals("NULL")) HomeFragment.STREET_TEMP.setText(LIST1.get(LIST1.size() - 1));
            else HomeFragment.STREET_TEMP.setText("");
            HomeFragment.HOME_HUM.setText(LIST8.get(LIST8.size() - 1));
            if (!LIST2.get(LIST2.size() - 1).equals("NULL")) HomeFragment.STREET_HUM.setText(LIST2.get(LIST2.size() - 1));
            else HomeFragment.STREET_HUM.setText("");
            if (!LIST3.get(LIST3.size() - 1).equals("NULL")) HomeFragment.RAIN.setText(LIST3.get(LIST3.size() - 1));
            else HomeFragment.RAIN.setText("");
            if (!LIST4.get(LIST4.size() - 1).equals("NULL")) HomeFragment.VBat.setText(LIST4.get(LIST4.size() - 1));
            else HomeFragment.VBat.setText("");
            if (!LIST6.get(LIST6.size() - 1).equals("NULL")) HomeFragment.WIND_SPEED.setText(LIST6.get(LIST6.size() - 1));
            else HomeFragment.WIND_SPEED.setText("");
            if (!LIST5.get(LIST5.size() - 1).equals("NULL")) HomeFragment.WIND_DIRECTION.setText(LIST5.get(LIST5.size() - 1));
            else HomeFragment.WIND_DIRECTION.setText("");
            HomeFragment.PRESSURE.setText(LIST9.get(LIST9.size() - 1));
            HomeFragment.TIME.setText(HomeFragment.time_for_display);
            //вывод индикатора направления ветра
            switch (LIST5.get(LIST5.size() - 1)) {
                case "N-W":
                    HomeFragment.imagewind.setImageResource(R.drawable.nw);
                    break;
                case "N":
                    HomeFragment.imagewind.setImageResource(R.drawable.n);
                    break;
                case "S":
                    HomeFragment.imagewind.setImageResource(R.drawable.s);
                    break;
                case "E":
                    HomeFragment.imagewind.setImageResource(R.drawable.e);
                    break;
                case "W":
                    HomeFragment.imagewind.setImageResource(R.drawable.w);
                    break;
                case "N-E":
                    HomeFragment.imagewind.setImageResource(R.drawable.ne);
                    break;
                case "S-W":
                    HomeFragment.imagewind.setImageResource(R.drawable.sw);
                    break;
                case "S-E":
                    HomeFragment.imagewind.setImageResource(R.drawable.se);
                    break;
                default:
                    HomeFragment.imagewind.setImageResource(R.drawable.def);
                    break;
            }
            //вывод индикатора прогноза погоды
            if ((Float.parseFloat(LIST6.get(LIST6.size() - 1)) == 0f) && (Float.parseFloat(LIST3.get(LIST3.size() - 1)) <= 10f)) {
                HomeFragment.weath_forecast.setImageResource(R.drawable.weath_sunny);
            } else if ((Float.parseFloat(LIST6.get(LIST6.size() - 1)) >= 10f) && (Float.parseFloat(LIST3.get(LIST3.size() - 1)) <= 10f)) {
                HomeFragment.weath_forecast.setImageResource(R.drawable.weath_only_clouds);
            } else if ((Float.parseFloat(LIST6.get(LIST6.size() - 1)) < 10f) && (Float.parseFloat(LIST3.get(LIST3.size() - 1)) <= 10f)) {
                HomeFragment.weath_forecast.setImageResource(R.drawable.weath_cloud);
            } else if ((Float.parseFloat(LIST3.get(LIST3.size() - 1)) < 90f) && (Float.parseFloat(LIST3.get(LIST3.size() - 1)) > 15f)) {
                HomeFragment.weath_forecast.setImageResource(R.drawable.weath_rainy);
            } else {

            }
        }
        catch (Exception e)
        {

        }
    }
    public void FillAllParams(String result, int id)
    {
        int i = 0;
        int k = 0;
        //заполнение HomeTemp
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST7.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение StreetTemp
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST1.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение HomeHum
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST8.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение StreetHum
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST2.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение Pressuare
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST9.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение WindSpeed
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST6.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение WindDirect
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST5.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение Rain
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST3.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение BatteryCharge
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST4.add(id- 1, result.substring(k,i));
        i++;
        k = i;
        //заполнение Time
        while(result.charAt(i) != '|')
        {
            i++;
        }
        LIST10.add(id- 1, result.substring(k,i));
    }
}
