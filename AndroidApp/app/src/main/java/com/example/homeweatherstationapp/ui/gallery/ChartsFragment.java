package com.example.homeweatherstationapp.ui.gallery;

import static com.example.homeweatherstationapp.R.id.street_temp_chart;

import android.os.Bundle;
import android.provider.Settings;
import android.service.controls.Control;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import com.example.homeweatherstationapp.CreateCharts;
import com.example.homeweatherstationapp.Firebase;
import com.example.homeweatherstationapp.R;
import com.example.homeweatherstationapp.SettingsActivity;
import com.example.homeweatherstationapp.databinding.FragmentChartsBinding;
import com.example.homeweatherstationapp.ui.home.HomeFragment;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;

import java.util.ArrayList;

public class ChartsFragment extends Fragment {

    private FragmentChartsBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
       /* GalleryViewModel galleryViewModel =
                new ViewModelProvider(this).get(GalleryViewModel.class);*/

        binding = FragmentChartsBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        int count = 0;

        final LineChart street_temp_chart = root.findViewById(R.id.street_temp_chart);
        final LineChart street_hum_chart = root.findViewById(R.id.street_hum_chart);
        final LineChart rain_chart = root.findViewById(R.id.rain_chart);
        final LineChart vbat_chart = root.findViewById(R.id.vbat_chart);
        final LineChart wind_speed_chart = root.findViewById(R.id.wind_speed_chart);
        final LineChart home_temp_chart = root.findViewById(R.id.home_temp_chart);
        final LineChart home_hum_chart = root.findViewById(R.id.home_hum_chart);
        final LineChart pressure_chart = root.findViewById(R.id.pressure_chart);

        street_temp_chart.setVisibility(View.GONE);
        street_hum_chart.setVisibility(View.GONE);
        rain_chart.setVisibility(View.GONE);
        vbat_chart.setVisibility(View.GONE);
        wind_speed_chart.setVisibility(View.GONE);
        home_temp_chart.setVisibility(View.GONE);
        home_hum_chart.setVisibility(View.GONE);
        pressure_chart.setVisibility(View.GONE);

        if (SettingsActivity.choose_chart_mode == "nothing")
        {

        }
        if (SettingsActivity.choose_chart_mode == "all_other")
        {
            street_temp_chart.setVisibility(View.VISIBLE);
            street_hum_chart.setVisibility(View.VISIBLE);
            rain_chart.setVisibility(View.VISIBLE);
            vbat_chart.setVisibility(View.VISIBLE);
            wind_speed_chart.setVisibility(View.VISIBLE);
            home_temp_chart.setVisibility(View.VISIBLE);
            home_hum_chart.setVisibility(View.VISIBLE);
            pressure_chart.setVisibility(View.VISIBLE);

            CreateCharts create_chart = new CreateCharts();

            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 0;
            home_temp_chart.setLayoutParams(layoutParams);
            create_chart.Fill_Home_Temp_Chart(home_temp_chart);

            RelativeLayout.LayoutParams layoutParams1 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams1.leftMargin = 50;
            layoutParams1.topMargin = 850;
            street_temp_chart.setLayoutParams(layoutParams1);
            create_chart.Fill_Street_Temp_Chart(street_temp_chart);

            RelativeLayout.LayoutParams layoutParams2 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams2.leftMargin = 50;
            layoutParams2.topMargin = 1700;
            street_hum_chart.setLayoutParams(layoutParams2);
            create_chart.Fill_Street_HUM_Chart(street_hum_chart);

            RelativeLayout.LayoutParams layoutParams3 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams3.leftMargin = 50;
            layoutParams3.topMargin = 2550;
            home_hum_chart.setLayoutParams(layoutParams3);
            create_chart.Fill_Home_Hum_Chart(home_hum_chart);

            RelativeLayout.LayoutParams layoutParams4 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams4.leftMargin = 50;
            layoutParams4.topMargin = 3400;
            pressure_chart.setLayoutParams(layoutParams4);
            create_chart.Fill_Pressure_Chart(pressure_chart);

            RelativeLayout.LayoutParams layoutParams5 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams5.leftMargin = 50;
            layoutParams5.topMargin = 4250;
            wind_speed_chart.setLayoutParams(layoutParams5);
            create_chart.Fill_Wind_Speed_Chart(wind_speed_chart);

            RelativeLayout.LayoutParams layoutParams6 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams6.leftMargin = 50;
            layoutParams6.topMargin = 5100;
            rain_chart.setLayoutParams(layoutParams6);
            create_chart.Fill_Rain_Chart(rain_chart);

            RelativeLayout.LayoutParams layoutParams7 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams7.leftMargin = 50;
            layoutParams7.topMargin = 5950;
            vbat_chart.setLayoutParams(layoutParams7);
            create_chart.Fill_VBAT_Chart(vbat_chart);

        }

        if (SettingsActivity.TEMP_HOME_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            home_temp_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            home_temp_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Home_Temp_Chart(home_temp_chart);
            count++;
        }
        if (SettingsActivity.TEMP_STREET_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            street_temp_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            street_temp_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Street_Temp_Chart(street_temp_chart);
            count++;
        }
        if (SettingsActivity.HUM_STREET_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            street_hum_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            street_hum_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Street_HUM_Chart(street_hum_chart);
            count++;
        }
        if (SettingsActivity.HUM_HOME_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            home_hum_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            home_hum_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Home_Hum_Chart(home_hum_chart);
            count++;
        }
        if (SettingsActivity.PRESSURE_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            pressure_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            pressure_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Pressure_Chart(pressure_chart);
            count++;
        }
        if (SettingsActivity.WIND_SPEED_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            wind_speed_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            wind_speed_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Wind_Speed_Chart(wind_speed_chart);
            count++;
        }
        if (SettingsActivity.RAIN_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            rain_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            rain_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_Rain_Chart(rain_chart);
            count++;
        }
        if (SettingsActivity.VBAT_MODE == true)
        {
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
            layoutParams.leftMargin = 50;
            layoutParams.topMargin = 850*count;
            vbat_chart.setLayoutParams(layoutParams);

            CreateCharts create_chart = new CreateCharts();
            vbat_chart.setVisibility(View.VISIBLE);
            create_chart.Fill_VBAT_Chart(vbat_chart);
            count++;
        }
        /*create_chart.Fill_Street_Temp_Chart(street_temp_chart);
        create_chart.Fill_Street_HUM_Chart(street_hum_chart);
        create_chart.Fill_Rain_Chart(rain_chart);
        create_chart.Fill_VBAT_Chart(vbat_chart);
        create_chart.Fill_Wind_Speed_Chart(wind_speed_chart);
        create_chart.Fill_Home_Temp_Chart(home_temp_chart);
        create_chart.Fill_Home_Hum_Chart(home_hum_chart);
        create_chart.Fill_Pressure_Chart(pressure_chart);*/
        /*// Массив координат точек
        ArrayList<Entry> entries = new ArrayList<>();
        for (int i = 0; i < Firebase.LIST1.size();i++)
        {
            entries.add(new Entry(i, Float.parseFloat(Firebase.LIST1.get(i))));
        }

        // На основании массива точек создадим первую линию с названием
        LineDataSet dataset = new LineDataSet(entries, "Уличная температура");

        // Создадим переменную данных для графика
        LineData data = new LineData(dataset);
        // Передадим данные для графика в сам график
        chart.setData(data);
        chart.animateX(500);

        // Не забудем отправить команду на перерисовку кадра, иначе график не отобразится
        chart.invalidate();*/


        //galleryViewModel.getText().observe(getViewLifecycleOwner(), textView::setText);
        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}