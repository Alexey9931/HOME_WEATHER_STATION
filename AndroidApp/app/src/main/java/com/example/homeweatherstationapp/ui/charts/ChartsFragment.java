package com.example.homeweatherstationapp.ui.charts;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TableLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.example.homeweatherstationapp.CreateCharts;
import com.example.homeweatherstationapp.R;
import com.example.homeweatherstationapp.databinding.FragmentChartsBinding;
import com.example.homeweatherstationapp.ui.chart_settings.ChartSettingFragment;
import com.github.mikephil.charting.charts.LineChart;

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
        final TableLayout wind_direct_table = root.findViewById(R.id.table);

        street_temp_chart.setVisibility(View.GONE);
        street_hum_chart.setVisibility(View.GONE);
        rain_chart.setVisibility(View.GONE);
        vbat_chart.setVisibility(View.GONE);
        wind_speed_chart.setVisibility(View.GONE);
        home_temp_chart.setVisibility(View.GONE);
        home_hum_chart.setVisibility(View.GONE);
        pressure_chart.setVisibility(View.GONE);
        wind_direct_table.setVisibility(View.GONE);


        //SettingsActivity settingsActivity = new SettingsActivity();
        String mode = ChartSettingFragment.choose_chart_mode;
        if (mode == "nothing")
        {

        }
        else if (mode == "all_other")
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

            CreateCharts create_chart = new CreateCharts();

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
            create_chart.Fill_Wind_Direct_Table(wind_direct_table,getContext());

            /*RelativeLayout.LayoutParams layoutParams8 = new RelativeLayout.LayoutParams(1300,750);
            layoutParams8.leftMargin = 15;
            layoutParams8.topMargin = 5950;
            wind_direct_chart.setLayoutParams(layoutParams8);
            create_chart.Fill_Wind_Direct_Chart(wind_direct_chart);*/

        }
        else
        {
            if (ChartSettingFragment.TEMP_HOME_MODE == true)
            {
                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(1300,750);
                layoutParams.leftMargin = 15;
                layoutParams.topMargin = 850*count;
                home_temp_chart.setLayoutParams(layoutParams);

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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

                CreateCharts create_chart = new CreateCharts();
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


                CreateCharts create_chart = new CreateCharts();
                wind_direct_table.setVisibility(View.VISIBLE);
                create_chart.Fill_Wind_Direct_Table(wind_direct_table,getContext());
                count++;
            }
        }

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}