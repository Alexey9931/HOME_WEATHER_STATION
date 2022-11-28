package com.example.homeweatherstationapp;

import android.graphics.Color;
import android.os.Bundle;
import android.text.util.Linkify;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import com.example.homeweatherstationapp.databinding.FragmentMoreDetailsBinding;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.components.Description;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

public class MoreDetailsFragment extends Fragment {
    private FragmentMoreDetailsBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        binding = FragmentMoreDetailsBinding.inflate(inflater, container, false);
        View root = binding.getRoot();
        DecimalFormat decimalFormat = new DecimalFormat( "#.##" );
        CalculateDetails calculateDetails = new CalculateDetails();

        final TextView textView_avg_str_temp = root.findViewById(R.id.textView_avg_str_temp);
        final TextView textView_avg_home_temp = root.findViewById(R.id.textView_avg_home_temp);
        final TextView textView_avg_str_hum = root.findViewById(R.id.textView_avg_str_hum);
        final TextView textView_avg_home_hum = root.findViewById(R.id.textView_avg_home_hum);
        final TextView textView_avg_rainfall = root.findViewById(R.id.textView_avg_rainfall);
        final TextView textView_avg_wind_speed = root.findViewById(R.id.textView_avg_wind_speed);
        final TextView textView_max_str_temp = root.findViewById(R.id.textView_max_str_temp);
        final TextView textView_max_home_temp = root.findViewById(R.id.textView_max_home_temp);
        final TextView textView_max_str_hum = root.findViewById(R.id.textView_max_str_hum);
        final TextView textView_max_home_hum = root.findViewById(R.id.textView_max_home_hum);
        final TextView textView_max_rainfall = root.findViewById(R.id.textView_max_rainfall);
        final TextView textView_max_wind_speed = root.findViewById(R.id.textView_max_wind_speed);
        final TextView textView_max_bat_charge = root.findViewById(R.id.textView_max_bat_charge);
        final TextView textView_min_str_temp = root.findViewById(R.id.textView_min_str_temp);
        final TextView textView_min_home_temp = root.findViewById(R.id.textView_min_home_temp);
        final TextView textView_min_str_hum = root.findViewById(R.id.textView_min_str_hum);
        final TextView textView_min_home_hum = root.findViewById(R.id.textView_min_home_hum);
        final TextView textView_min_rainfall = root.findViewById(R.id.textView_min_rainfall);
        final TextView textView_min_wind_speed = root.findViewById(R.id.textView_min_wind_speed);
        final TextView textView_min_bat_charge = root.findViewById(R.id.textView_min_bat_charge);
        final PieChart WindDirectDiagram = root.findViewById(R.id.WindDirectDiagram);

        textView_avg_str_temp.setVisibility(View.GONE);
        textView_avg_home_temp.setVisibility(View.GONE);
        textView_avg_str_hum.setVisibility(View.GONE);
        textView_avg_home_hum.setVisibility(View.GONE);
        textView_avg_rainfall.setVisibility(View.GONE);
        textView_avg_wind_speed.setVisibility(View.GONE);
        textView_max_str_temp.setVisibility(View.GONE);
        textView_max_home_temp.setVisibility(View.GONE);
        textView_max_str_hum.setVisibility(View.GONE);
        textView_max_home_hum.setVisibility(View.GONE);
        textView_max_rainfall.setVisibility(View.GONE);
        textView_max_wind_speed.setVisibility(View.GONE);
        textView_max_bat_charge.setVisibility(View.GONE);
        textView_min_str_temp.setVisibility(View.GONE);
        textView_min_home_temp.setVisibility(View.GONE);
        textView_min_str_hum.setVisibility(View.GONE);
        textView_min_home_hum.setVisibility(View.GONE);
        textView_min_rainfall.setVisibility(View.GONE);
        textView_min_wind_speed.setVisibility(View.GONE);
        textView_min_bat_charge.setVisibility(View.GONE);

        //if (!Firebase.error)
        //{
            textView_avg_str_temp.setVisibility(View.VISIBLE);
            textView_avg_home_temp.setVisibility(View.VISIBLE);
            textView_avg_str_hum.setVisibility(View.VISIBLE);
            textView_avg_home_hum.setVisibility(View.VISIBLE);
            textView_avg_rainfall.setVisibility(View.VISIBLE);
            textView_avg_wind_speed.setVisibility(View.VISIBLE);
            textView_max_str_temp.setVisibility(View.VISIBLE);
            textView_max_home_temp.setVisibility(View.VISIBLE);
            textView_max_str_hum.setVisibility(View.VISIBLE);
            textView_max_home_hum.setVisibility(View.VISIBLE);
            textView_max_rainfall.setVisibility(View.VISIBLE);
            textView_max_wind_speed.setVisibility(View.VISIBLE);
            textView_max_bat_charge.setVisibility(View.VISIBLE);
            textView_min_str_temp.setVisibility(View.VISIBLE);
            textView_min_home_temp.setVisibility(View.VISIBLE);
            textView_min_str_hum.setVisibility(View.VISIBLE);
            textView_min_home_hum.setVisibility(View.VISIBLE);
            textView_min_rainfall.setVisibility(View.VISIBLE);
            textView_min_wind_speed.setVisibility(View.VISIBLE);
            textView_min_bat_charge.setVisibility(View.VISIBLE);

            textView_avg_str_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST1)))) + " °C");
            textView_avg_home_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST7)))) + " °C");
            textView_avg_str_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST2)))) + " %");
            textView_avg_home_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST8)))) + " %");
            textView_avg_rainfall.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST3)))) + " %");
            textView_avg_wind_speed.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(BackgroundWorker.LIST6)))) + " m/s");

            textView_max_str_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST1)))) + " °C");
            textView_max_home_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST7)))) + " °C");
            textView_max_str_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST2)))) + " %");
            textView_max_home_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST8)))) + " %");
            textView_max_rainfall.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST3)))) + " %");
            textView_max_wind_speed.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST6)))) + " m/s");
            textView_max_bat_charge.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMax(BackgroundWorker.LIST4)))) + " V");

            textView_min_str_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST1)))) + " °C");
            textView_min_home_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST7)))) + " °C");
            textView_min_str_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST2)))) + " %");
            textView_min_home_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST8)))) + " %");
            textView_min_rainfall.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST3)))) + " %");
            textView_min_wind_speed.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST6)))) + " m/s");
            textView_min_bat_charge.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateMin(BackgroundWorker.LIST4)))) + " V");

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
            PieData pieData = new PieData(pieDataSet);

            WindDirectDiagram.setData(pieData);

        //}
        /*else
        {
            Toast.makeText(getContext(), "Невозможно отобразить информацию! Ошибка в базе данных! Отсутствуют некоторые показания!", Toast.LENGTH_SHORT).show();
            textView_avg_str_temp.setVisibility(View.GONE);
            textView_avg_home_temp.setVisibility(View.GONE);
            textView_avg_str_hum.setVisibility(View.GONE);
            textView_avg_home_hum.setVisibility(View.GONE);
            textView_avg_rainfall.setVisibility(View.GONE);
            textView_avg_wind_speed.setVisibility(View.GONE);
            textView_max_str_temp.setVisibility(View.GONE);
            textView_max_home_temp.setVisibility(View.GONE);
            textView_max_str_hum.setVisibility(View.GONE);
            textView_max_home_hum.setVisibility(View.GONE);
            textView_max_rainfall.setVisibility(View.GONE);
            textView_max_wind_speed.setVisibility(View.GONE);
            textView_max_bat_charge.setVisibility(View.GONE);
            textView_min_str_temp.setVisibility(View.GONE);
            textView_min_home_temp.setVisibility(View.GONE);
            textView_min_str_hum.setVisibility(View.GONE);
            textView_min_home_hum.setVisibility(View.GONE);
            textView_min_rainfall.setVisibility(View.GONE);
            textView_min_wind_speed.setVisibility(View.GONE);
            textView_min_bat_charge.setVisibility(View.GONE);
        }*/

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}
