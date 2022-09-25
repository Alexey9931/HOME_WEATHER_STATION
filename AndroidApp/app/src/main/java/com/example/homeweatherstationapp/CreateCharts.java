package com.example.homeweatherstationapp;

import android.graphics.Color;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;

import java.util.ArrayList;
import java.util.Collections;

public class CreateCharts {
    public void Fill_Street_Temp_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST1.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST1.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Уличная температура");
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
        LineDataSet dataset = new LineDataSet(entries, "Уличная влажность");
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
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Rain_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST3.size();i++)
        {
            entries.add(new Entry(i, 100 - 100 * Float.parseFloat(Firebase.LIST3.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Количество осадков");
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
        LineDataSet dataset = new LineDataSet(entries, "Заряд аккумулятора");
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
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Wind_Direct_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST5.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST5.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Направление ветра");

        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);

        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
    public void Fill_Wind_Speed_Chart(LineChart chart)
    {
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST6.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST6.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Скорость ветра");
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
        LineDataSet dataset = new LineDataSet(entries, "Комнатная температура");
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
        LineDataSet dataset = new LineDataSet(entries, "Комнатная влажность");
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
        LineDataSet dataset = new LineDataSet(entries, "Атмосферное давление");
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
        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();
    }
}
