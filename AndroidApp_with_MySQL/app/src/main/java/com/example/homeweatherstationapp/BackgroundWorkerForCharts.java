package com.example.homeweatherstationapp;

import android.content.Context;
import android.graphics.Color;
import android.os.AsyncTask;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TableLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.example.homeweatherstationapp.ui.chart_settings.ChartSettingFragment;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;

import java.util.ArrayList;
import java.util.List;

public class BackgroundWorkerForCharts extends AsyncTask<View,Void,String> {
    LineChart street_temp_chart;
    LineChart street_hum_chart;
    LineChart rain_chart;
    LineChart vbat_chart;
    LineChart wind_speed_chart;
    LineChart home_temp_chart;
    LineChart home_hum_chart;
    LineChart pressure_chart;
    TableLayout wind_direct_table;
    //TextView error_message;
    Context context;

    CreateCharts create_chart = new CreateCharts();
    public BackgroundWorkerForCharts(Context ctx){
        context = ctx;
    }
    @Override
    protected String doInBackground(View... params) {
        street_temp_chart = (LineChart) params[0];
        street_hum_chart = (LineChart) params[1];
        rain_chart = (LineChart) params[2];
        vbat_chart = (LineChart) params[3];
        wind_speed_chart = (LineChart) params[4];
        home_temp_chart = (LineChart) params[5];
        home_hum_chart = (LineChart) params[6];
        pressure_chart = (LineChart) params[7];
        wind_direct_table = (TableLayout) params[8];

        return null;
    }

    @Override
    protected void onPreExecute() {

    }

    @Override
    protected void onPostExecute(String result) {
        int count = 0;
        String mode = ChartSettingFragment.choose_chart_mode;
        if (mode == "all_other")
        {
            street_temp_chart.setVisibility(View.VISIBLE);
            street_hum_chart.setVisibility(View.VISIBLE);
            rain_chart.setVisibility(View.VISIBLE);
            vbat_chart.setVisibility(View.VISIBLE);
            wind_speed_chart.setVisibility(View.VISIBLE);
            home_temp_chart.setVisibility(View.VISIBLE);
            home_hum_chart.setVisibility(View.VISIBLE);
            pressure_chart.setVisibility(View.VISIBLE);
            wind_direct_table.setVisibility(View.VISIBLE);

            //CreateCharts create_chart = new CreateCharts();

            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 15;
            layoutParams.topMargin = 0;
            home_temp_chart.setLayoutParams(layoutParams);
            create_chart.Fill_Home_Temp_Chart(home_temp_chart);

            RelativeLayout.LayoutParams layoutParams1 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams1.leftMargin = 15;
            layoutParams1.topMargin = 850;
            street_temp_chart.setLayoutParams(layoutParams1);
            create_chart.Fill_Street_Temp_Chart(street_temp_chart);

            RelativeLayout.LayoutParams layoutParams2 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams2.leftMargin = 15;
            layoutParams2.topMargin = 1700;
            street_hum_chart.setLayoutParams(layoutParams2);
            create_chart.Fill_Street_HUM_Chart(street_hum_chart);

            RelativeLayout.LayoutParams layoutParams3 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams3.leftMargin = 15;
            layoutParams3.topMargin = 2550;
            home_hum_chart.setLayoutParams(layoutParams3);
            create_chart.Fill_Home_Hum_Chart(home_hum_chart);

            RelativeLayout.LayoutParams layoutParams4 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams4.leftMargin = 15;
            layoutParams4.topMargin = 3400;
            pressure_chart.setLayoutParams(layoutParams4);
            create_chart.Fill_Pressure_Chart(pressure_chart);

            RelativeLayout.LayoutParams layoutParams5 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams5.leftMargin = 15;
            layoutParams5.topMargin = 4250;
            wind_speed_chart.setLayoutParams(layoutParams5);
            create_chart.Fill_Wind_Speed_Chart(wind_speed_chart);

            RelativeLayout.LayoutParams layoutParams6 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams6.leftMargin = 15;
            layoutParams6.topMargin = 5100;
            rain_chart.setLayoutParams(layoutParams6);
            create_chart.Fill_Rain_Chart(rain_chart);

            RelativeLayout.LayoutParams layoutParams7 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams7.leftMargin = 15;
            layoutParams7.topMargin = 5950;
            vbat_chart.setLayoutParams(layoutParams7);
            create_chart.Fill_VBAT_Chart(vbat_chart);

            RelativeLayout.LayoutParams layoutParams8 = new RelativeLayout.LayoutParams(900,RelativeLayout.LayoutParams.WRAP_CONTENT);
            layoutParams8.leftMargin = 100;
            layoutParams8.topMargin = 6850;
            wind_direct_table.setLayoutParams(layoutParams8);
            create_chart.Fill_Wind_Direct_Table(wind_direct_table,context);

        }
        else
        {
            if (ChartSettingFragment.TEMP_HOME_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                home_temp_chart.setLayoutParams(layoutParams);

               // CreateCharts create_chart = new CreateCharts();
                home_temp_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Home_Temp_Chart(home_temp_chart);
                count++;
            }
            if (ChartSettingFragment.TEMP_STREET_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                street_temp_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                street_temp_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Street_Temp_Chart(street_temp_chart);
                count++;
            }
            if (ChartSettingFragment.HUM_STREET_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                street_hum_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                street_hum_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Street_HUM_Chart(street_hum_chart);
                count++;
            }
            if (ChartSettingFragment.HUM_HOME_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                home_hum_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                home_hum_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Home_Hum_Chart(home_hum_chart);
                count++;
            }
            if (ChartSettingFragment.PRESSURE_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                pressure_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                pressure_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Pressure_Chart(pressure_chart);
                count++;
            }
            if (ChartSettingFragment.WIND_SPEED_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                wind_speed_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                wind_speed_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Wind_Speed_Chart(wind_speed_chart);
                count++;
            }
            if (ChartSettingFragment.RAIN_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                rain_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                rain_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_Rain_Chart(rain_chart);
                count++;
            }
            if (ChartSettingFragment.VBAT_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                vbat_chart.setLayoutParams(layoutParams);

                //CreateCharts create_chart = new CreateCharts();
                vbat_chart.setVisibility(View.VISIBLE);
                create_chart.Fill_VBAT_Chart(vbat_chart);
                count++;
            }
            if (ChartSettingFragment.WIND_DIRECT_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(900,RelativeLayout.LayoutParams.WRAP_CONTENT);
                layoutParams.leftMargin = 100;
                layoutParams.topMargin = 850*count;
                wind_direct_table.setLayoutParams(layoutParams);


                //CreateCharts create_chart = new CreateCharts();
                wind_direct_table.setVisibility(View.VISIBLE);
                create_chart.Fill_Wind_Direct_Table(wind_direct_table,context);
                count++;
            }

        }
    }
    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);

    }
}
