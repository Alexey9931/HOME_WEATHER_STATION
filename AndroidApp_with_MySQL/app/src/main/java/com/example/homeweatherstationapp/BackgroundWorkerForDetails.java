package com.example.homeweatherstationapp;

import android.content.Context;
import android.graphics.Color;
import android.os.AsyncTask;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.homeweatherstationapp.ui.home.HomeFragment;
import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;

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
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

public class BackgroundWorkerForDetails extends AsyncTask<View,Void,String> {
        TextView textView_avg_str_temp;
        TextView textView_avg_home_temp;
        TextView textView_avg_str_hum;
        TextView textView_avg_home_hum;
        TextView textView_avg_rainfall;
        TextView textView_avg_wind_speed;
        TextView textView_max_str_temp;
        TextView textView_max_home_temp;
        TextView textView_max_str_hum;
        TextView textView_max_home_hum;
        TextView textView_max_rainfall;
        TextView textView_max_wind_speed;
        TextView textView_max_bat_charge;
        TextView textView_min_str_temp;
        TextView textView_min_home_temp;
        TextView textView_min_str_hum;
        TextView textView_min_home_hum;
        TextView textView_min_rainfall;
        TextView textView_min_wind_speed;
        TextView textView_min_bat_charge;
        PieChart WindDirectDiagram;
        PieData pieData;

        String avg_str_temp;
        String avg_home_temp;
        String avg_str_hum;
        String avg_home_hum;
        String avg_rainfall;
        String avg_wind_speed;
        String max_str_temp;
        String max_home_temp;
        String max_str_hum;
        String max_home_hum;
        String max_rainfall;
        String max_wind_speed;
        String max_bat_charge;
        String min_str_temp;
        String min_home_temp;
        String min_str_hum;
        String min_home_hum;
        String min_rainfall;
        String min_wind_speed;
        String min_bat_charge;
        DecimalFormat decimalFormat = new DecimalFormat( "#.##" );
        CalculateDetails calculateDetails = new CalculateDetails();
        Context context;

        public BackgroundWorkerForDetails(Context ctx){
            context = ctx;
        }
        @Override
        protected String doInBackground(View... params) {
            textView_avg_str_temp = (TextView) params[0];
            textView_avg_home_temp = (TextView) params[1];
            textView_avg_str_hum = (TextView) params[2];
            textView_avg_home_hum = (TextView) params[3];
            textView_avg_rainfall = (TextView) params[4];
            textView_avg_wind_speed = (TextView) params[5];
            textView_max_str_temp = (TextView) params[6];
            textView_max_home_temp = (TextView) params[7];
            textView_max_str_hum = (TextView) params[8];
            textView_max_home_hum = (TextView) params[9];
            textView_max_rainfall = (TextView) params[10];
            textView_max_wind_speed = (TextView) params[11];
            textView_max_bat_charge = (TextView) params[12];
            textView_min_str_temp = (TextView) params[13];
            textView_min_home_temp = (TextView) params[14];
            textView_min_str_hum = (TextView) params[15];
            textView_min_home_hum = (TextView) params[16];
            textView_min_rainfall = (TextView) params[17];
            textView_min_wind_speed = (TextView) params[18];
            textView_min_bat_charge = (TextView) params[19];
            WindDirectDiagram = (PieChart) params[20];


            avg_str_temp = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST1)))) + " °C";
            avg_home_temp = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST7)))) + " °C";
            avg_str_hum = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST2)))) + " %";
            avg_home_hum = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST8)))) + " %";
            avg_rainfall = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST3)))) + " %";
            avg_wind_speed = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST6)))) + " m/s";
            max_str_temp = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST1)))) + " °C";
            max_home_temp = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST7)))) + " °C";
            max_str_hum = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST2)))) + " %";
            max_home_hum = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST8)))) + " %";
            max_rainfall = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST3)))) + " %";
            max_wind_speed = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST6)))) + " m/s";
            max_bat_charge = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST4)))) + " V";
            min_str_temp = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST1)))) + " °C";
            min_home_temp = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST7)))) + " °C";
            min_str_hum = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST2)))) + " %";
            min_home_hum = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST8)))) + " %";
            min_rainfall = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST3)))) + " %";
            min_wind_speed = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST6)))) + " m/s";
            min_bat_charge = Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST4)))) + " V";

            CalculateDetails.Find_Wind_Direct_Percent(BackgroundWorker.LIST5);
            WindDirectDiagram.setUsePercentValues(true);
            WindDirectDiagram.getDescription().setEnabled(false);

            List<PieEntry> yVals = new ArrayList<>();
            List<Integer> colors = new ArrayList<>();
            if (CalculateDetails.NW_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.NW_Count, "N-W"));
                colors.add(Color.parseColor("#FF2A18"));
            }
            if (CalculateDetails.N_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.N_Count, "N"));
                colors.add(Color.parseColor("#FF9118"));
            }
            if (CalculateDetails.S_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.S_Count, "S"));
                colors.add(Color.parseColor("#FFE918"));
            }
            if (CalculateDetails.E_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.E_Count, "E"));
                colors.add(Color.parseColor("#ADFF18"));
            }
            if (CalculateDetails.W_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.W_Count, "W"));
                colors.add(Color.parseColor("#1AFF18"));
            }
            if (CalculateDetails.NE_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.NE_Count, "N-E"));
                colors.add(Color.parseColor("#18EBFF"));
            }
            if (CalculateDetails.SW_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.SW_Count, "S-W"));
                colors.add(Color.parseColor("#1829FF"));
            }
            if (CalculateDetails.SE_Count != 0)
            {
                yVals.add(new PieEntry((float)CalculateDetails.SE_Count, "S-E"));
                colors.add(Color.parseColor("#FF18ED"));
            }

            PieDataSet pieDataSet = new PieDataSet(yVals, "");
            pieDataSet.setColors(colors);
            pieData = new PieData(pieDataSet);


            return null;
        }

        @Override
        protected void onPreExecute() {
            //WindDirectDiagram.setVisibility(View.INVISIBLE);
            Toast.makeText(context.getApplicationContext(),"Пожалуйста подождите, идут вычисления...",Toast.LENGTH_LONG).show();
        }

        @Override
        protected void onPostExecute(String result) {
            if ((BackgroundWorker.LIST1.size() != 0) && (BackgroundWorker.LIST7.size() != 0) && (BackgroundWorker.LIST2.size() != 0) && (BackgroundWorker.LIST8.size() != 0) && (BackgroundWorker.LIST3.size() != 0) && (BackgroundWorker.LIST6.size() != 0) && (BackgroundWorker.LIST4.size() != 0))
            {
                WindDirectDiagram.setVisibility(View.VISIBLE);
                textView_avg_str_temp.setText(avg_str_temp);
                textView_avg_home_temp.setText(avg_home_temp);
                textView_avg_str_hum.setText(avg_str_hum);
                textView_avg_home_hum.setText(avg_home_hum);
                textView_avg_rainfall.setText(avg_rainfall);
                textView_avg_wind_speed.setText(avg_wind_speed);

                textView_max_str_temp.setText(max_str_temp);
                textView_max_home_temp.setText(max_home_temp);
                textView_max_str_hum.setText(max_str_hum);
                textView_max_home_hum.setText(max_home_hum);
                textView_max_rainfall.setText(max_rainfall);
                textView_max_wind_speed.setText(max_wind_speed);
                textView_max_bat_charge.setText(max_bat_charge);

                textView_min_str_temp.setText(min_str_temp);
                textView_min_home_temp.setText(min_home_temp);
                textView_min_str_hum.setText(min_str_hum);
                textView_min_home_hum.setText(min_home_hum);
                textView_min_rainfall.setText(min_rainfall);
                textView_min_wind_speed.setText(min_wind_speed);
                textView_min_bat_charge.setText(min_bat_charge);

                WindDirectDiagram.setData(pieData);
            }
            else
            {
                Toast.makeText(context.getApplicationContext(),"Ошибка вычислений! (База Данных пустая!)",Toast.LENGTH_LONG).show();
            }
        }
        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);

        }


}
