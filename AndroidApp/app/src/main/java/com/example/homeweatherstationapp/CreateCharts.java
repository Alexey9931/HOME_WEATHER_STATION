package com.example.homeweatherstationapp;

import android.content.Context;
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

import java.util.ArrayList;

public class CreateCharts {
    public void Fill_Street_Temp_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST1.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST1.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Уличная температура, °C");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.RED);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Street_HUM_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST2.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST2.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Уличная влажность, %");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.BLUE);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Rain_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST3.size();i++)
        {
            //entries.add(new Entry(i, 100 - 100 * Float.parseFloat(Firebase.LIST3.get(i))));
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST3.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Количество осадков, %");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.GREEN);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_VBAT_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST4.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST4.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Заряд аккумулятора, В");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.CYAN);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
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
        while(k < (Firebase.LIST10.size()/4) + 1)
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
                if ((j + COLS*k) < Firebase.LIST10.size())
                {
                    textView1.setText(Firebase.LIST10.get(j + COLS*k));
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
                if ((j + COLS*k) < Firebase.LIST5.size())
                {
                    textView2.setText(Firebase.LIST5.get(j + COLS*k));
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
        for (int i = 0; i < Firebase.LIST6.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST6.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Скорость ветра, м/с");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.MAGENTA);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Home_Temp_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST7.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST7.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Комнатная температура, °C");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.LTGRAY);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Home_Hum_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST8.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST8.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Комнатная влажность, %");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.YELLOW);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Pressure_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST9.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST9.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Атмосферное давление, мм.рт.ст");
        dataset.setDrawFilled(true);
        dataset.setColor(Color.DKGRAY);
        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);
        chart.setDrawBorders(true);
        chart.setDrawMarkers(true);
        chart.getDescription().setEnabled(false);
        //chart.setScaleMinima(1f, 1f);
        chart.setVisibleXRangeMaximum(4);
        chart.setScaleXEnabled(false);

        YAxis yAxisRight = chart.getAxisRight();
        yAxisRight.setTextColor(Color.WHITE);

        XAxis xAxis = chart.getXAxis();
        xAxis.setValueFormatter(new IndexAxisValueFormatter(Firebase.LIST10));
        xAxis.setGranularityEnabled(true);
        xAxis.setLabelCount(Firebase.LIST10.size(), false);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawGridLines(true);
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }

}
