package com.example.homeweatherstationapp;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.view.Gravity;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter;
import com.github.mikephil.charting.renderer.XAxisRenderer;
import com.github.mikephil.charting.utils.MPPointF;
import com.github.mikephil.charting.utils.Transformer;
import com.github.mikephil.charting.utils.Utils;
import com.github.mikephil.charting.utils.ViewPortHandler;

import java.util.ArrayList;

public class CreateCharts {
    public void Fill_Street_Temp_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST1.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST1.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Уличная температура, °C");
        dataset.setDrawFilled(true);
        dataset.setFillColor(Color.RED);
        dataset.setColor(Color.RED);
        dataset.setCircleColor(Color.RED);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Street_HUM_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST2.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST2.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Уличная влажность, %");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.BLUE);
        dataset.setFillColor(Color.BLUE);
        dataset.setCircleColor(Color.BLUE);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Rain_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST3.size();i++)
        {
            //entries.add(new Entry(i, 100 - 100 * Float.parseFloat(Firebase.LIST3.get(i))));
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST3.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Количество осадков, %");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.GREEN);
        dataset.setFillColor(Color.GREEN);
        dataset.setCircleColor(Color.GREEN);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_VBAT_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST4.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST4.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Заряд аккумулятора, В");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.CYAN);
        dataset.setFillColor(Color.CYAN);
        dataset.setCircleColor(Color.CYAN);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Wind_Direct_Table(TableLayout wind_direct_table, Context context) {
        //int ROWS = 3;
        int COLS = 4;

        //for (int i = 0; i < (Firebase.LIST10.size()/4) + 1; i++)
        int i = 0;
        int k = 0;
        while(k < (BackgroundWorker.LIST10.size()/4) + 1)
        {
            //строка с временем
            TableRow tableRow = new TableRow(context);
            tableRow.setBackgroundColor(Color.parseColor("#0079D6"));
            tableRow.setLayoutParams(new TableLayout.LayoutParams(
                    TableLayout.LayoutParams.MATCH_PARENT,
                    TableLayout.LayoutParams.WRAP_CONTENT));
            for (int j = 0; j < COLS; j++)
            {
                TextView textView1 = new TextView(context);
                textView1.setTextColor(Color.BLACK);
                textView1.setGravity(Gravity.CENTER);
                if ((j + COLS*k) < BackgroundWorker.LIST10.size())
                {
                    textView1.setText(BackgroundWorker.LIST10.get(j + COLS*k));
                }
                tableRow.addView(textView1, new TableRow.LayoutParams(
                        TableRow.LayoutParams.WRAP_CONTENT, TableRow.LayoutParams.WRAP_CONTENT, 0.5f));
            }
            wind_direct_table.addView(tableRow, i);
            i++;
            //строка с данными
            TableRow tableRow1 = new TableRow(context);
            tableRow1.setBackgroundColor(Color.parseColor("#DAE8FC"));
            tableRow1.setLayoutParams(new TableLayout.LayoutParams(
                    TableLayout.LayoutParams.MATCH_PARENT,
                    TableLayout.LayoutParams.WRAP_CONTENT));
            for (int j = 0; j < COLS; j++) {
                TextView textView2 = new TextView(context);
                textView2.setTextColor(Color.BLACK);
                textView2.setGravity(Gravity.CENTER);
                if ((j + COLS*k) < BackgroundWorker.LIST5.size())
                {
                    textView2.setText(BackgroundWorker.LIST5.get(j + COLS*k));
                }
                tableRow1.addView(textView2, new TableRow.LayoutParams(
                        TableRow.LayoutParams.WRAP_CONTENT, TableRow.LayoutParams.WRAP_CONTENT, 0.5f));
            }
            wind_direct_table.addView(tableRow1, i);
            k++;
            i++;
        }
    }
    public void Fill_Wind_Speed_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST6.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST6.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Скорость ветра, м/с");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.MAGENTA);
        dataset.setFillColor(Color.MAGENTA);
        dataset.setCircleColor(Color.MAGENTA);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Home_Temp_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST7.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST7.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Комнатная температура, °C");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.LTGRAY);
        dataset.setFillColor(Color.LTGRAY);
        dataset.setCircleColor(Color.LTGRAY);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Home_Hum_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST8.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST8.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Комнатная влажность, %");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.rgb(255, 150,0));
        dataset.setFillColor(Color.rgb(255, 150,0));
        dataset.setCircleColor(Color.rgb(255, 150,0));
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Pressure_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < BackgroundWorker.LIST9.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(BackgroundWorker.LIST9.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Атмосферное давление, мм.рт.ст");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.DKGRAY);
        dataset.setFillColor(Color.DKGRAY);
        dataset.setCircleColor(Color.DKGRAY);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);

        //chart.setVisibleXRangeMaximum(4);
        //chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(BackgroundWorker.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(4, false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }

}

